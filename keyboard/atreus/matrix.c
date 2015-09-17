/* Copyright 2012 Jun Wako <wakojun@gmail.com>
 *
 * This is heavily based on phantom/board.{c|h}.
 * https://github.com/BathroomEpiphanies/AVR-Keyboard
 *
 * Copyright (c) 2012 Fredrik Atmer, Bathroom Epiphanies Inc
 * http://bathroomepiphanies.com
 *
 * As for liscensing consult with the original files or its author.
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	0
#endif
static uint8_t debouncing = DEBOUNCE;

// bit array of key state(1:on, 0:off)
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

#ifndef SLEEP_LED_ENABLE
/* LEDs are on output compare pins OC1B OC1C
   This activates fast PWM mode on them.
   Prescaler 256 and 8-bit counter results in
   16000000/256/256 = 244 Hz blink frequency.
   LED_A: Caps Lock
   LED_B: Scroll Lock  */
/* Output on PWM pins are turned off when the timer 
   reaches the value in the output compare register,
   and are turned on when it reaches TOP (=256). */
static
void setup_leds(void)
{
    TCCR1A |=      // Timer control register 1A
        (1<<WGM10) | // Fast PWM 8-bit
        (1<<COM1B1)| // Clear OC1B on match, set at TOP
        (1<<COM1C1); // Clear OC1C on match, set at TOP
    TCCR1B |=      // Timer control register 1B
        (1<<WGM12) | // Fast PWM 8-bit
        (1<<CS12);   // Prescaler 256
    OCR1B = LED_BRIGHTNESS;    // Output compare register 1B
    OCR1C = LED_BRIGHTNESS;    // Output compare register 1C
    // LEDs: LED_A -> PORTB6, LED_B -> PORTB7
    DDRB  |= (1<<6) | (1<<7);
    PORTB  &= ~((1<<6) | (1<<7));
} 
#endif

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
 }

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    // To use PORTF disable JTAG with writing JTD bit twice within four cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);
	
    // initialize row and col
    unselect_rows();
    init_cols();
#ifndef SLEEP_LED_ENABLE
    setup_leds();
#endif

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++)  {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {  // 0-3
        select_row(row);
        _delay_us(3);       // without this wait it won't read stable value.
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[row] != cols) {
                matrix_debouncing[row] = cols;
                if (debouncing) {
                    dprint("bounce!: "); dprintf("%02X", debouncing); dprintln();
                }
                debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%02X: %032lb\n", row, bitrev32(matrix_get_row(row)));
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop32(matrix[i]);
    }
    return count;
}

/* Column pin configuration
 * col: 0   1   2   3   4   5   6   7   8   9   10 
 * pin: C7  C6  C5  A7  A6  A5  A4  A3  A2  A1  A0
 */
static void init_cols(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRA  |= 0b00000000; // PA: 
    PORTA |= 0b11111111;
//    DDRB  |= 0b00000000; // PB: 
//    PORTB |= 0b00000000;
    DDRC  |= 0b00000000; // PC: 
    PORTC |= 0b11100000;
//    DDRD  |= 0b00000000; // PD: 5 4 3 2 1 0
//    PORTD |= 0b00000000;
//    DDRE  |= 0b00000000; // PE: 
//    PORTE |= 0b00000000;
//    DDRF  |= 0b00000000; // PF: 6 5 4 1 0
//    PORTF |= 0b00000000;
}

static matrix_row_t read_cols(void)
{
    return (PINC&(1<<7) ? 0 : (1<<0)) |
           (PINC&(1<<6) ? 0 : (1<<1)) |
           (PINC&(1<<5) ? 0 : (1<<2)) |
           (PINA&(1<<7) ? 0 : (1<<3)) |
           (PINA&(1<<6) ? 0 : (1<<4)) |
           (PINA&(1<<5) ? 0 : (1<<5)) |
           (PINA&(1<<4) ? 0 : (1<<6)) |
           (PINA&(1<<3) ? 0 : (1<<7)) |
           (PINA&(1<<2) ? 0 : (1<<8)) |
           (PINA&(1<<1) ? 0 : (1<<9)) |
           (PINA&(1<<0) ? 0 : (1<<10));
}

/* Row pin configuration
 * row: 0   1   2   3 
 * pin: C3  C2  C1  C0 
 */
static void unselect_rows(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRC  &= ~0b00001111;
    PORTC |= 0b00001111;

}
static void select_row(uint8_t row)
{ 
    // Output low(DDR:1, PORT:0) to select
    switch(row) {
        case 0:
            DDRC  |= (1<<3);
            PORTC &= ~(1<<3);
            break;
        case 1:
            DDRC  |= (1<<2);
            PORTC &= ~(1<<2);
            break;
        case 2:
            DDRC  |= (1<<1);
            PORTC &= ~(1<<1);
            break;
        case 3:
            DDRC  |= (1<<0);
            PORTC &= ~(1<<0);
            break;
     }
} 
