/* Copyright 2020 Laurence de Bruxelles
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
};

enum custom_keycodes {
    SY_KP_00,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_F1,  KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_NUBS, KC_BSPC, KC_DEL,  KC_PEQL, KC_PSLS, KC_PAST, KC_BRK,
        KC_F2,  KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,                          KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS,
        KC_F3,  KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_GRV,           KC_ENT,     KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS,
        KC_F4,  KC_LSFT, KC_LT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLASH, KC_ASTR, /*LSFT*/ KC_NLCK, KC_KP_1, KC_KP_2, KC_KP_3,
        KC_F5,           KC_CAPSLOCK,                    KC_SPACE,                          KC_ALGR,                            KC_KP_0, SY_KP_00,KC_KP_DOT, KC_KP_ENTER
    )
};

void keyboard_post_init_user(void) {
    writePin(SANYO_LED_GRAPH_PIN, !LED_PIN_ON_STATE);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LT:
            /* This key sends < if unshifted and > if shifted */
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    register_code(KC_DOT);
                    return false;
                } else {
                    return true;
                }
            } else {
                // rather than remembering which was pressed, just release both
                del_key(KC_COMM);
                del_key(KC_DOT);
                return true;
            }
            break;
        case KC_F1:
        case KC_F2:
        case KC_F3:
        case KC_F4:
        case KC_F5:
            /* The Sanyo has only 5 function keys; to get F6 through F10 you hold shift */
            if (get_mods() & MOD_MASK_SHIFT) {
                if (record->event.pressed) {
                    // tapping is easier than trying to make the shift hold logic work
                    del_mods(MOD_MASK_SHIFT);
                    tap_code(keycode + 5);
		    register_code(KC_LSFT);
                }
                return false;
            }
            return true;
        case SY_KP_00:
            /* This key is next to 0 on the numpad and types 0 twice! */
            if (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) { // if Num Lock is off this should probably do nothing
                if (record->event.pressed) {
                    register_code(KC_KP_0);
                    register_code(KC_KP_0);
                }
            }
            return false;
        case KC_KP_2:
        case KC_KP_5:
            /* On the Sanyo the down arrow is on the numpad 5 instead of the numpad 2 */
            if (!IS_HOST_LED_ON(USB_LED_NUM_LOCK)) { // this is the way
                if (keycode == KC_KP_5) {
                    if (record->event.pressed) {
                        register_code(KC_KP_2);
                    } else {
                        unregister_code(KC_KP_2);
                    }
                }
                return false;
            } else {
                return true;
            }
        case KC_ALGR:
            /* On the Sanyo the graph key is a locking modifier; when it is
             * active the alphanums produce 'graphical characters' which I'm
             * not sure were meant to look like, so instead we treat it as a
             * locking AltGr */
            if (record->event.pressed) {
                if (!(get_mods() & MOD_BIT(KC_ALGR))) {
                    register_code(KC_ALGR);
                    writePin(SANYO_LED_GRAPH_PIN, LED_PIN_ON_STATE);
                } else {
                    unregister_code(KC_ALGR);
                    writePin(SANYO_LED_GRAPH_PIN, !LED_PIN_ON_STATE);
                }
            }
            return false;
    }

    return true;
}
