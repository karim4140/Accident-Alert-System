#include <reg52.h>
#include "lcd.h"
#include "SIM808.h"
#include "serial.h"

#define BUFFER_SIZE 56
#define DATETIME_OFFSET 14
#define LATITUDE_OFFSET 33
#define LONGITUDE_OFFSET 43

unsigned char serial_buffer[BUFFER_SIZE];
unsigned char latitude[11];
unsigned char longitude[12];
unsigned char datetime[19];

unsigned char	counter = 0;
unsigned char flag = 0;

void clear_buffer() {
	int i;
	for (i = 0; i < BUFFER_SIZE; i++) {
		serial_buffer[i] = '\0';
		counter = 0;
	}
	return;
}

void ISR_serial() interrupt 4 {
	if (RI == 1) {
		RI = 0;
		if (counter == 54) {
			serial_buffer[counter] = '\r';
			serial_buffer[counter+1] = '\0';
			return;
		} else if (counter > 54) {
			return;
		}
		if ((unsigned char)SBUF == '\r' || (unsigned char)SBUF == '\n') {
			if (counter > 0) {
				flag = 1;
			}
			return;
		}
		serial_buffer[counter] = (unsigned char)SBUF;
		counter++;
	}
	return;
}

void disable_echo() {
	clear_buffer();
	send_string(prefix);
	send_string(disable_echo_command);
	send_string(delimiter);
	
	while(1) {
		if (flag) {
			write_string("Disable Echo");
			move_cursor_second_line();
			write_string(serial_buffer);
			return;
		}
	}
}

void text_mode() {
	clear_buffer();
	send_string(prefix);
	send_string(select_SMS_message_format);
	send_char('1');
	send_string(delimiter);
	
	while(1) {
		if (flag) {
			write_string("Text Mode");
			move_cursor_second_line();
			write_string(serial_buffer);
			return;
		}
	}
}

void send_sms(unsigned char *number, unsigned char *latitude, unsigned char *longitude) {
	clear_buffer();
	write_string("Sending SMS...");
	
	move_cursor_second_line();
	send_string(prefix);
	send_string(send_SMS);
	send_char('"');
	send_string(number);
	send_char('"');
	send_string(delimiter);
	gsm_delay();
	send_string("Accident Occured at:\n");
	send_string(latitude);
	send_string(", ");
	send_string(longitude);
	send_char(SMS_delimiter);
	write_string("SMS Sent");	
	return;
}

void enable_gnss() {
	clear_buffer();
	send_string(prefix);
	send_string(gnss_power);
	send_char('1');
	send_string(delimiter);
	while(1) {
		if (flag) {
			write_string("Enable GNSS");
			move_cursor_second_line();
			write_string(serial_buffer);
			return;
		}
	}
}

void update_gnss() {
	clear_buffer();
	send_string(prefix);
	send_string(gnss_info);
	send_string(delimiter);
	while(1) {
		if (flag) {
			return;
		}
	}
}

void extract_gnss_data() {
	unsigned char i = 14;
	unsigned char comma = 0;
	gsm_delay();
	for (; i < counter; i++) {
		if (serial_buffer[i] == '\0') {
			datetime[i] = '\0';
			latitude[i] = '\0';
			longitude[i] = '\0';
			return;
		}
		if (serial_buffer[i] == ',') {
			comma++;
			continue;
		}
		switch (comma) {
			case 0:
				datetime[i - DATETIME_OFFSET] = serial_buffer[i];
				break;
			case 1:
				latitude[i - LATITUDE_OFFSET] = serial_buffer[i];
				break;
			case 2:
				longitude[i - LONGITUDE_OFFSET] = serial_buffer[i];
				break;
		}		
	}
	return;
}

void gsm_delay() {
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