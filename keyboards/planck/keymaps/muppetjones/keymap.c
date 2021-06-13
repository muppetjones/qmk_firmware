/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"

enum planck_layers {
  _CLMK_DH,
  _CLMK_II,
  _QWERTY,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _PLOVER,
  _NUMPD,
  _ADJUST,
};

enum planck_keycodes {
  CLMK_DH = SAFE_RANGE,
  CLMK_II,
  QWERTY,
  COLEMAK,
  PLOVER,
  BACKLIT,
  EXT_PLV,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define NUMPD MO(_NUMPD)

#define HY_ESC HYPR_T(KC_ESC)

// Left-hand home row mods (colemak)
#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LCTL_T(KC_S)
#define HOME_T LSFT_T(KC_T)

// Right-hand home row mods (colemak)
#define HOME_N RSFT_T(KC_N)
#define HOME_E RCTL_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RGUI_T(KC_O)

// Left-hand home row mods (lower)---
// #define HOME_UND LCTL_T(KC_UNDS)  // NOTE: Mod-tap restricted to basic keycodes
#define HOME_MIN LSFT_T(KC_MINS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Colemak DH (* indicates changes from base Colemak)
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |  *B  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |  *G  |  *M  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |  *D  |  *V  |   K  |  *H  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |NumPad| Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_CLMK_DH] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    HY_ESC,  HOME_A,  HOME_R,  HOME_S,  HOME_T,  KC_G,    KC_M,    HOME_N,  HOME_E,  HOME_I, HOME_O, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,
    KC_LCTL, NUMPD,   KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX
),



/* Colemak DH inner row
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_CLMK_II] = LAYOUT_planck_grid(
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_TAB,  KC_BSPC, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
    HOME_A,  HOME_R,  HOME_S,  HOME_T,  KC_G,    HY_ESC,  KC_QUOT, KC_M,    HOME_N,  HOME_E,  HOME_I,  HOME_O,
    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    XXXXXXX, KC_ENT,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   `  |   $  |   (  |   )  |   7  |   8  |   9  |   \  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   %  |   ^  |   _  |   -  |   {  |   }  |   4  |   5  |   6  |   *  |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |   +  |   =  |   [  |   ]  |   1  |   2  |   3  |   |  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Space    |   0  |   .  |   =  |   &  | Play |
 * `-----------------------------------------------------------------------------------'
 * 21.02.22: Removed F keys.
 * 21.03.28: Completely revamped to contain 10-key numpad and symbols.
 */
[_LOWER] = LAYOUT_planck_grid(
    _______, _______, KC_GRV,  KC_TILD, KC_LPRN, XXXXXXX, KC_BSPC, KC_RPRN, KC_7, KC_8,   KC_9,   KC_BSLS,
    KC_LGUI, KC_LALT, KC_UNDS,HOME_MIN, KC_LCBR, XXXXXXX, XXXXXXX, KC_RCBR, KC_4, KC_5,   KC_6,   KC_ASTR,
    _______, _______, KC_PLUS, KC_EQL,  KC_LBRC, XXXXXXX, KC_ENT,  KC_RBRC, KC_1, KC_2,   KC_3,   KC_PIPE,
    _______, _______, _______, _______, _______, KC_SPC,  KC_SPC,  _______, KC_0, KC_DOT, KC_EQL, KC_AMPR
 ),

/* Raise
* ,-----------------------------------------------------------------------------------.
* |   `  |MS_W_L|MS_W_D|MS_W_U|MS_W_R|      |      |      |      |      |      | Bksp |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      | MS_L | MS_D | MS_U | MS_R |      |      | LEFT | DOWN |  UP  |RIGHT |  \   |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |MS_A_1|MS_A_2| MS_2 | MS_1 |      |      | Home | End  |Pg Up |Pg Dn |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
* `-----------------------------------------------------------------------------------'
* 21.02.22: Removed F keys and replaced with useful programming keys.
*/
[_RAISE] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______, XXXXXXX, XXXXXXX, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,
    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, XXXXXXX, XXXXXXX, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
    _______, _______, _______, _______, _______, KC_SPC,  KC_SPC,  _______, _______, KC_MNXT, KC_VOLD, KC_VOLU
),

/* Num Pad
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |      |      |   7  |   8  |   9  |   \  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |      |   4  |   5  |   6  |   *  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |      |   1  |   2  |   3  |   ^  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |   0  |   .  |Enter |      |
 * `-----------------------------------------------------------------------------------'
 * 21.02.22: Added F keys
 */
[_NUMPD] = LAYOUT_planck_grid(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, KC_7,    KC_8, KC_9,   KC_BSLS, KC_BSPC,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, KC_4,    KC_5, KC_6,   KC_ASTR, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_1,    KC_2, KC_3,   KC_CIRC, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_0, KC_DOT, KC_ENT,  _______
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Brite |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|ClmkDH|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, _______,
    _______, BACKLIT, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK,  DVORAK,  PLOVER,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  CLMK_DH, _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)
    // clang-format on
};

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

/* Setup layer lighting
#define HSV_WHITE 0, 0, 255
#define HSV_RED 0, 255, 255
#define HSV_CORAL 11, 176, 255
#define HSV_ORANGE 28, 255, 255
#define HSV_GOLDENROD 30, 218, 218
#define HSV_GOLD 36, 255, 255
#define HSV_YELLOW 43, 255, 255
#define HSV_CHARTREUSE 64, 255, 255
#define HSV_GREEN 85, 255, 255
#define HSV_SPRINGGREEN 106, 255, 255
#define HSV_TURQUOISE 123, 90, 112
#define HSV_TEAL 128, 255, 128
#define HSV_CYAN 128, 255, 255
#define HSV_AZURE 132, 102, 255
#define HSV_BLUE 170, 255, 255
#define HSV_PURPLE 191, 255, 255
#define HSV_MAGENTA 213, 255, 255
#define HSV_PINK 234, 128, 255
#define HSV_BLACK 0, 0, 0
#define HSV_OFF HSV_BLACK
 *
 */

#define LIGHT_GOLDEN 30, 255, 100
#define LIGHT_MAGENTA 213, 255, 100
#define LIGHT_AZURE 148, 255, 100

// Define light layers
// -- e.g., light up LEDS 3-6 with RED when the numpd layer is active
const rgblight_segment_t PROGMEM rgb_clmk_dh[] = RGBLIGHT_LAYER_SEGMENTS({0, 9, HSV_RED});
const rgblight_segment_t PROGMEM rgb_lower[]   = RGBLIGHT_LAYER_SEGMENTS({0, 9, LIGHT_GOLDEN});
const rgblight_segment_t PROGMEM rgb_raise[]   = RGBLIGHT_LAYER_SEGMENTS({0, 9, LIGHT_MAGENTA});
const rgblight_segment_t PROGMEM rgb_numpd[]   = RGBLIGHT_LAYER_SEGMENTS({0, 9, LIGHT_AZURE});

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(rgb_clmk_dh, rgb_lower, rgb_raise, rgb_numpd);

void keyboard_post_init_user(void) {
  rgblight_layers = rgb_layers;  // Enable the LED layers
}

layer_state_t layer_state_set_user(layer_state_t state) {
  // rgblight_set_layer_state(0, layer_state_cmp(state, _CLMK_DH));
  // rgblight_set_layer_state(1, layer_state_cmp(state, _NUMPD));
  rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
  rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
  rgblight_set_layer_state(3, layer_state_cmp(state, _NUMPD));
  return update_tri_layer_state(state, _LOWER, _NUMPD, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case CLMK_DH:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_CLMK_DH);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
        backlight_step();
#endif
#ifdef KEYBOARD_planck_rev5
        writePinLow(E6);
#endif
      } else {
        unregister_code(KC_RSFT);
#ifdef KEYBOARD_planck_rev5
        writePinHigh(E6);
#endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
#ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(plover_song);
#endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
          eeconfig_init();
        }
        keymap_config.raw  = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
#ifdef AUDIO_ENABLE
        PLAY_SONG(plover_gb_song);
#endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo += 1;
      } else {
        muse_tempo -= 1;
      }
    }
  } else {
    if (clockwise) {
#ifdef MOUSEKEY_ENABLE
      tap_code(KC_MS_WH_DOWN);
#else
      tap_code(KC_PGDN);
#endif
    } else {
#ifdef MOUSEKEY_ENABLE
      tap_code(KC_MS_WH_UP);
#else
      tap_code(KC_PGUP);
#endif
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
  switch (index) {
    case 0: {
#ifdef AUDIO_ENABLE
      static bool play_sound = false;
#endif
      if (active) {
#ifdef AUDIO_ENABLE
        if (play_sound) {
          PLAY_SONG(plover_song);
        }
#endif
        layer_on(_ADJUST);
      } else {
#ifdef AUDIO_ENABLE
        if (play_sound) {
          PLAY_SONG(plover_gb_song);
        }
#endif
        layer_off(_ADJUST);
      }
#ifdef AUDIO_ENABLE
      play_sound = true;
#endif
      break;
    }
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
      }
  }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
  if (muse_mode) {
    if (muse_counter == 0) {
      uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
      if (muse_note != last_muse_note) {
        stop_note(compute_freq_for_midi_note(last_muse_note));
        play_note(compute_freq_for_midi_note(muse_note), 0xF);
        last_muse_note = muse_note;
      }
    }
    muse_counter = (muse_counter + 1) % muse_tempo;
  } else {
    if (muse_counter) {
      stop_all_notes();
      muse_counter = 0;
    }
  }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
