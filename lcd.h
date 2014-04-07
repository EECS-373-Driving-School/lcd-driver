/*
 * lcd.h
 *
 *  Created on: Apr 6, 2014
 *      Author: njurgens
 */

#ifndef LCD_H_
#define LCD_H_

#include "drivers/mss_uart/mss_uart.h"

#define LCD_BAUD_RATE MSS_UART_115200_BAUD

typedef enum {
	LCD_PIXEL_OFF = 0,
	LCD_PIXEL_ON = 1
} lcd_pixel_state_t;


typedef struct {
	mss_uart_instance_t *uart;
} lcd_instance_t;

extern lcd_instance_t lcd1;

void LCD_init ( lcd_instance_t*, mss_uart_instance_t* );

void LCD_clear ( lcd_instance_t* );

void LCD_set_backlight ( lcd_instance_t*, uint8_t duty_cycle );

void LCD_set_cursor ( lcd_instance_t*, uint8_t x, uint8_t y );

void LCD_set_pixel ( lcd_instance_t*, uint8_t x, uint8_t y, lcd_pixel_state_t );

void LCD_print ( lcd_instance_t*, const char* );

#endif /* LCD_H_ */
