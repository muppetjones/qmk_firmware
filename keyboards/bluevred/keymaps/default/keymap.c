/* Copyright 2021 Stephen Bush <@muppetjones>
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

/** Layers
 *
 */
enum layers {
    _CLMKDH = 0,
    _QWERTY,
    _LOWER,
    _RAISE,
    _NAV,
    _MEDIA,
    _ADJUST,
};

/** Keycodes
 *
 */

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

// Left-hand home row mods (qwerty)
#define HRQ_A LGUI_T(KC_A)
#define HRQ_S LALT_T(KC_S)
#define HRQ_D LCTL_T(KC_D)
#define HRQ_F LSFT_T(KC_F)

// Right-hand home row mods (qwerty)
#define HRQ_J RSFT_T(KC_J)
#define HRQ_K RCTL_T(KC_K)
#define HRQ_L LALT_T(KC_L)
#define HRQ_QUOT RGUI_T(KC_QUOT)

// Layer tap-mods
#define ADJ_TAB LT(_ADJUST, KC_TAB)
#define LOW_ENT LT(_LOWER, KC_ENT)
#define MED_BSP LT(_MEDIA, KC_BSPC)
#define NAV_SPC LT(_NAV, KC_SPC)
#define RAI_DEL LT(_RAISE, KC_DEL)

// Layer keycodes
enum custom_keycodes {
    CLMK_DH = SAFE_RANGE,
    QWERTY,
};

/** Keymap
 *
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
/* Layer Template
 * ,----------------------------------.                ,----------------------------------.
 * |      |      |      |      |      |                |      |      |      |      |      |
 * |------+------+------+------+------|                |------+------+------+------+------|
 * |      |      |      |      |      |                |      |      |      |      |      |
 * |------+------+------+------+------|                |------+------+------+------+------|
 * |      |      |      |      |      |                |      |      |      |      |      |
 * `--------------------+------+------+------.  ,------+------+---------------------------'
 *                      |      |      |      |  |      |      |      |
 *                      `--------------------'  `--------------------'
 */
// _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,
// _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,
// _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,
//                            _______, _______, _______, _______, _______, _______,
/*
 * Base Layer: Colemak mod-DH
 *
 * ,----------------------------------.                ,----------------------------------.
 * |      |      |      |      |      |                |      |      |      |      |      |
 * |------+------+------+------+------|                |------+------+------+------+------|
 * |      |      |      |      |      |                |      |      |      |      |      |
 * |------+------+------+------+------|                |------+------+------+------+------|
 * |      |      |      |      |      |                |      |      |      |      |      |
 * `--------------------+------+------+------.  ,------+------+---------------------------'
 *                      |      |      |      |  |      |      |      |
 *                      `--------------------'  `--------------------'
 */
[_CLMKDH] = LAYOUT(
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
    HR_A,    HR_R,    HR_S,    HR_T,    KC_G,                      KC_M,    HR_N,    HR_E,    HR_I,    HR_O,
    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                      KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
                               ADJ_TAB, LOW_ENT, RAI_DEL, MED_BSP, NAV_SPC, HY_ESC
),

[_QWERTY] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    HRQ_A,   HRQ_S,   HRQ_D,   HRQ_F,   KC_G,                      KC_H,    HRQ_J,   HRQ_K,   HRQ_L,   HRQ_QUOT,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                               _______, _______, _______, _______, _______, _______
),

[_LOWER] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_DEL,  KC_7,    KC_8,    KC_9,    KC_BSLS,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                   KC_MINS, KC_4,    KC_5,    KC_6,    KC_ASTR,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_EQL,  KC_1,    KC_2,    KC_3,    KC_COMM,
                               KC_TAB,  _______, KC_DEL,  KC_BSPC, KC_0,    KC_DOT
),

[_RAISE] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_LPRN, KC_RPRN, KC_GRV,  KC_TILD,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                   KC_UNDS, KC_LBRC, KC_RBRC, XXXXXXX, KC_SCLN,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_PLUS, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX,
                               KC_TAB,  KC_ENT,  _______, KC_BSPC, KC_SPC,  KC_ESC
),
/* Navigation
 * - VIM ":wq" roll on left hand)
 * - Activated by right hand
 */
[_NAV] = LAYOUT(
    _______, _______, KC_COLN, XXXXXXX, XXXXXXX,                   KC_PGUP, KC_HOME, KC_WH_D, KC_WH_U, KC_END,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               KC_TAB,  KC_ENT,  KC_DEL,  KC_BSPC, _______, KC_ESC
),
/* Media
 * - F-keys on right
 * - Activated by right hand
 */
[_MEDIA] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,                   XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,
    KC_MPLY, KC_MSTP, KC_MNXT, KC_MPRV, KC_VOLD,                   XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE,                   XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,
                               KC_TAB,  KC_ENT,  KC_DEL,  _______, KC_SPC,  KC_ESC
),
[_ADJUST] = LAYOUT(
    RESET,   DEBUG,   XXXXXXX, XXXXXXX, KC_BRMU,                   XXXXXXX, AG_NORM, AG_SWAP, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRMD,                   XXXXXXX, CLMK_DH, QWERTY,  XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),
    // clang-format on
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) { return true; }
