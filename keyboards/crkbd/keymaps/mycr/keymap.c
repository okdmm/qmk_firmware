#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};



#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_ADJUST ADJUST
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_CTRZ CTL_T(KC_Z)
#define KC_SSPC LSFT_T(KC_SPC)

enum combos {
  ct_h_BS,
  ct_i_TB,
  ct_rbrc_ESC,
  ct_m_ENT
};

/*
const uint16_t PROGMEM bs_combo[] = {KC_LCTL, KC_H, COMBO_END};
const uint16_t PROGMEM tb_combo[] = {KC_LCTL, KC_I, COMBO_END};
const uint16_t PROGMEM esc_combo[] = {KC_LCTL, KC_RBRC, COMBO_END};
const uint16_t PROGMEM ent_combo[] = {KC_LCTL, KC_M, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [ct_h_BS] = COMBO(bs_combo, KC_BSPC),
  [ct_i_TB] = COMBO(tb_combo, KC_TAB),
  [ct_rbrc_ESC] = COMBO(esc_combo, KC_ESC),
  [ct_m_ENT] = COMBO(ent_combo, KC_ENT)
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  /*                ,-----------------------------------------.
  //    TAB,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,   -,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
  //   LCTL,     A,     S,     D,     F,     G,                      H,     J,     K,     L,    ;:,   '",\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
  //    ESC,     Z,     X,     C,     V,     B,                      N,     M,  ,< ,   . > ,  /?  , ALTKN,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
  //                              GUIEI, LOWER,  SPC,      RSFT, RAISE,   ENT \
                              //`--------------------'  `--------------------'
  */ 

      /*
  //,-----------------------------------------.                ,-----------------------------------------.
           ,      ,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  MINS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  BSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        ESC,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RALT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LOWER,  SPC,      RSFT, RAISE,  RGUI\
                              //`--------------------'  `--------------------'
                              //
      */

  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX,  XXXXX, COMMA,   DOT,     P,     Y,                      F,     G,     C,     R,     L, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     A,     O,     E,     U,     I,                      D,     H,     T,     N,     S,  SCLN,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        ESC,  SLSH,     Q,     J,     K,     X,                      B,     M,     W,     V,     Z,  MINS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LALT, RAISE,  SSPC,     SSPC, LOWER,  RGUI\
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  /*
  //,-----------------------------------------.                ,-----------------------------------------.
  //    ESC,     1,     -,     -,     @,     #,                      6,     7,     {,     },     ',  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
  //   LCTL,     !,     =,     |,     &,     *,                      ^,     $,     (,     ),     ",     `,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
  //  CTLTB,     _,     +,     -,     +,     ~,                   LEFT,     %,     [,     ],     `, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
  //                              GUIEI, LOWER,  SPC,      RSFT, RAISE,   ENT \
                              //`--------------------'  `--------------------'
  */ 

  //,-----------------------------------------.                ,-----------------------------------------.
      _____, _____,  TILD,  PLUS, _____, _____,                  _____, _____,  LCBR,  RCBR,   GRV, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  EXLM,  PEQL,  PIPE,  AMPR,  ASTR,                   CIRC,   DLR,  LPRN,  RPRN,  DQUO,  HASH,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  UNDS,    AT,  BSLS,  MINS, _____,                  _____,  PERC,  LBRC,  RBRC,  QUOT, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____\
                              //`--------------------'  `-------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  /*
  //,-----------------------------------------.                ,-----------------------------------------.
  //    ESC,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
  //   LCTL,     _,     +,     {,     },     ~,                   LEFT,  DOWN,    UP, RIGHT,   F10, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
  //    ESC,  UNDS,  PLUS,  LCBR,  RCBR,  TILD,                   LEFT,  DOWN,    UP, RIGHT,   F10, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
  //                              GUIEI, LOWER,  SPC,      RSFT, RAISE,   ENT \
                              //`--------------------'  `--------------------'
  */ 

  //,-----------------------------------------.                ,-----------------------------------------.
      _____, _____,  TILD,  PLUS, _____, _____,                  _____, _____,  RGUI,  RALT, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,    P5,    P4,    P3,    P2,    P1,                     P6,    P7,    P8,    P9,    P0, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  UNDS,    AT,  BSLS,  MINS, _____,                  _____,  PERC,  LBRC,  RBRC,  QUOT, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____\
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,    F5,    F4,    F3,    F2,    F1,                     F6,    F7,    F8,    F9, RIGHT, MUTE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+-----|
      _____,  LHUI,  LSAI,  BTN1,  BTN2,  LSFT,                  LEFT,   LEFT,    UP, RIGHT,   F10, VOLD,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+-----|
      _____,  LHUD,  ACL2,  DOWN,    UP, XXXXX,                  MS_L,  VOLD,  VOLU,   MUTE, XXXXX, VOLU,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____\
                              //`--------------------'  `--------------------'
  ),
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

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
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
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
      break;
  }
  return true;
}
