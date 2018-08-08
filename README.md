# Arduino_CWBeacon
Configurable CW Beacon with PTT and Keyer output
C. Howe / AA0CN, 2018
See LICENSE text file

This is an automated keyer project. It can be used to send periodic CW/Morse messages
with configurable speed, delay, and message. Configuration can be done by Serial Port,
and configuration can be saved to the device such that it automatically starts with
saved configuration on next power-on.
The device can be configured to key output pins, relays, optocouplers, or other
outputs directly with the morse key (on/off) and the PTT (transmit enable) signals.
This can be hooked up to radios, buzzers, lights, or other equiptment to repeatedly
signal the desired message at the set speed and interval indefinitely.


Hardware Configuration:
An Arduino Uno, Nano, or Similar Atmel Atmega328-based processor can be used.
Code could be ported to other platforms.
For Arduino-type devices, TLL-Level output pins can be used to drive PC817 Optocouplers
through 330 Ohm resistors like so:

OUTPUT PIN ----
              |
              |
              R = 330Ohm
              |          _______ KEY / PTT
              \      |  /
              _|_  ~ | /
             _\_/_ ~ |<      PC817 Optocoupler
               |   ~ | \
              /      | _\|______ RADIO GND
   |----------
 --+--  
  -+- GND
   +
   
>>> The message will be displated as transmitted Dits/Dahs and the ASCII character in the 
Serial output, as well as the LED on Arduino devices (unless otherwise modified)

>>> At Power On, the device will start automatically with the previous
default configuration (if saved to EEPROM)
>>> The User/Controller may modify the configuration or monitor the
operation of the CW Beacon via a Serial Port/UART, with the following
configuration: 9600 Baud, 8 Data Bits, 1 Stop Bit, No Pairity.
>>> On Reset or Power On, the following information will be displayed
from EEPROM/Default and keying will start automatically.

>>> On first load, EEPROM restore will not find a saved configuration.
If no previous EEPROM configuration is set, the default configuration
of a fresh install is a 10WPM message of 'VVV', every 5 seconds.

--------------------------------
- - -   AA0CN CW BEACON    - - -
--------------------------------
- - -  Version 1.00, 2017  - - -
  OUT:         PIN D2
  OUT Inverse: PIN D7
  PTT:         PIN D3
  PTT Inverse: PIN D8
--------------------------------
EEPROM Configuration restored!

 Press [ENTER] to Configure, [P] for Pins/Info
Message:
CQ TEST CQ TEST DE AA0CN AA0CN K

C : -.-.
Q : --.-
  :
T : -
E : .
S : ...
T : -


>>> Pressing [ENTER] will enter Configuration Mode. This is the user interface
where the user may change the current configuration and save or restore from EEPROM.
>>> Pressing 'D' or [ENTER] will return to Run mode
>>> Pressing 'S' will save the current configuration as Default in EEPROM
>>> Pressing 'T' will toggle the TX/PTT Relay on Pin 3 (as well as its inverse)
>>> Pressing 'W' allows the User to change the WPM rate of CW keying
>>> Pressing 'I' allows the User to change the intermessage delay, in seconds. (min, 1, max 32767)
>>> Pressing 'E' allows the User to set a new message, to a max of 239 characters

=== Config Mode ===
(D) Done (or Enter)
(S) Save as Default
(T) TX/PTT Relay (TTL Pin 3) = Off
(W) WPM = 15
(I) Intermessage Delay, Seconds = 5
(E) Edit Message :
CQ TEST CQ TEST DE AA0CN AA0CN K
================================================================================




>>> When in Run mode, pressing 'P' will Pause TX and also display Pin info
>>> Pin info is set by compile-time #defines at the top of cw_beacon.ino

- - -  Version 1.00, 2017  - - -
  OUT:         PIN D2
  OUT Inverse: PIN D7
  PTT:         PIN D3
  PTT Inverse: PIN D8
--------------------------------

Press any key to continue...

>>> Pressing any key will return to Run mode.



---------------------------------------------------------------
Contact AA0CN with any updates, questions, bugs, or uses!
https://github.com/AA0CN/Arduino_CWBeacon
