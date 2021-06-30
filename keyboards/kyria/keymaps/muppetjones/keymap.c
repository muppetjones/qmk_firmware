/* Copyright 2020 Stephen J. Bush
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
#include "features/casemodes.h"
#include "rgblight.h"
#include "features/encoder_mouse.h"

enum layers { _COLEDH = 0, _MOUSE, _LOWER, _RAISE, _NAV, _ADJUST };

/*
 * Custom Keys
 */

// Mod-tap
#define NAV_SPC LT(_NAV, KC_SPC)
#define LOW_SPC LT(_LOWER, KC_SPC)
#define RSE_ENT LT(_RAISE, KC_ENT)
#define RSE_TAB LT(_RAISE, KC_TAB)

// HYPER
#define HY_ESC HYPR_T(KC_ESC)

// Left-hand home row mods (colemak)
#define HR_A LGUI_T(KC_A)
#define HR_R LALT_T(KC_R)
#define HR_S LCTL_T(KC_S)
#define HR_T LSFT_T(KC_T)

// Right-hand home row mods (colemak)
#define HR_N RSFT_T(KC_N)
#define HR_E RCTL_T(KC_E)
#define HR_I LALT_T(KC_I)
#define HR_O RGUI_T(KC_O)

// for casemodes
enum custom_keycodes {
    CAPSWRD = SAFE_RANGE,
};

#ifdef ENCODER_ENABLE
void encoder_update_standard(uint8_t index, bool clockwise);
#endif

#ifdef RGBLIGHT_ENABLE
static rgblight_config_t home_rgb;

void set_rgb_home(void);
void set_rgb_by_layer(layer_state_t);
#endif

#ifdef TAP_DANCE_ENABLE
/*
 * TAP DANCE
 * https://docs.qmk.fm/#/feature_tap_dance
 */

// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE = 0,
    TD_UNKNOWN,
    TD_1X_TAP,
    TD_1X_HOLD,
    TD_2X_TAP,
    TD_4X_TAP,
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

enum {  // Our custom tap dance key; add any other tap dance keys to this enum
    TD_LAYERS = 0,
};
#    define TD_LYR TD(TD_LAYERS)

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void lyr_finished(qk_tap_dance_state_t *state, void *user_data);
void lyr_reset(qk_tap_dance_state_t *state, void *user_data);
#endif

/*
 * LAYERS
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
/*
 * Base Layer: Colemak DH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |CAPSWORD|   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |ESC/HYPR|   A  |   R  |  S   |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  |LShift|Leader|  | Del  | Tab  |   K  |   H  | ,  < | . >  | /  ? | Sft/Ent|
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | MUTE | Del  | Enter| Space| Enter|  | Bspc | Space| Hyper| Tab  | AltGr|
 *                        |      |      | Alt  | Lower| Raise|  |      | Nav  | Esc  | Raise|      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEDH] = LAYOUT(
        CAPSWRD, KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                        KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
        HY_ESC,  HR_A,    HR_R,    HR_S,    HR_T,    KC_G,                                        KC_M,    HR_N,    HR_E,    HR_I,    HR_O,    KC_QUOT,
        TD_LYR,  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_LSFT, KC_LEAD, KC_DEL,  KC_TAB,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,
                                   KC_MUTE, KC_DEL,  HY_ESC,  LOW_SPC, RSE_ENT, KC_BSPC, NAV_SPC, HY_ESC,  RSE_TAB, KC_RALT
    ),
    [_MOUSE] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 KC_BTN1, _______, _______, _______, _______, _______, _______, _______, _______, KC_BTN2
    ),
/*
 * Lower Layer: Numpad
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | / ?  | 7 &  | 8 *  | 9 (  | - _  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | GUI  | ALT  | CTL  | SFT  |      |                              | *    | 4 $  | 5 %  | 6 ^  | , <  | +      |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      | 0 )  | 1 !  | 2 @  | 3 #  | = +  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      | Lower|      |      |  |      | Nav  | 0    | .    |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_SLSH, KC_7,    KC_8,    KC_9, KC_ASTR, _______,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_MINS, KC_4,    KC_5,    KC_6, KC_COMM, KC_PLUS,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_1,    KC_2,    KC_3, KC_EQL,  _______,
                                 _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_DOT,  _______
    ),
/*
 * Raise Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                              |      |  &   |  €   |      |      |  \     |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                              |   _  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   +  |  =   |  ,   |  .   |  / ? | - _    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      | Lower|      |      |  |      | Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    // [_RAISE] = LAYOUT(
    //   _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                     _______, KC_AMPR, _______, _______, _______, KC_BSLS,
    //   _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                      KC_UNDS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
    //   _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, _______, _______, KC_PLUS, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
    //                              _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    // ),
    [_RAISE] = LAYOUT(
      _______, _______, _______, KC_GRV,  KC_GRV,  KC_BSLS,                                     _______, KC_LPRN, KC_RPRN, _______, _______, KC_BSLS,
      _______, _______, _______, KC_UNDS, KC_MINS, KC_TILD,                                     KC_UNDS, KC_LCBR, KC_RCBR, KC_ASTR, KC_PERC, KC_QUOT,
      _______, _______, _______, _______, KC_EQL,  _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_DOT,  KC_SLSH, KC_MINS,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Navigation Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | PgUp | Home | Up   | End  |      | ScrlLk |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | GUI  | ALT  | CTL  | SFT  |      |                              | PgDn | Left | Down | Up   | Right| CapsLk |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      | Lower|      |      |  |      | Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, KC_SLCK,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_CAPS,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    /*
     * Adjust Layer: Function keys, RGB
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * | RESET  |      |      |      |      |      |                              |      | F1   |  F2  | F3   | F4   |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      | F5   |  F6  | F7   | F8   |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      | F9   |  F10 | F11  | F12  |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_ADJUST] = LAYOUT(
        RESET,   _______, _______, _______, _______, _______,                                     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,
        _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, KC_F5,   KC_F6,   KC_F7,   KC_8,   _______,
        _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
    // /*
    //  * Layer template
    //  *
    //  * ,-------------------------------------------.                              ,-------------------------------------------.
    //  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
    //  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    //  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
    //  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
    //  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
    //  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    //  *                        |      |      |      |      |      |  |      |      |      |      |      |
    //  *                        |      |      |      |      |      |  |      |      |      |      |      |
    //  *                        `----------------------------------'  `----------------------------------'
    //  */
    //     [_LAYERINDEX] = LAYOUT(
    //       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
    //       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
    //       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    //     ),
    // clang-format on
};

/*
 *
 */

void keyboard_post_init_user(void) {
    // Call the keymap level matrix init.

#ifdef RGBLIGHT_ENABLE
    set_rgb_home();
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    set_rgb_by_layer(state);
#endif
    return state;
    // return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // capsword
    if (!process_case_modes(keycode, record)) {
        return false;
    }
    // Regular user keycode case statement
    switch (keycode) {
        case CAPSWRD:
            if (record->event.pressed) {
                toggle_caps_word();
            }
            return false;
        default:
            return true;
    }
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Regular user keycode case statement
    switch (keycode) {
#ifdef RGBLIGHT_ENABLE
        case RGB_HUD:
        case RGB_HUI:
        case RGB_SAD:
        case RGB_SAI:
        case RGB_VAD:
        case RGB_VAI:
            set_rgb_home();
            break;
#endif
        default:
            break;
    }
}

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
#    ifdef POINTING_DEVICE_ENABLE
    if (IS_LAYER_ON(_MOUSE))
        encoder_update_mouse(index, clockwise);
    else
#    endif
        encoder_update_standard(index, clockwise);
}

void encoder_update_standard(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
#endif

#ifdef RGBLIGHT_ENABLE

void set_rgb_home(void) {
    home_rgb.raw = eeconfig_read_rgblight();
    // these get the current -- not eeprom
    // home_rgb.hue = rgblight_get_hue();
    // home_rgb.sat = rgblight_get_sat();
    // home_rgb.val = rgblight_get_val();
}

void set_rgb_by_layer(layer_state_t state) {
    if (!rgblight_is_enabled()) {
        return;  // lighting not enabled
    }

    uint8_t offset = 0;
    switch (get_highest_layer(state)) {
        case _RAISE:
            offset = 2 * RGBLIGHT_HUE_STEP;
            break;
        case _LOWER:
            offset = -2 * RGBLIGHT_HUE_STEP;
            break;
        case _NAV:
            offset = 1 * RGBLIGHT_HUE_STEP;
            break;
        case _MOUSE:
            offset = -10 * RGBLIGHT_HUE_STEP;
            break;
        // case _ADJUST:  // layer color not recommended on layer w/ rgb keys
        //     offset = -96;
        //     break;
        default:  //  for any other layers, or the default layer
            break;
    }
    rgblight_sethsv_noeeprom((home_rgb.hue + offset) % 255, home_rgb.sat, home_rgb.val);
}
#endif

#ifdef TAP_DANCE_ENABLE
// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    switch (state->count) {
        case 1:
            if (!state->pressed)
                return TD_1X_TAP;
            else
                return TD_1X_HOLD;
        case 2:
            return TD_2X_TAP;
            break;
        case 4:
            return TD_4X_TAP;
            break;
        default:
            return TD_UNKNOWN;
    }
}

// Initialize tap structure associated with example tap dance key
static td_tap_t lyr_tap_state = {.is_press_action = true, .state = TD_NONE};

// Functions that control what our tap dance key does
void lyr_finished(qk_tap_dance_state_t *state, void *user_data) {
    lyr_tap_state.state = cur_dance(state);
    switch (lyr_tap_state.state) {
        case TD_1X_TAP:
            if (layer_state_is(_MOUSE))
                layer_off(_MOUSE);
            else
                layer_on(_MOUSE);
            break;
        case TD_1X_HOLD:
            layer_on(_ADJUST);
            break;
        case TD_2X_TAP:
            // Toggle lower layer
            if (layer_state_is(_LOWER))
                layer_off(_LOWER);
            else
                layer_on(_LOWER);
            break;
        case TD_4X_TAP:
            // Toggle lower layer
            if (layer_state_is(_ADJUST))
                layer_off(_ADJUST);
            else
                layer_on(_ADJUST);
            break;
        default:
            break;
    }
}

void lyr_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (lyr_tap_state.state == TD_1X_HOLD) {
        layer_off(_ADJUST);
    }
    lyr_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[1] = {[TD_LAYERS] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, lyr_finished, lyr_reset, 275)};
#endif
