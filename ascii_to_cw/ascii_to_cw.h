#define SEMAPHORE_WRAP(a,b) (b)

const char * AsciiToSemaphore[] = {
	SEMAPHORE_WRAP('NUL' , ""),         // 0x00
	SEMAPHORE_WRAP('SOH' , "-.-.-"),    // 0x01 Start of Header / ATTN Copy This
	SEMAPHORE_WRAP('STX' , "-.-.-"),    // 0x02 Start of Text / ATTN Copy This
	SEMAPHORE_WRAP('ETX' , ".-.-."),    // 0x03 End of Text / All Rendered AR
	SEMAPHORE_WRAP('EOT' , "...-.-"),   // 0x04 End of Transmission / SK
	SEMAPHORE_WRAP('ENQ' , ""),         // 0x05
	SEMAPHORE_WRAP('ACK' , "...-."),    // 0x06 Understood SN
	SEMAPHORE_WRAP('BEL' , "-.-.-"),    // 0x07 BELL / ATTN Copy THis
	SEMAPHORE_WRAP('BS' , "........"),  // 0x08 Backspace / ERROR HH
	SEMAPHORE_WRAP('HT' , ""),          // 0x09
	SEMAPHORE_WRAP('LF' , ".-.-"),      // 0x0A Line Feed / Newline AA
	SEMAPHORE_WRAP('VT' , "-...-"),     // 0x0B Vertical Tab / Begin Two BT
	SEMAPHORE_WRAP('FF' , ".-.-."),     // 0x0C Form Feed / All Rendered AR
	SEMAPHORE_WRAP('CR' , ".-.-"),      // 0x0D Carriage Return / Newline AA
	SEMAPHORE_WRAP('SO' , ""),          // 0x0E
	SEMAPHORE_WRAP('SI' , ""),          // 0x0F
	SEMAPHORE_WRAP('DLE' , ""),         // 0x10
	SEMAPHORE_WRAP('DC1' , ""),         // 0x11
	SEMAPHORE_WRAP('DC2' , ""),         // 0x12
	SEMAPHORE_WRAP('DC3' , ""),         // 0x13
	SEMAPHORE_WRAP('DC4' , ""),         // 0x14
	SEMAPHORE_WRAP('NAK' , ""),         // 0x15
	SEMAPHORE_WRAP('SYN' , ".-..."),    // 0x16 Synch / Wait AS
	SEMAPHORE_WRAP('ETB' , "-...-.-"),  // 0x17 End of Transaction Block / Back to You BK
	SEMAPHORE_WRAP('CAN' , ""),         // 0x18
	SEMAPHORE_WRAP('EM' , "-.-..-.."),  // 0x19 End of Medium / Closing CL
	SEMAPHORE_WRAP('SUB' , ""),         // 0x1A
	SEMAPHORE_WRAP(' ESC' , ""),        // 0x1B
	SEMAPHORE_WRAP(' FS' , ""),         // 0x1C
	SEMAPHORE_WRAP('GS' , ""),          // 0x1D
	SEMAPHORE_WRAP('RS' , ""),          // 0x1E
	SEMAPHORE_WRAP('US' , ""),          // 0x1F
	SEMAPHORE_WRAP('Space' , "   "),    // 0x20 Space (three beats)
	SEMAPHORE_WRAP('!' , "-.-.--"),     // 0x21
	SEMAPHORE_WRAP('"' , ".-..-."),     // 0x22
	SEMAPHORE_WRAP('#' , ""),           // 0x23
	SEMAPHORE_WRAP('$' , "...-..-"),    // 0x24
	SEMAPHORE_WRAP('%' , ""),           // 0x25
	SEMAPHORE_WRAP('&' , ".-..."),      // 0x26 &, AS
	SEMAPHORE_WRAP('\'' , ".----."),    // 0x27 " ' "
	SEMAPHORE_WRAP('(' , "-.--."),      // 0x28
	SEMAPHORE_WRAP(')' , "-.--.-"),     // 0x29
	SEMAPHORE_WRAP('*' , ""),           // 0x2A
	SEMAPHORE_WRAP('+' , ""),           // 0x2B
	SEMAPHORE_WRAP(',' , "--..--"),     // 0x2C
	SEMAPHORE_WRAP('-' , "-....-"),     // 0x2D
	SEMAPHORE_WRAP('.' , ".-.-.-"),     // 0x2E
	SEMAPHORE_WRAP('/' , "-..-."),      // 0x2F
	SEMAPHORE_WRAP('0' , "-----"),      // 0x30
	SEMAPHORE_WRAP('1' , ".----"),      // 0x31
	SEMAPHORE_WRAP('2' , "..---"),      // 0x32
	SEMAPHORE_WRAP('3' , "...--"),      // 0x33
	SEMAPHORE_WRAP('4' , "....-"),      // 0x34
	SEMAPHORE_WRAP('5' , "....."),      // 0x35
	SEMAPHORE_WRAP('6' , "-...."),      // 0x36
	SEMAPHORE_WRAP('7' , "--..."),      // 0x37
	SEMAPHORE_WRAP('8' , "---.."),      // 0x38
	SEMAPHORE_WRAP('9' , "----."),      // 0x39
	SEMAPHORE_WRAP(':' , "---..."),     // 0x3A
	SEMAPHORE_WRAP(';' , "-.-.-."),     // 0x3B
	SEMAPHORE_WRAP('<' , ""),           // 0x3C
	SEMAPHORE_WRAP('=' , "-...-"),      // 0x3D
	SEMAPHORE_WRAP('>' , ""),           // 0x3E
	SEMAPHORE_WRAP('?' , "..--.."),     // 0x3F
	SEMAPHORE_WRAP('@' , ".--.-."),     // 0x40
	SEMAPHORE_WRAP('A' , ".-"),         // 0x41
	SEMAPHORE_WRAP('B' , "-..."),       // 0x42
	SEMAPHORE_WRAP('C' , "-.-."),       // 0x43
	SEMAPHORE_WRAP('D' , "-.."),        // 0x44
	SEMAPHORE_WRAP('E' , "."),          // 0x45
	SEMAPHORE_WRAP('F' , "..-."),       // 0x46
	SEMAPHORE_WRAP('G' , "--."),        // 0x47
	SEMAPHORE_WRAP('H' , "...."),       // 0x48
	SEMAPHORE_WRAP('I' , ".."),         // 0x49
	SEMAPHORE_WRAP('J' , ".---"),       // 0x4A
	SEMAPHORE_WRAP('K' , "-.-"),        // 0x4B
	SEMAPHORE_WRAP('L' , ".-.."),       // 0x4C
	SEMAPHORE_WRAP('M' , "--"),         // 0x4D
	SEMAPHORE_WRAP('N' , "-."),         // 0x4E
	SEMAPHORE_WRAP('O' , "---"),        // 0x4F
	SEMAPHORE_WRAP('P' , ".--."),       // 0x50
	SEMAPHORE_WRAP('Q' , "--.-"),       // 0x51
	SEMAPHORE_WRAP('R' , ".-."),        // 0x52
	SEMAPHORE_WRAP('S' , "..."),        // 0x53
	SEMAPHORE_WRAP('T' , "-"),          // 0x54
	SEMAPHORE_WRAP('U' , "..-"),        // 0x55
	SEMAPHORE_WRAP('V' , "...-"),       // 0x56
	SEMAPHORE_WRAP('W' , ".--"),        // 0x57
	SEMAPHORE_WRAP('X' , "-..-"),       // 0x58
	SEMAPHORE_WRAP('Y' , "-.--"),       // 0x59
	SEMAPHORE_WRAP('Z' , "--.."),       // 0x5A
	SEMAPHORE_WRAP('[' , ""),           // 0x5B
	SEMAPHORE_WRAP('\\' , ""),          // 0x5C
	SEMAPHORE_WRAP(']' , ""),           // 0x5D
	SEMAPHORE_WRAP('^' , ""),           // 0x5E
	SEMAPHORE_WRAP('_' , "..--.-"),     // 0x5F
	SEMAPHORE_WRAP('`' , ""),           // 0x60
	SEMAPHORE_WRAP('a' , ".-"),         // 0x61
	SEMAPHORE_WRAP('b' , "-..."),       // 0x62
	SEMAPHORE_WRAP('c' , "-.-."),       // 0x63
	SEMAPHORE_WRAP('d' , "-.."),        // 0x64
	SEMAPHORE_WRAP('e' , "."),          // 0x65
	SEMAPHORE_WRAP('f' , "..-."),       // 0x66
	SEMAPHORE_WRAP('g' , "--."),        // 0x67
	SEMAPHORE_WRAP('h' , "...."),       // 0x68
	SEMAPHORE_WRAP('i' , ".."),         // 0x69
	SEMAPHORE_WRAP('j' , ".---"),       // 0x6A
	SEMAPHORE_WRAP('k' , "-.-"),        // 0x6B
	SEMAPHORE_WRAP('l' , ".-.."),       // 0x6C
	SEMAPHORE_WRAP('m' , "--"),         // 0x6D
	SEMAPHORE_WRAP('n' , "-."),         // 0x6E
	SEMAPHORE_WRAP('o' , "---"),        // 0x6F
	SEMAPHORE_WRAP('p' , ".--."),       // 0x70
	SEMAPHORE_WRAP('q' , "--.-"),       // 0x71
	SEMAPHORE_WRAP('r' , ".-."),        // 0x72
	SEMAPHORE_WRAP('s' , "..."),        // 0x73
	SEMAPHORE_WRAP('t' , "-"),          // 0x74
	SEMAPHORE_WRAP('u' , "..-"),        // 0x75
	SEMAPHORE_WRAP('v' , "...-"),       // 0x76
	SEMAPHORE_WRAP('w' , ".--"),        // 0x77
	SEMAPHORE_WRAP('x' , "-..-"),       // 0x78
	SEMAPHORE_WRAP('y' , "-.--"),       // 0x79
	SEMAPHORE_WRAP('z' , "--.."),       // 0x7A
	SEMAPHORE_WRAP('{' , ""),           // 0x7B
	SEMAPHORE_WRAP('|' , ""),           // 0x7C
	SEMAPHORE_WRAP('}' , ""),           // 0x7D
	SEMAPHORE_WRAP('~' , ""),           // 0x7E
	SEMAPHORE_WRAP('DEL' , "........")  // 0x7F Backspace / ERROR HH
};
