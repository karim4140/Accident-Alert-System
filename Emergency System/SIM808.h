#include <reg52.h>

#define prefix 											"AT"
#define disable_echo_command 				"E0"
#define select_SMS_message_format		"+CMGF="
#define send_SMS 										"+CMGS="
#define gnss_power 									"+CGNSPWR="
#define gnss_info 									"+CGNSINF"
#define delimiter 									"\r\n"
#define SMS_delimiter 							0x1A // CTRL + Z OR ESC

extern unsigned char latitude[11];
extern unsigned char longitude[12];
extern unsigned char datetime[19];

void disable_echo();
void text_mode();
void send_sms(unsigned char *number, unsigned char *latitude, unsigned char *longitude);
void enable_gnss();
void update_gnss();
void extract_gnss_data();
void clear_buffer();
void gsm_delay();