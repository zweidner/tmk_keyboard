/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H


/* USB Device descriptor parameter */
#define VENDOR_ID       0x1337
#define PRODUCT_ID      0xBEEF
#define DEVICE_VER      0x9001
#define MANUFACTURER    t.m.k
#define PRODUCT         Atreus Keyboard

/* message strings */
#define DESCRIPTION     Atreus board

/* matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 11

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if need no debouncing */
#define DEBOUNCE    3

/* Set LED brightness 0-255.
 * This have no effect if sleep LED is enabled. */
#define LED_BRIGHTNESS  250

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* USART configuration
 *     asynchronous, 9600baud, 8-data bit, non parity, 1-stop bit, no flow control
 */
#ifdef __AVR_ATmega32U4__
    #define SERIAL_UART_BAUD       9600
    #define SERIAL_UART_DATA       UDR1
    #define SERIAL_UART_UBRR       ((F_CPU/(16UL*SERIAL_UART_BAUD))-1)
    #define SERIAL_UART_RXD_VECT   USART1_RX_vect
    #define SERIAL_UART_TXD_READY  (UCSR1A&(1<<UDRE1))
    #define SERIAL_UART_INIT()     do { \
        UBRR1L = (uint8_t) SERIAL_UART_UBRR;       /* baud rate */ \
        UBRR1H = (uint8_t) (SERIAL_UART_UBRR>>8);  /* baud rate */ \
        UCSR1B = (1<<TXEN1);                /* TX: enable */ \
        UCSR1C = (0<<UMSEL11) | (0<<UMSEL10) | /* Async USART*/\
                 (0<<UPM11) | (0<<UPM10) | /* parity: none(00), even(01), odd(11) */ \
                 (0<<UCSZ12) | (1<<UCSZ11) | (1<<UCSZ10); /* data-8bit(011) */ \
        UCSR1D = (1<<CTSEN) | (1<<RTSEN); \
        sei(); \
    } while(0)
#else
//#   error "USART configuration is needed."
#endif

#endif
