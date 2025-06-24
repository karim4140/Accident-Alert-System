#include <reg52.h>
#include "interrupt.h"
#include "lcd.h"
unsigned char flag_ex = 1;
void ISR_external() interrupt 0 {
	flag_ex = 0;
	return;
}

void enable() {
	EA = 1;
	ES = 1;
	EX0 = 1;
	IT0 = 1;
}