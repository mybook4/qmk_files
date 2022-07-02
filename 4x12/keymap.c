#include QMK_KEYBOARD_H

enum layers {
    _COLEMAKMODDH,
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAKMODDH] = LAYOUT_ortho_4x12(
    KC_ESC,                  KC_Q,    KC_W,    KC_F,            KC_P,              KC_B,       KC_J,                  KC_L,    KC_U,      KC_Y,        KC_SCLN,  KC_BSPC,
    LCTL_T(KC_TAB),          KC_A,    KC_R,    KC_S,            KC_T,              KC_G,       KC_M,                  KC_N,    KC_E,      KC_I,           KC_O,  KC_QUOT,
    KC_LSPO,                 KC_Z,    KC_X,    KC_C,            KC_D,              KC_V,       KC_K,                  KC_H, KC_COMM,    KC_DOT,        KC_SLSH,  KC_RSPC,
  //KC_RCTL,              KC_LGUI, KC_RALT, KC_PIPE,         KC_BSPC, LT(_LOWER,KC_ENT), LT(_RAISE,KC_QUOT),        KC_SPC,  KC_DOT, KC_PGDOWN,        KC_PGUP,  KC_ENT
    KC_RCTL,              KC_PIPE, KC_LALT, KC_LGUI,         KC_BSPC, LT(_LOWER,KC_ENT), LT(_RAISE,KC_QUOT),        KC_SPC, KC_RALT, KC_PGDOWN,        KC_PGUP,  KC_ENT
  ),

  [_QWERTY] = LAYOUT_ortho_4x12(
    KC_ESC,                  KC_Q,    KC_W,    KC_E,            KC_R,             KC_T,              KC_Y,       KC_U,    KC_I,      KC_O,           KC_P, KC_BSPC,
    LCTL_T(KC_TAB),          KC_A,    KC_S,    KC_D,            KC_F,             KC_G,              KC_H,       KC_J,    KC_K,      KC_L,        KC_SCLN, KC_QUOT,
    KC_LSPO,                 KC_Z,    KC_X,    KC_C,            KC_V,             KC_B,              KC_N,       KC_M, KC_COMM,    KC_DOT,        KC_SLSH, KC_RSPC,
  //KC_RCTL,              KC_LGUI, KC_RALT, KC_PIPE,         KC_BSPC,LT(_LOWER,KC_ENT),LT(_RAISE,KC_QUOT),     KC_SPC,  KC_DOT, KC_PGDOWN,        KC_PGUP,  KC_ENT
    KC_RCTL,              KC_PIPE, KC_LALT, KC_LGUI,         KC_BSPC, LT(_LOWER,KC_ENT), LT(_RAISE,KC_QUOT),   KC_SPC, KC_RALT, KC_PGDOWN,        KC_PGUP,  KC_ENT
  ),

  [_LOWER] = LAYOUT_ortho_4x12(
    KC_ESC,            KC_1,    KC_2,    KC_3,      KC_4,    KC_5,          KC_6,        KC_7,   KC_8,   KC_9,    KC_0,  KC_BSPC,
    LCTL_T(KC_TAB),  KC_TAB, KC_HOME,   KC_UP,    KC_END, KC_PGUP,        KC_EQL,        KC_4,   KC_5,   KC_6, KC_ASTR,  KC_MINS,
   KC_LSPO,         KC_LSFT, KC_LEFT, KC_DOWN,  KC_RIGHT, KC_PGDN,       KC_PLUS,        KC_1,   KC_2,   KC_3, KC_SLSH,  KC_RSPC,
 //KC_RCTL,         KC_LGUI, KC_RALT, KC_PIPE, KC_BSPC, KC_NO,       DF(_QWERTY),       KC_0, KC_DOT,KC_PGDOWN,KC_PGUP,  KC_ENT
   KC_RCTL,         KC_PIPE, KC_LALT, KC_LGUI, KC_BSPC, KC_NO,       DF(_QWERTY),       KC_0, KC_DOT,KC_PGDOWN,KC_PGUP,  KC_ENT
  ),

  [_RAISE] = LAYOUT_ortho_4x12(
  KC_ESC,  KC_EXLM,   KC_AT, KC_HASH,  KC_DLR,           KC_PERC,       KC_CIRC, KC_AMPR,  KC_ASTR,  KC_LPRN, KC_RPRN,  KC_DEL,
   KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,             KC_F6,       KC_EQL,  KC_MINS,  KC_LCBR,  KC_RCBR, KC_PIPE,  KC_GRV,
   KC_F7,    KC_F8,   KC_F9,  KC_F10,  KC_F11,            KC_F12,       KC_PLUS, KC_UNDS,  KC_LBRC,  KC_RBRC, KC_BSLS, KC_TILD,
//KC_RCTL, KC_LGUI, KC_RALT, KC_PIPE, KC_BSPC, DF(_COLEMAKMODDH),       KC_NO,    KC_SPC,  KC_DOT, KC_PGDOWN, KC_PGUP,  KC_ENT
  KC_RCTL, KC_PIPE, KC_LALT, KC_LGUI, KC_BSPC, DF(_COLEMAKMODDH),       KC_NO,    KC_SPC,  KC_DOT, KC_PGDOWN, KC_PGUP,  KC_ENT
  )

};



