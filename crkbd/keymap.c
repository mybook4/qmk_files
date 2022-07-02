// Adapted from Soundmonster's keymap.c

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
static uint32_t oled_refresh_timer = 0;
#endif

static uint8_t keylog_enabled = 0;
static uint32_t keylog_interkey_timer = 0;
#define KEYLOG_LEN 71
char keylog_str[KEYLOG_LEN] = {};

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  _COLEMAKMODDH,
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum custom_keycodes {
  COLEMAKMODDH = SAFE_RANGE,
  QWERTY,
  LOWER_ENT,
  RAISE_QUOT,
  ADJUST,
  RGBRST,
  KEYLOG_TOG
};

// keeps track of current base layer
static int mybaselayer = COLEMAKMODDH;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAKMODDH] = LAYOUT(
  //,-----------------------------------------------.                ,---------------------------------------------------.
     KC_TAB,        KC_Q,  KC_W,  KC_F,  KC_P,  KC_B,                   KC_J,  KC_L,  KC_U,  KC_Y,       KC_SCLN, KC_BSPC,
  //|------+------------+------+------+------+------|                |------+------+-------+------+-------------+--------|
    KC_RCPC,        KC_A,  KC_R,  KC_S,  KC_T,  KC_G,                   KC_M,  KC_N,  KC_E,  KC_I,          KC_O, KC_QUOT,
  //|------+------------+------+------+------+------|                |------+------+-------+------+-------------+--------|
    KC_LSPO,LSFT_T(KC_Z),  KC_X,  KC_C,  KC_D,  KC_V,                   KC_K,  KC_H,KC_COMM,KC_DOT,RSFT_T(KC_SLSH),KC_ENT,
  //|------+------------+------+------+------+------+------|  |------+------+------+-------+------+-------------+--------|
                        KC_LGUI, LCTL_T(KC_BSPC), LOWER_ENT,   RAISE_QUOT, RCTL_T(KC_SPC), KC_LALT
                                    //`--------------------'  `--------------------'
  ),


  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------.                ,---------------------------------------------------.
     KC_TAB,        KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                   KC_Y,  KC_U,  KC_I,  KC_O,          KC_P, KC_BSPC,
  //|------+------------+------+------+------+------|                |------+------+-------+------+-------------+--------|
    KC_RCPC,        KC_A,  KC_S,  KC_D,  KC_F,  KC_G,                   KC_H,  KC_J,  KC_K,  KC_L,       KC_SCLN, KC_QUOT,
  //|------+------------+------+------+------+------|                |------+------+-------+------+-------------+--------|
    KC_LSPO,LSFT_T(KC_Z),  KC_X,  KC_C,  KC_V,  KC_B,                   KC_N,  KC_M,KC_COMM,KC_DOT,RSFT_T(KC_SLSH),KC_ENT,
  //|------+------------+------+------+------+------+------|  |------+------+------+-------+------+-------------+--------|
                        KC_LGUI, LCTL_T(KC_BSPC), LOWER_ENT,   RAISE_QUOT, RCTL_T(KC_SPC), KC_LALT
                                    //`--------------------'  `--------------------'
  ),        

  [_LOWER] = LAYOUT(
  //,----------------------------------------------.                ,-----------------------------------------.
     KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,  KC_7,  KC_8,  KC_9,   KC_0,KC_BSPC,
  //|------+-------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    KC_LCTL,KC_TAB ,KC_HOME,  KC_UP, KC_END,KC_PGUP,                 KC_EQL,  KC_4,  KC_5,  KC_6,KC_ASTR,KC_MINS,
  //|------+-------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    KC_LSFT,KC_LSFT,KC_LEFT,KC_DOWN,KC_RIGHT,KC_PGDN,               KC_PLUS,  KC_1,  KC_2,  KC_3,KC_SLSH,KC_ENT,
  //|------+-------+-------+-------+-------+-------+------|  |------+------+------+------+------+------+------|
                        KC_LGUI, LCTL_T(KC_BSPC), LOWER_ENT,   RAISE_QUOT, RCTL_T(KC_0), LALT_T(KC_DOT)
                                   //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT(
  //,-----------------------------------------.                ,-----------------------------------------.
     KC_ESC,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_PERC,             KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LCTL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                KC_EQL,KC_MINS,KC_LCBR,KC_RCBR,KC_PIPE,KC_GRV,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LSFT, KC_F6, KC_F7, KC_F8, KC_F9,KC_F10,               KC_PLUS,KC_UNDS,KC_LBRC,KC_RBRC,KC_BSLS,KC_TILD,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                        KC_ESC, LCTL_T(KC_DEL), LOWER_ENT,   RAISE_QUOT, RCTL_T(KC_SPC), KC_LALT
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT(
  //,-----------------------------------------.                ,-----------------------------------------.
      RESET, KC_ESC,RGB_MOD,RGB_TOG, RGBRST, QWERTY,     COLEMAKMODDH,KC_PSCR,KC_CALC, KC_F11, KC_F12, DEBUG,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,RGB_SPI,KC_NO,            KC_WH_U,KC_BTN1,KC_MS_U,KC_BTN2, KC_QUOT, KEYLOG_TOG,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,RGB_SPD,KC_NO,            KC_WH_D,KC_MS_L,KC_MS_D,KC_MS_R, KC_ACL2, RGB_RMOD,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                        KC_LGUI, LCTL_T(KC_BSPC), LOWER_ENT,   RAISE_QUOT, RCTL_T(KC_SPC), KC_RALT
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}


#define CUBE_ANI_NUM_FRAMES 9

void render_logo(void) {
    static uint16_t currentFrame = 0;

    static const char PROGMEM cubeAni[CUBE_ANI_NUM_FRAMES][11] = {

        // frame 1
        { 0x01, 0x02, 0x20, 0x01, 0x02, 
          0x03, 0x04, 0x20, 0x03, 0x04, 0 },

        // frame 2
        { 0x05, 0x06, 0x20, 0x05, 0x06, 
          0x07, 0x08, 0x20, 0x07, 0x08, 0 },

        // frame 3
        { 0x09, 0x0b, 0x20, 0x09, 0x0b,
          0x0c, 0x0e, 0x20, 0x0c, 0x0e, 0 },

        // frame 4
        { 0x0f, 0x10, 0x20, 0x0f, 0x10,
          0x11, 0x12, 0x20, 0x11, 0x12, 0 },

        // frame 5
        { 0x13, 0x14, 0x20, 0x13, 0x14,
          0x15, 0x16, 0x20, 0x15, 0x16, 0 },

        // frame 6
        { 0x17, 0x18, 0x20, 0x17, 0x18,
          0x19, 0x1a, 0x20, 0x19, 0x1a, 0 },

        // frame 7
        { 0x1b, 0x1c, 0x20, 0x1b, 0x1c,
          0x1d, 0x1e, 0x20, 0x1d, 0x1e, 0 },

        // frame 8
        { 0x1f, 0xc0, 0x20, 0x1f, 0xc0,
          0xc1, 0xc2, 0x20, 0xc1, 0xc2, 0 },

        // frame 9
        { 0xc3, 0xd1, 0x20, 0xc3, 0xd1,
          0xd2, 0xd3, 0x20, 0xd2, 0xd3, 0 }

    };


    if(currentFrame == CUBE_ANI_NUM_FRAMES) {
        currentFrame = 0;
    }

    oled_write_P(cubeAni[currentFrame], false);
    oled_write_P(cubeAni[currentFrame], false);

    currentFrame++;
}


void render_layer_state(void) {

    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};

    if(layer_state_is(_ADJUST)) {
        oled_write_P(adjust_layer, false);

    } else if(layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);

    } else if(layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);

    } else {
        oled_write_P(default_layer, false);
    }
}

void render_default_layer_name(void) {
    // State the default layer we're using
    if(COLEMAKMODDH == mybaselayer) {
        oled_write_P(PSTR("ModDH\n"), false);
    } else {
        oled_write_P(PSTR("qwert\n"), false);
    }
}


void render_keylog_enable_state(void) {
    if(keylog_enabled) {
        oled_write_P(PSTR("KL 1 \n"), false);
    } else {
        oled_write_P(PSTR("KL 0 \n"), false);
    }
}


void render_keylog(void) {
    // print the contents of the keylog
    oled_write(keylog_str, false);
}


void render_status_main(void) {
    oled_set_brightness(50);

    if(keylog_enabled) {
        oled_clear();
        oled_write_P(PSTR("KLog:\n"), false);
        render_keylog();

    } else {
        render_logo();
        render_layer_state();
        render_default_layer_name();
        render_keylog_enable_state();
        render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
        render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
    }
}

void render_status_secondary(void) {
    oled_set_brightness(50);
    render_logo();
    render_layer_state();
    render_default_layer_name();
    render_keylog_enable_state();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 20000) {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else { oled_on(); }
#endif

    // We limit OLED framerate to 10 fps to keep matrix scan frequency high
    if (timer_elapsed32(oled_refresh_timer) < 100) {
        return;  // skip refreshing the OLED display contents
    }

    oled_refresh_timer = timer_read32();  // update the refresh timer value after having refreshed the displays

    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }

}

#endif

#define CODE_TO_NAME_LEN 60
const char code_to_name[CODE_TO_NAME_LEN] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};


void add_to_keylog(uint16_t keycode) {

    static uint8_t keylog_str_idx = 0;

//uprintf("Keycode udec in add_to_keylog: %u\n", keycode);
    
    if (timer_elapsed32(keylog_interkey_timer) > 10000) {
        // if the interkey timeout is exceeded, we clear the log
        memset(keylog_str, '\0', KEYLOG_LEN);
        keylog_str_idx = 0;
    }

    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    if (keylog_str_idx == (KEYLOG_LEN-1)) {
        keylog_str_idx = 0; // wrap they keylog around
    }


    if (keycode < CODE_TO_NAME_LEN) {
        keylog_str[keylog_str_idx] = code_to_name[keycode];
        // only reset the timer and increment the keylog position if we actually added something to the log
        keylog_interkey_timer = timer_read32();
        keylog_str_idx++;
    }

}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

//uprintf("Keycode udec in process_record_user: %u, pressed: %u\n", keycode, record->event.pressed);

  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
#endif
    if (keylog_enabled) {
        add_to_keylog(keycode);
    }

    // set_timelog();
  }

  static uint16_t lower_ent_timer;
  static uint16_t raise_quot_timer;

  switch (keycode) {
    case LOWER_ENT:
      if (record->event.pressed) {
        lower_ent_timer = timer_read();
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        if(timer_elapsed(lower_ent_timer) < TAPPING_TERM) {
          //SEND_STRING("\n");
          tap_code(KC_ENT);
        }
      }
      return false;
    case RAISE_QUOT:
      if (record->event.pressed) {
        raise_quot_timer = timer_read();
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        if(timer_elapsed(raise_quot_timer) < TAPPING_TERM) {
          //SEND_STRING(" ");
          tap_code(KC_QUOT);
        }
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case QWERTY:
        if (record->event.pressed) {
            mybaselayer = QWERTY;
            layer_on(_QWERTY);  
        }
        return false;
        break;
    case COLEMAKMODDH:
        if (record->event.pressed) {
            mybaselayer = COLEMAKMODDH;
            layer_off(_QWERTY);  // all we need to do is turn off _QWERTY, since _COLEMAKMODDH is the default layer 
        }
        return false;
        break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      #ifdef RGB_MATRIX_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
          rgb_matrix_enable();
        }
      #endif
      break;
    case KEYLOG_TOG:
      if (record->event.pressed) {
          keylog_enabled ^= 1;  // toggle they keylogger
      }
      break;
  }
  return true;
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif
