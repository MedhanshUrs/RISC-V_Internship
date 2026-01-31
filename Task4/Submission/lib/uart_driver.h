#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <stdint.h>

void uart_init(uint32_t baud_rate);
void uart_send_char(char c);
void uart_send_string(const char *str);
char uart_receive_char(void);
uint8_t uart_char_available(void);


#endif
