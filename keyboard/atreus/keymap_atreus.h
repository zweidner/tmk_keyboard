// Phantom ANSI
static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* 0: workman */
    KEYMAP(                                                     \
           Q,   D,   R,   W,   B,  NO,   J,   F,   U,   P,SCLN, \
           A,   S,   H,   T,   G,  NO,   Y,   N,   E,   O,   I, \
           Z,   X,   M,   C,   V, ESC,   K,   L,COMM, DOT,SLSH, \
        CAPS,LALT,LCTL,LSFT, SPC, ENT,BSPC, FN0, FN1, FN0,LGUI  ),

    /* 1: number and arrows */
    KEYMAP(                                                     \
           1,   2,   3,   4,   5,  NO,   6,   7,   8,   9,   0, \
         TAB,LEFT,  UP,RGHT,LBRC,  NO,RBRC,TRNS,QUOT,MINS, EQL, \
        TRNS,PGUP,DOWN,PGDN,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,BSLS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS  ),

    /* 2: function layer*/
    KEYMAP(                                                     \
          F1,  F2,  F3,  F4,  F5,  NO,  F6,  F7,  F8,  F9, F10, \
        TRNS,MS_L,MS_U,MS_R,TRNS,  NO,TRNS,TRNS,TRNS, F11, F12, \
        TRNS,BTN2,MS_D,BTN1,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS  )

};
static const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_LAYER_MOMENTARY(2)
};
