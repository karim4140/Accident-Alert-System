#include <reg52.h>

#define lcd_data P2

sbit rs=P0^0;
sbit rw=P0^1;
sbit en=P0^2;

void lcd_init();
void send_command(unsigned char command);
void write_char(unsigned char character);
void write_string(unsigned char *string);
void write_date(unsigned char *string);
void move_cursor_first_line();
void move_cursor_second_line();
void lcd_clear();
void lcd_delay();