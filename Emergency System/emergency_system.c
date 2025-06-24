#include <reg52.h>
#include "lcd.h"
#include "SIM808.h"
#include "serial.h"
#include "interrupt.h"

#define NUMBER "+201092998552"

void delay();


int main(void) {
  lcd_init();
	lcd_clear();
	serial_init();
	clear_buffer();
	enable();
	
	disable_echo();
	delay();
	
	lcd_clear();
	enable_gnss();
	delay();
	
	lcd_clear();
	text_mode();
	delay();
	
	while(1) {
		if (flag_ex == 0) {
			lcd_clear();
			write_string("ACCIDENT");
			delay();
			send_sms(NUMBER, latitude, longitude);
			flag_ex = 1;
		}
		update_gnss();
		extract_gnss_data();
		delay();
		
		lcd_clear();
		write_date(datetime);
		delay();
		delay();
	
		lcd_clear();
		write_string(latitude);
		move_cursor_second_line();
		write_string(longitude);
		delay();
		delay();

	}
}

void delay() {
	int i;
	TH0 = 0X00;
	TL0 = 0X00;
	TR0 = 1;
	for (i =0; i < 10; i++) {
		while(TF0 == 0);
		TF0 = 0;
		TR0 = 1;
	}
	TF0 = 0;
	TR0 = 0;
	return;
}
