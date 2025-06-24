#include <reg52.h>
#include "lcd.h"

//LCD Commands
#define clear 						0x01
#define home 							0x02
#define cur_dec 					0x04
#define cur_inc 					0x06
#define disp_shift_right 	0x05
#define disp_shift_left 	0x07
#define disp_off_cur_off 	0x08
#define disp_off_cur_on 	0x0A
#define disp_on_cur_off 0x0C
#define disp_on_cur_on 0x0E
#define disp_on_cur_blinking 0x0F
#define cur_shift_left 0x10
#define cur_shift_right 0x14
#define disp_full_shift_left 0x18
#define disp_full_shift_right 0x1C
#define cur_first_line 0x80
#define cur_second_line 0xC0
#define init 0x38


void lcd_init() {
	send_command(init);
  send_command(disp_on_cur_blinking);
  lcd_clear();
  move_cursor_first_line();
	return;
}

void lcd_clear() {
	send_command(clear);
	send_command(cur_first_line);
	return;
}

void move_cursor_first_line() {
	send_command(cur_first_line);
	return;
}

void move_cursor_second_line() {
	send_command(cur_second_line);
	return;
}

void send_command(unsigned char command) {
	lcd_data = command;
  rs = 0;
  rw = 0;
  en = 1;
  lcd_delay();
  en = 0;
	return;
}

void write_char(unsigned char character) {
  if (character == '\n' || character == '\r') {
		return;
	}
	lcd_data = character;
  rs = 1;
  rw = 0;
  en = 1;
  lcd_delay();
	en = 0;
	return;
}

void write_string(unsigned char *string) {
	while(*string != '\0') {
		write_char(*string++);
  }
	return;
}

void write_date(unsigned char *string) {
	unsigned char i;
	for (i = 0; i < 4; i++) {
		write_char(*string++);
	}
	write_char('/');
	
	for (i = 0; i < 2; i++) {
		write_char(*string++);
	}
	write_char('/');
	
	for (i = 0; i < 2; i++) {
		write_char(*string++);
	}
	
	move_cursor_second_line();
	
	for (i = 0; i < 2; i++) {
		if (i == 1) {
			write_char(*string++ + 2);
			continue;
		}
		write_char(*string++);
	}
	write_char(':');
	
	for (i = 0; i < 2; i++) {
		write_char(*string++);
	}	
}

void lcd_delay() {
	TMOD |= 0x09;
	TH0 = 0XAF;
	TL0 = 0X00;
	TR0 = 1;
	while(TF0 == 0);
	TF0 = 0;
	TR0 = 0;
	return;
}