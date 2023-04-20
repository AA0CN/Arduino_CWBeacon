/*******************************
* CW Beacon, Serial Programmable
* .- .- ----- -.-. -.
* Collin Howe, AA0CN
* Copyleft License, 2017
********************************/

#include <ascii_to_cw.h>
#include <EEPROM.h>

#define NEWLINE F("\n\r")
#define SEPERATOR F("\n\r--------------------------------")

#define OUTPORT 2
#define OUTPORT_INV 7
#define PTTPORT 3
#define PTTPORT_INV 8
#define LED_P13 13




#define ROWS 3
#define COLS 80
#define MESSAGE_LEN (ROWS*COLS)
#define CHAR_BUFF 8

char current_status[COLS];

typedef struct {
  char valid[4];
  char reserved[3]; // TODO: Add a checksum?
  bool tx_relay;
  uint32_t intermessage_pause;
  uint32_t wpm_rate;
  char message[MESSAGE_LEN];
} beacon_config_t;

beacon_config_t config_in_ram;

void eeprom_update(int address, char value)
{
  if (EEPROM.read(address)!= value){
    EEPROM.write(address, value);
  }
}

/*
 * @name strlen
 * @brief String Length, works for null-terminated strings
 * @return Returns the length of string .
 */
int strlen(char* a)
{
  int ret = 0;
  while(a[ret] != 0){
    ret++;
  }
  return ret;
}

//
// strcpy: String Length, works for null-terminated strings
//
int strcpy_s( char * destination, char * source, int length )
{
  // TODO: Check length for int overflow
  // Check for null pointers
  
  memset(destination, 0, MESSAGE_LEN);
  
  int i = 0;
  while((source[i] != 0) && (i <= length)){
    destination[i] = source[i];
    i++;
  }
  return i;
}

//
// Clear remote terminal screen
//
void clear_screen(){
  Serial.write(27);       // ESC command
  Serial.print(F("[2J")); // clear screen command
  Serial.write(27);
  Serial.print(F("[H"));  // cursor to home command
}


//
// wpm_to_dit_ms: Return number of MS equivalent to one dit at given WPM rate
//
unsigned int wpm_to_dit_ms(int wpm, int dits){
  return (dits*(1200/wpm));
}

//
// Output semaphore to output pin: blocking.
//
int semaphore_to_output(const char * semaphore, int out_pin){
  int i = 0;
  int escape = 0;
  while ( (semaphore[i] != 0) ) { // Null terminated strings
  
    if (Serial.available() > 0){
      escape = -1;
      break;
    }
    
    Serial.print(semaphore[i]);
    
    if ((semaphore[i] == '-') || (semaphore[i] == '_')){
      digitalWrite(OUTPORT, HIGH);
      digitalWrite(LED_P13, HIGH);
      digitalWrite(OUTPORT_INV, LOW);
      delay(wpm_to_dit_ms(config_in_ram.wpm_rate, 3)); // Dash weighs 3 dits
      digitalWrite(OUTPORT, LOW);
      digitalWrite(LED_P13, LOW);
      digitalWrite(OUTPORT_INV, HIGH);
      // Inter-symbol pause, one dit
      delay(wpm_to_dit_ms(config_in_ram.wpm_rate, 1));
    }
    else if (semaphore[i] == '.'){
      digitalWrite(OUTPORT, HIGH);
      digitalWrite(LED_P13, HIGH);
      digitalWrite(OUTPORT_INV, LOW);
      delay(wpm_to_dit_ms(config_in_ram.wpm_rate, 1)); // Dit weighs 1 dit
      digitalWrite(OUTPORT, LOW);
      digitalWrite(LED_P13, LOW);
      digitalWrite(OUTPORT_INV, HIGH);
      // Inter-symbol pause, one dit
      delay(wpm_to_dit_ms(config_in_ram.wpm_rate, 1));
    }
    else if (semaphore[i] == ' '){
      // Extra Inter-symbol pause, one dit
      delay(wpm_to_dit_ms(config_in_ram.wpm_rate, 1));
    }
    else {
      // Unknown charachter in semaphore!
      char c = semaphore[i];
      Serial.print(F("\n\r Unknown char in semaphore:"));
      Serial.print(c);
      Serial.print(NEWLINE);
    }
    i++;

  }

  // Newline to seperate semaphores
  Serial.print(NEWLINE);

  // Inter-charachter pause, three dits
    if (Serial.available() > 0){
      escape = -1;
    } else {
      delay(wpm_to_dit_ms(config_in_ram.wpm_rate, 3));
    }
      
  return 0;
}

//
// cw_print: Print a null-terminated String to OUTPORT
//
int cw_print(char * input){
  int i = 0;
  int escape = 0;
  Serial.print(F("Message:\n\r"));
  for(int c = 0; c < MESSAGE_LEN; c++){
    if(input[c] == 0){
      break;
    }
    if((c%COLS==0) && (c!=0)){
      Serial.print(NEWLINE);
    }
    Serial.print(input[c]);
  }
  
  // Print two newlines
  Serial.print(NEWLINE);
  Serial.print(NEWLINE);
  
  while ( input[i] != 0 ) { // Null terminated strings
    Serial.print(input[i]);
    Serial.print(" : ");
    escape = semaphore_to_output(AsciiToSemaphore[(unsigned int) input[i]], OUTPORT);
    if (Serial.available() > 0){
      escape = -1;
      break;
    } else if (escape != 0){
      break;
    }
    i++;
  }
  return escape;
}

//
// s_getstr: GetString from Serial. Terminate with NULL on given Escape char.
//
int s_getstr(char * buffer, int buff_size, char escape, char * prompt){
  int i = 0;
  char charin = 0;
  char tempbuffer[MESSAGE_LEN];

  // Don't initialize the string with anything.
  //strcpy_s(tempbuffer, buffer, MESSAGE_LEN);
  //i=strlen(tempbuffer);
  memset(tempbuffer, 0, MESSAGE_LEN);

  clear_screen();
  Serial.print(prompt);
  Serial.print(tempbuffer);
  do {
    while(Serial.available() <= 0);
    charin = Serial.read();
    if(charin == 0x08){ // Backspace char
      if(i <= 0){
        break;
      }
      i--;
      tempbuffer[i]=0;
      clear_screen();
      Serial.print(prompt);
      for(int c = 0; c < MESSAGE_LEN; c++){
        if(tempbuffer[c] == 0){
          break;
        }
        if((c%COLS==0) && (c!=0)){
          Serial.print(NEWLINE);
        }
        Serial.print(tempbuffer[c]);
      }
    }
#ifdef TEST_EDITOR
    else if ((charin == 0x1b) && (escape != 0x1b)) {
      if(Serial.available() > 0){ 
        charin = Serial.read(); // Retrieve next char
        if(charin == '['){
          // Escape char w. '['
          if(Serial.available() >0){ 
            charin = Serial.read(); // Retrieve next char
            switch(charin){
              case 'A': // Up
                if(i >= COLS){
                  i -= COLS;
                }
                break;
              case 'B': // Down
                if(i + COLS <= strlen(tempbuffer)){
                  i += COLS;
                }
                break;
              case 'C': // Right
                if(i <= strlen(tempbuffer)){
                  i++;
                }
                break;
              case 'D': // Left
                if(i > 0){
                  i--;
                }
                break;
              default:
                ; // No behavior here
            }
          }
        }
      }
      else {
        // Legit Escape key, break out without overwriting string
        return -1;
      }
      charin = 0;
    }
#endif // TEST_EDITOR
    else {
      tempbuffer[i] = charin;
      Serial.print(tempbuffer[i]);
      i++;
      if((i%COLS==0) && (i!=0)){
        Serial.print(NEWLINE);
      }
    }
  } while ( (i < (buff_size-1)) &&
            (tempbuffer[i-1] != escape));
            
  if(tempbuffer[i-1] == escape) {
    tempbuffer[i-1] = 0;
  }
  else {
    tempbuffer[i] = 0;
  }
  
  // Escape caught, to commit.
  strcpy_s(buffer, tempbuffer, MESSAGE_LEN);
  Serial.print(NEWLINE);

  return i;
}

// 
// s_getchar: Get single charachter from Serial
//
char s_getchar(){
  char charout = (char) 0;
  while(Serial.available() <= 0);
  charout = Serial.read();
  return charout;
}

//
// s_get_int: Get Integer from Serial, within limits.
//
int s_get_int(const char * message, int min_val, int max_val){
  char buff[CHAR_BUFF];
  int temp = -1;
  int numchars = 0;
  char charin = 0;
  double power = 0;

  memset(buff, 0, CHAR_BUFF);

  // Only return from here when acceptable int taken in.
  while (temp == -1){
    // If last char was return, attempt to evaluate
    while (charin != '\r'){
      clear_screen();
      // Print out Message
      Serial.print(message);
      // Print out current buffer after message.
      for(int i = 0; i < numchars; i++){
        Serial.print(buff[i]);
      }

      // Wait for serial input
      while(Serial.available() <= 0);
      charin = Serial.read();

      // Evaluate the char input.
      // If it's a number, and not off the end, store it.
      if(charin >= '0' && charin <= '9') {
        if (numchars < CHAR_BUFF) {
          buff[numchars] = charin;
          numchars++;
        }
        else {
          buff[numchars] = charin;
        }
      }
      else if((charin == 0x08) && (numchars > 0)){ // Backspace char
        numchars--;
        buff[numchars]=0;
        clear_screen();
        Serial.print(message);
        for(int i = 0; i < numchars; i++){
          Serial.print(buff[i]);
        }
      }
      else if (charin == 0x7F) {
        // Backspace char: Remove last char from te buffer.
        numchars--;
        // IF was last char, buffer is clear. Numchars should be zeroed.
        if (numchars < 0) {
          numchars = 0;
        }
        // Null out last char removed.
        buff[numchars] = 0;
      }
    }

    // Enter hit. Calculate buffer if any:
    if(numchars > 0){
      temp = 0;
      for(int i = numchars-1; i >= 0; i--){
        // Calculate by nth place: ...100s, 10s, 1s...
        power = pow(10, ((numchars-1)-i)) + 0.5; // 0.5 is ugly hack because POW doesn't play well with ints.
        temp = temp + ( ((int)(buff[i] - '0')) * (int) power );
      }
      if ((temp < min_val) || (temp > max_val)){
        temp = -1;
        charin = 0;
        // Reset buffet, reject
        numchars = 0;
        memset(buff, 0, CHAR_BUFF);
      }
    }
    else {
      // No buffer. Reset vars and try again.
      temp = -1;
      charin = 0;
    }
  }
  return temp;
}


//
// print_options: Print Config Mode to screen
//
void print_options(){
  Serial.print(F("=== Config Mode ===\n\r"));
  Serial.print(F("(D) Done (or Enter)\n\r"));
  Serial.print(F("(S) Save as Default\n\r"));
  Serial.print(F("(T) TX/PTT Relay (TTL Pin "));
  Serial.print(PTTPORT);
  Serial.print(F(") = "));
  if(config_in_ram.tx_relay) {
    Serial.print(F("On\n\r"));
  }
  else {
    Serial.print(F("Off\n\r"));
  }
  Serial.print(F("(W) WPM = "));
  Serial.print(config_in_ram.wpm_rate);
  Serial.print(NEWLINE);
  Serial.print(F("(I) Intermessage Delay, Seconds = "));
  Serial.print(config_in_ram.intermessage_pause);
  Serial.print(NEWLINE);
  Serial.print(F("(E) Edit Message : "));
  Serial.print(NEWLINE);
}

//
// print_Status: Print seperator and the string input
//
void print_status(char * current_status){
  for(int i = 0; i < 80; i++){
    Serial.print('=');
  }
  Serial.print(NEWLINE);
  Serial.print(current_status);
  Serial.print(NEWLINE);
}
 
//
// config_mode: Enter Configuration Mode.
//
void config_mode(){
  
  memset(current_status, 0, COLS);
  
  char * config_in_ram_ptr = (char *) &(config_in_ram.valid[0]);
  char last = 0;
  while(true){
    clear_screen();
    print_options();
    for(int c = 0; c < MESSAGE_LEN; c++){
      if(config_in_ram.message[c] == 0){
        break;
      }
      if((c%COLS==0) && (c!=0)){
        Serial.print(NEWLINE);
      }
      Serial.print(config_in_ram.message[c]);
    }

    Serial.print(NEWLINE);
        
    print_status(current_status);
    last = s_getchar();
    switch(last){
      // (D)one
      case 'D':
      case 'd':
      case '\r':
        clear_screen();
        return;
      // (S)ave
      case 'S':
      case 's':

        for(int i = 4; i < sizeof(beacon_config_t); i++){
          eeprom_update (i, config_in_ram_ptr[i]);
        }
        eeprom_update(0, 'V');
        eeprom_update(1, 'E');
        eeprom_update(2, 'R');
        eeprom_update(3, 'I');

        sprintf(current_status, "EEPROM Configuration Saved!\n\r");

        break;
      // (W)PM
      case 'T':
      case 't':
        config_in_ram.tx_relay = !config_in_ram.tx_relay;
        sprintf(current_status, "\n\r");
        break;
      case 'W':
      case 'w':
        // W: Take new WPM Rate
        config_in_ram.wpm_rate = s_get_int("Enter new WPM: ", 1, 999);
        sprintf(current_status, "New WPM set: %i WPM\n\r", config_in_ram.wpm_rate);
        break;
      // (I)nterval
      case 'I':
      case 'i':
        // I: Take new Interval
        config_in_ram.intermessage_pause = s_get_int("Enter new Interval (Secs): ", 1, 32767); // max int size
        sprintf(current_status, "New Interval set: %i Seconds\n\r", config_in_ram.intermessage_pause);
        break;
      // (E)dit
      case 'E':
      case 'e':
        s_getstr(config_in_ram.message, MESSAGE_LEN, '\r', "Enter New Message:\n\r");
        sprintf(current_status, "New message set!\n\r");
        break;
      default: {
        char charout = last;
        while(Serial.available() > 0){
          charout = Serial.read();
        }
        sprintf(current_status, "\'%c\' [0x%x] -- Unknown command\n\r", charout, charout);
      }
    }
  }
  return;
}

void print_info(){
  Serial.print(F("\n\r- - -  Version 1.00, 2017  - - -"));
  Serial.print(F("\n\r  OUT:         PIN D"));
  Serial.print(OUTPORT);
  Serial.print(F("\n\r  OUT Inverse: PIN D"));
  Serial.print(OUTPORT_INV);
  Serial.print(F("\n\r  PTT:         PIN D"));
  Serial.print(PTTPORT);
  Serial.print(F("\n\r  PTT Inverse: PIN D"));
  Serial.print(PTTPORT_INV);
  Serial.print(SEPERATOR);
  Serial.print(NEWLINE);
}
 
//
// Setup Code, run once.
//
void setup() {
  // Level Output Ports
  pinMode(OUTPORT, OUTPUT);
  pinMode(PTTPORT, OUTPUT);
  pinMode(LED_P13, OUTPUT);

  // Inverse Level Output Ports
  pinMode(OUTPORT_INV, OUTPUT);
  pinMode(PTTPORT_INV, OUTPUT);
  
  digitalWrite(PTTPORT, LOW); // Start in RX
  digitalWrite(PTTPORT_INV, HIGH); // Start in RX

  digitalWrite(OUTPORT, LOW); // Start in non-keyed
  digitalWrite(LED_P13, LOW); // Start in non-keyed
  digitalWrite(OUTPORT_INV, HIGH); // Start in non-keyed
  
  config_in_ram.intermessage_pause = 5;
  config_in_ram.wpm_rate = 10;
  config_in_ram.tx_relay = true;
  memset(config_in_ram.message, 0, MESSAGE_LEN);
  sprintf(config_in_ram.message, "VVV");

  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  clear_screen();
  Serial.print(" ");
  Serial.print(SEPERATOR);
  Serial.print(NEWLINE);
  Serial.print(F("- - -   AA0CN CW BEACON    - - -"));
  Serial.print(SEPERATOR);
  print_info();
  
  
  //
  if( (EEPROM.read(0) == 'V') && (EEPROM.read(1) == 'E') && (EEPROM.read(2) == 'R') && (EEPROM.read(3) == 'I')) {
    // EEPROM image verified!
    char * config_in_ram_ptr = (char *) &(config_in_ram.valid[0]);
    for(int i = 0; i < sizeof(beacon_config_t); i++){
      config_in_ram_ptr[i] = EEPROM.read(i);
    }
    Serial.print(F("EEPROM Configuration restored!\n\r"));
  }

}

//
// Loop Code, repeat
//
void loop() {
  // put your main code here, to run repeatedly:
  long delay_control = 0;
  int bytesAvailable = 0;
  char byte_read = 0;
  while(true){
    bytesAvailable = Serial.available();
    if (bytesAvailable > 0) {
      byte_read = Serial.read();
      if(byte_read == 0x0D) {
        config_mode();
        Serial.print(SEPERATOR);
        Serial.print(F("\n\r Returning to RUN MODE "));
        Serial.print(SEPERATOR);
        delay_control = 0;
      }
      else if ((byte_read=='P') || (byte_read == 'p')) {
        print_info();
        Serial.print(F("\n\rPress any key to continue...\n\r"));
        while(Serial.available() <= 0);
        byte_read = Serial.read(); // Consume last char
        delay_control = 0;
      }
      else {
        byte_read = Serial.read(); // Consume last char, do nothing else.
        Serial.print(F("\n\rUnknown keyboard input  "));
        Serial.print(F("\n\r Press [ENTER] to Configure, [P] for Pins/Info \n\r"));
        while(Serial.available()){
          Serial.read();
        }
      }
    }
    
    if (delay_control == 0) {
      if(config_in_ram.tx_relay){
        digitalWrite(PTTPORT, HIGH); // Put in TX mode
        digitalWrite(PTTPORT_INV, LOW); // Put in TX mode
        // Give relay 100ms head start before keying, but compensate in count.
        delay(100);
        delay_control += 100;
      }
      Serial.print(F("\n\r Press [ENTER] to Configure, [P] for Pins/Info \n\r"));
      cw_print(config_in_ram.message);
      if(config_in_ram.tx_relay){
        digitalWrite(PTTPORT, LOW); // Return to RX
        digitalWrite(PTTPORT_INV, HIGH); // Return to RX
      }
      Serial.print(NEWLINE);
      Serial.print(F(" Intermessage Pause of "));
      Serial.print(config_in_ram.intermessage_pause);
      Serial.print(F(" Seconds..."));
      Serial.print(NEWLINE);
      delay(10);
      delay_control += 10;
    }
    else {
      // Increment in 10ms tics
      delay(10);
      delay_control += 10;
      if (delay_control > config_in_ram.intermessage_pause*1000){
        delay_control = 0;
      }
    }
  }
}
