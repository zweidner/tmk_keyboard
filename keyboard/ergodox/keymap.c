/*
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>

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
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "keycode.h"
#include "action.h"
#include "action_util.h"
#include "action_code.h"
#include "action_macro.h"
#include "action_layer.h"
#include "bootloader.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"
#include "ergodox.h"
#include "keymap_passwords.h"


/* ErgoDox keymap definition macro */
#define KEYMAP(                                                 \
                                                                \
    k0D,k0C,k0B,k0A,k09,k08,k07,                                \
    k1D,k1C,k1B,k1A,k19,k18,k17,                                \
    k2D,k2C,k2B,k2A,k29,k28,                                    \
    k3D,k3C,k3B,k3A,k39,k38,k37,                                \
    k4D,k4C,k4B,k4A,k49,                                        \
                            k58,k57,                            \
                                k59,                            \
                        k5A,k5B,k5C,                            \
                                                                \
        k06,k05,k04,k03,k02,k01,k00,                            \
        k16,k15,k14,k13,k12,k11,k10,                            \
            k25,k24,k23,k22,k21,k20,                            \
        k36,k35,k34,k33,k32,k31,k30,                            \
                k44,k43,k42,k41,k40,                            \
    k56,k55,                                                    \
    k54,                                                        \
    k51,k52,k53)                                                \
                                                                \
   /* matrix positions */                                       \
   {                                                            \
    { KC_##k00,KC_##k10,KC_##k20,KC_##k30,KC_##k40,KC_NO   },   \
    { KC_##k01,KC_##k11,KC_##k21,KC_##k31,KC_##k41,KC_##k51},   \
    { KC_##k02,KC_##k12,KC_##k22,KC_##k32,KC_##k42,KC_##k52},   \
    { KC_##k03,KC_##k13,KC_##k23,KC_##k33,KC_##k43,KC_##k53},   \
    { KC_##k04,KC_##k14,KC_##k24,KC_##k34,KC_##k44,KC_##k54},   \
    { KC_##k05,KC_##k15,KC_##k25,KC_##k35,KC_NO,   KC_##k55},   \
    { KC_##k06,KC_##k16,KC_NO,   KC_##k36,KC_NO,   KC_##k56},   \
                                                                \
    { KC_##k07,KC_##k17,KC_NO,   KC_##k37,KC_NO,   KC_##k57},   \
    { KC_##k08,KC_##k18,KC_##k28,KC_##k38,KC_NO,   KC_##k58},   \
    { KC_##k09,KC_##k19,KC_##k29,KC_##k39,KC_##k49,KC_##k59},   \
    { KC_##k0A,KC_##k1A,KC_##k2A,KC_##k3A,KC_##k4A,KC_##k5A},   \
    { KC_##k0B,KC_##k1B,KC_##k2B,KC_##k3B,KC_##k4B,KC_##k5B},   \
    { KC_##k0C,KC_##k1C,KC_##k2C,KC_##k3C,KC_##k4C,KC_##k5C},   \
    { KC_##k0D,KC_##k1D,KC_##k2D,KC_##k3D,KC_##k4D,KC_NO   }    \
   }

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KEYMAP(  // layer 0 : default
        // left hand
         EQL,   1,   2,   3,   4,   5, ESC,
         TAB,   Q,   W,   E,   R,   T,RBRC,
        BSPC,   A,   S,   D,   F,   G,
        LSFT,   Z,   X,   C,   V,   B, ESC,
        CAPS, GRV,LALT,LCTL,LSFT,
                                      LCTL, FN2,
                                           HOME,
                                  SPC, ENT, END,
        // right hand
              ESC,   6,   7,   8,   9,   0,MINS,
             LBRC,   Y,   U,   I,   O,   P,RBRC,
                     H,   J,   K,   L,SCLN,QUOT,
              FN1,   N,   M,COMM, DOT,SLSH,RSFT,
                        FN1,RCTL, FN1,RGHT,RGUI,
        RALT,RCTL,
        PGUP,
        PGDN,ENT,BSPC
    ),

    KEYMAP(  // layer 1 : function and symbol keys
        // left hand
        TRNS,F1,  F2,  F3,  F4,  F5,  F11,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN4,
        TRNS,TRNS,LEFT,  UP,RGHT,TRNS,
        TRNS,TRNS,PGUP,DOWN,PGDN,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
              F12,  F6,  F7,  F8,  F9, F10, FN0,
             TRNS,TRNS,TRNS,  UP,TRNS,TRNS,TRNS,
                  TRNS,LEFT,DOWN,RGHT,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // layer 2 : keyboard functions
        // left hand
        FN0, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             FN4, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // layer 3: numpad
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS,NLCK,PSLS,PAST,PAST,PMNS,BSPC,
             TRNS,NO,  P7,  P8,  P9,  PMNS,BSPC,
                  NO,  P4,  P5,  P6,  PPLS,PENT,
             TRNS,NO,  P1,  P2,  P3,  PPLS,PENT,
                       P0,  PDOT,SLSH,PENT,PENT,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // layer 4 : workman layer
        // left hand
         EQL,   1,   2,   3,   4,   5,   ESC,
         TAB,   Q,   D,   R,   W,   B,  LBRC,
        BSPC,   A,   S,   H,   T,   G,
        LSFT,   Z,   X,   M,   C,   V,   ESC,
        LGUI,GRV,LALT,LCTL,LSFT,
                                      LCTL ,FN4,
                                           HOME,
                                  SPC, ENT, END,
        // right hand
             FN3, 6,   7,   8,   9,   0,   MINS,
             RBRC,J,   F,   U,   P,   SCLN,RBRC,
                  Y,   N,   E,   O,   I,   QUOT,
             FN1, K,   L,   COMM,DOT, SLSH,RSFT,
                       FN3, FN5, RCTL,RALT,RGUI,
        RALT,RCTL,
        PGUP,
        PGDN,ENT,BSPC
    ),

    KEYMAP(  // layer 5 : function and symbol keys
        // left hand
        TRNS,  F1,  F2,  F3,  F4,  F5, F11,
        TRNS,   1,   2,   3,   4,   5,TRNS,
        TRNS, TAB,LEFT,  UP,RGHT,LBRC,TRNS,
             TRNS,PGDN,DOWN,PGUP,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
              F12,  F6,  F7,  F8,  F9, F10, FN0,
             TRNS,   6,   7,   8,   9,   0,TRNS,
                  RBRC,TRNS,QUOT,MINS, EQL,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,BSLS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // layer 6 : keyboard functions
        // left hand
        FN0, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,ACL0,ACL1,ACL2,TRNS,TRNS,
        TRNS,TRNS,MS_L,MS_U,MS_R,BTN1,
        TRNS,TRNS,WH_D,MS_D,WH_U,BTN2,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             FN4, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,FN6, FN7, FN8, FN9, FN10,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
};

/* id for user defined functions */
enum function_id {
    TEENSY_KEY,
};

enum macro_id {
    PASSWORD1,
    PASSWORD2,
    PASSWORD3,
    PASSWORD4,
    PASSWORD5,
};
/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
    ACTION_FUNCTION(TEENSY_KEY),                    // FN0 - Teensy key
    ACTION_LAYER_MOMENTARY(1),                      // FN1 - switch to Layer1
    ACTION_LAYER_SET(4, ON_PRESS),                  // FN2 - set Layer4
    ACTION_LAYER_MOMENTARY(5),                      // FN3 - switch to Layer5
    ACTION_LAYER_SET(0, ON_PRESS),                  // FN4 - set Layer0
    ACTION_LAYER_MOMENTARY(6),                      // FN5 - switch to Layer6
    ACTION_MACRO(PASSWORD1),                        // FN6 - password macro 1
    ACTION_MACRO(PASSWORD2),                        // FN7 - password macro 2
    ACTION_MACRO(PASSWORD3),                        // FN8 - password macro 3
    ACTION_MACRO(PASSWORD4),                        // FN9 - password macro 4
    ACTION_MACRO(PASSWORD5),                        // FN10 - password macro 5
};

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(250);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }
}


#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
#define FN_ACTIONS_SIZE (sizeof(fn_actions) / sizeof(fn_actions[0]))

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
    if (layer < KEYMAPS_SIZE) {
        return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
    } else {
        // fall back to layer 0
        return pgm_read_byte(&keymaps[0][(key.row)][(key.col)]);
    }
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    if (FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    } else {
        action.code = ACTION_NO;
    }
    return action;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch (id) {
            case PASSWORD1:     return MACRO_PASSWORD1;
            case PASSWORD2:     return MACRO_PASSWORD2;
            case PASSWORD3:     return MACRO_PASSWORD3;
            case PASSWORD4:     return MACRO_PASSWORD4;
            case PASSWORD5:     return MACRO_PASSWORD5;
        }
    }
    return MACRO_NONE;
}
