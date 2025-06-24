#include <reg52.h>
#include "serial.h"

// Generate 9600 baudrate 
void serial_init() {
	SM0 = 0;
	SM1 = 1;
	SM2 = 0;
	REN = 1;
  TMOD |= 0x20;
  TH1 = 0xFD;
  TL1 = 0xFD;
  TR1 = 1;
	return;
}

// Sends a character via serial
void send_char(unsigned char character) {
	SBUF = character;
	while (TI == 0) {	
	}
	TI = 0;
	return;
}

// Sends a string via serial
void send_string(unsigned char *string) {
	while(*string != '\0') {
		send_char(*string++);
  }
	return;
}