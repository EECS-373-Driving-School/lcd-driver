/*
 * lcd.c
 *
 *  Created on: Apr 6, 2014
 *      Author: njurgens
 */

#include "lcd.h"
#include "drivers/mss_uart/mss_uart.h"

lcd_instance_t lcd1;

void LCD_init ( lcd_instance_t *this_lcd, mss_uart_instance_t *uart )
{
	this_lcd->uart = uart;

	MSS_UART_init (
			uart,
			LCD_BAUD_RATE,
			MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT
	);
}

void LCD_clear ( lcd_instance_t *this_lcd )
{
	uint8_t cmd[] = { 0x7c, 0x00 };

	MSS_UART_polled_tx(this_lcd->uart, cmd, sizeof(cmd));
}

void LCD_set_backlight ( lcd_instance_t *this_lcd, uint8_t duty_cycle )
{
	uint8_t cmd[] = { 0x7c, 0x02, duty_cycle };

	if (duty_cycle > 100)
		cmd[2] = 100;

	MSS_UART_polled_tx(this_lcd->uart, cmd, sizeof(cmd));
}

void LCD_set_cursor ( lcd_instance_t *this_lcd, uint8_t x, uint8_t y )
{
	uint8_t cmd[] = { 0x7c, 0x18, x, 0x7c, 0x19, y };

	MSS_UART_polled_tx(this_lcd->uart, cmd, sizeof(cmd));
}

void LCD_set_pixel ( lcd_instance_t *this_lcd, uint8_t x, uint8_t y, lcd_pixel_state_t state )
{
	uint8_t cmd[] = { 0x7c, 0x10, x, y, state };

	MSS_UART_polled_tx(this_lcd->uart, cmd, sizeof(cmd));
}

void LCD_print ( lcd_instance_t *this_lcd, const char *str )
{
	MSS_UART_polled_tx_string(this_lcd->uart, str);
}
