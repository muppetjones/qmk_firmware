#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

enum layer_number {
  _CLMK_DH = 0,
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define HY_ESC HYPR_T(KC_ESC)
#define ADJ_BK LT(_ADJUST, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak DH
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | BADJ |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------| Raise |    | Lower |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  |Enter |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | Alt  | LGUI |LOWER | /Space  /       \Space \  |RAISE | Ctrl | RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_CLMK_DH] = LAYOUT( \
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    ADJ_BK, \
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                     KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_BSPC, \
  HY_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                     KC_M,    KC_N,    KC_E,    KC_I,   KC_O,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,   RAISE,   LOWER,   KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH, KC_SFTENT, \
                             KC_LALT, KC_LGUI, LOWER,  KC_SPC,  KC_SPC,  RAISE,   KC_LCTL, KC_RGUI \
),

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, \
                        KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC, KC_ENT, MO(_RAISE), KC_BSPC, KC_RGUI \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      | Mute | Vol- | Vol+ |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ~  |      |      |      |      |   (  |                    |   )  |   7  |   8  |   9  |   \  | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   %  |   ^  |   _  |   -  |   {  |-------.    ,-------|   }  |   4  |   5  |   6  |   *  |   \  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |   @  |   +  |   =  |   [  |-------|    |-------|   ]  |   1  |   2  |   3  |   |  |Enter |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |LOWER | /Space  /       \Enter \  |   0  |   .  |   =  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  KC_GRV , XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX,                   XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, \
  KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LPRN,                   KC_RPRN, KC_7,    KC_8,    KC_9,    KC_BSLS, KC_BSPC, \
  KC_GRV,  KC_PERC, KC_CIRC, KC_UNDS, KC_MINS, KC_LCBR,                   KC_RCBR, KC_4,    KC_5,    KC_6,    KC_ASTR, KC_BSLS, \
  XXXXXXX, XXXXXXX, XXXXXXX, KC_PLUS, KC_EQL,  KC_LBRC, _______, _______, KC_RBRC, KC_1,    KC_2,    KC_3,    KC_PIPE, KC_SFTENT, \
                             _______, _______, _______, KC_SPC,  KC_ENT,  KC_0,    KC_DOT,  KC_EQL \
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |MS_A_2|MS_W_L|MS_W_D|MS_W_U|MS_W_R|MS_W_U|                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |MS_A_1| MS_L | MS_D | MS_U | MS_R |MS_W_D|-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|MS_W_L |    |MS_W_R |------+------+------+------+------+------|
 * |MS_A_0|      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      | MS_2 | / MS_1  /       \      \  |RAISE |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, \
  KC_ACL2, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_WH_U,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, \
  KC_ACL1, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D,                     XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, XXXXXXX, \
  KC_ACL0, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_WH_L, KC_WH_R,  XXXXXXX, KC_HOME, KC_END,  KC_PGUP, KC_PGDN,  XXXXXXX, \
                             XXXXXXX, XXXXXXX, KC_BTN2,  KC_BTN1, XXXXXXX,  _______, XXXXXXX, XXXXXXX \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      | Reset|      |      |      |      |                    | Reset|      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, _CLMK_DH,_QWERTY, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  )
};

// Setting ADJUST layer RGB back to default
// void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
//   if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
//     layer_on(layer3);
//   } else {
//     layer_off(layer3);
//   }
// }

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
const char *wpm_state(void);
void render_bongo_cat(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
// const char *read_keylog(void);
// const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    // oled_write_ln(read_keylog(), false);
    // oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    render_bongo_cat();
    oled_set_cursor(0,6);
    oled_write(wpm_state(), false);
    // oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
