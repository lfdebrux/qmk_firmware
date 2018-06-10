
// Default ECO Layout
// KLE here : http://www.keyboard-layout-editor.com/#/gists/0733eca6b4cb88ff9d7de746803f4039

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FN 2

enum eco_keycodes {
  QWERTY = SAFE_RANGE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define FN MO(_FN)

// Mix together our modifiers and tap keys
#define LT_TAB LT(_FN, KC_TAB)
#define LT_SPC LT(_FN, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-------------------------------------------------------------------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |   [  |   ]  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |LT_Tab|   A  |   S  |   D  |   F  |   G  |   \  |   '  |   H  |   J  |   K  |   L  |   ;  | Enter|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   `  |   Z  |   X  |   C  |   V  |   -  |   /  |   B  |   N  |   M  |   ,  |   .  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |  FN  | Ctrl | Alt  |  GUI | Space| Space| Ctrl |  GUI | Space| Space| Left | Right| Down |  Up  |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    LT_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_BSLS, KC_QUOT, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LSFT, KC_GRAVE,KC_Z,    KC_X,    KC_C,    KC_V,    KC_MINS, KC_SLSH, KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT,
    FN,      KC_LCTL, KC_LALT, KC_LGUI, LT_SPC,  LT_SPC,  KC_RCTL, KC_RGUI, LT_SPC,  LT_SPC,  KC_LEFT, KC_RGHT, KC_DOWN, KC_UP
  ),

  /* FN1
   * ,-------------------------------------------------------------------------------------------------.
   * | Esc  |   !  |   @  |   £  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   _  |   +  | Del  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Tab  |   1  |   2  |   3  |   4  |   5  |   -  |   @  |   6  |   7  |   8  |   9  |   0  | Enter|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |   =  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Home | End  | PgDn | PgUp |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_FN] = LAYOUT(
    KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS, _______,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_AT,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, _______, _______, _______, _______, _______, KC_EQL,  _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END,  KC_PGDN, KC_PGUP
  )

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
  }
  return true;
}
