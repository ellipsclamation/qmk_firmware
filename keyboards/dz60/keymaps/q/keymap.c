#include QMK_KEYBOARD_H

enum custom_keycodes {
   DEL_LINE = SAFE_RANGE,
   DEL_LEFT,
   DEL_RIGHT,
   YANK_LINE,
   DESK_LEFT,
   DESK_RIGHT,
   NEW_LINE_UP,
   NEW_LINE_DOWN
};

uint32_t layer_state_set_user(uint32_t state) {
   switch (biton32(state)) {
      // base layer
      case 0:
         rgblight_disable();
         break;
      // gamer layer
      case 1:
         rgblight_enable();
         rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT);
         break;
      // numpad layer
      case 2:
         rgblight_enable();
         rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
         rgblight_sethsv_noeeprom_green();
         break;
      // function layer
      case 3:
         rgblight_enable();
         rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
         rgblight_sethsv_noeeprom_blue();
         break;
      // rgb layer
      case 4:
         rgblight_enable();
         rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
         rgblight_sethsv_noeeprom_red();
         break;
      default:
         rgblight_disable();
         break;
   }
   return state;
}

bool led_update_user(led_t led_state) {
   static uint8_t caps_state = 0;
   if (caps_state != led_state.caps_lock) {
      if (led_state.caps_lock) {
         rgblight_enable();
         rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
         rgblight_sethsv_noeeprom_pink();
      }
      else {
         rgblight_disable();
      }
      caps_state = led_state.caps_lock;
   }
   return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {
      // HOME HOME SHIFT+END DEL DEL
      case DEL_LINE:
         if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_HOME) SS_DOWN(X_LSHIFT) SS_TAP(X_END) SS_UP(X_LSHIFT) SS_TAP(X_DELETE) SS_TAP(X_DELETE));
         }
         break;

      // SHIFT+HOME DEL
      case DEL_LEFT:
         if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LSHIFT) SS_TAP(X_HOME) SS_UP(X_LSHIFT) SS_TAP(X_DELETE));
         }
         break;

      // SHIFT+END DEL
      case DEL_RIGHT:
         if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LSHIFT) SS_TAP(X_END) SS_UP(X_LSHIFT) SS_TAP(X_DELETE));
         }
         break;

      // HOME SHIFT+END CTRL+C END
      case YANK_LINE:
         if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_HOME) SS_DOWN(X_LSHIFT) SS_TAP(X_END) SS_UP(X_LSHIFT) SS_DOWN(X_LCTRL) SS_TAP(X_INSERT) SS_UP(X_LCTRL) SS_TAP(X_END));
         }
         break;

      // CTRL+WIN+LEFT
      case DESK_LEFT:
         if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LGUI) SS_TAP(X_LEFT) SS_UP(X_LGUI) SS_UP(X_LCTRL));
         }
         break;

      // CTRL+WIN+RIGHT
      case DESK_RIGHT:
         if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LGUI) SS_TAP(X_RIGHT) SS_UP(X_LGUI) SS_UP(X_LCTRL));
         }
         break;

      // HOME SHIFT+ENTER UP
      case NEW_LINE_UP:
         if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_HOME) SS_DOWN(X_LSHIFT) SS_TAP(X_ENTER) SS_UP(X_LSHIFT) SS_TAP(X_UP));
         }
         break;

      // END SHIFT+ENTER
      case NEW_LINE_DOWN:
         if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_END) SS_DOWN(X_LSHIFT) SS_TAP(X_ENTER) SS_UP(X_LSHIFT));
         }
         break;
   }
   return true;
};


/*
LAYER 0 (BASE LAYER):
   +-----------------------------------------------------------+
   |ESC|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
   |-----------------------------------------------------------|
   | TAB |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| DEL |
   |-----------------------------------------------------------|
   |CAPSLK|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  ENTER |
   |-----------------------------------------------------------|
   | SHIFT |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|SFT| UP|0M0|
   |-----------------------------------------------------------|
   |CTRL| WIN| 0M1|   BKSP | 0M2|   SPACE  |0M3|0M4|LEF|DWN|RGT|
   +-----------------------------------------------------------+

   0M0: TAP FOR MOUSE BTN 1
X  0M1: TAP ONCE FOR ALT+LEFT, TWICE FOR WIN+CTRL+LEFT, HOLD FOR ALT
   0M2: TAP TWICE TO TOGGLE LAYER 3, HOLD FOR MOMENTARY LAYER 3 (FUNCTION LAYER)
X  0M3: TAP ONCE FOR ALT+RIGHT, TWICE FOR WIN+CTRL+RIGHT, HOLD FOR ALT
X  OM4: TAP FOR CTRL+L, HOLD FOR CTRL

LAYER 1 (GAMER LAYER):
   SWAPPED SPACE AND BACKSPACE

LAYER 2 (NUMPAD LAYER):
   +-----------------------------------------------------------+
   |TRN|   |   |   |   |   |   |   |   |  (|  )|   |   |   |INS|
   |-----------------------------------------------------------|
   | TRN |HOM| UP|END|PGU|   |   |  *|  7|  8|  9|  -|  :| TRN |
   |-----------------------------------------------------------|
   | 1M0  |LFT|DWN|RGT|PGD|   |   |  /|  4|  5|  6|  +|  TRN   |
   |-----------------------------------------------------------|
   | TRN   |   |   |   |   |   |   |  0|  1|  2|  3|  .| UP|  =|
   |-----------------------------------------------------------|
   | TRN| TRN| TRN|   TRN  | TRN|   TRN    |TRN|TRN|LFT|DWN|RGT|
   +-----------------------------------------------------------+

   1M0: TOGGLE LAYER 2 (NUMPAD LAYER)

LAYER 3 (FUNCTION LAYER):
   +-----------------------------------------------------------+
   |2M0| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|2M1|PRT|
   |-----------------------------------------------------------|
   | TRN |2M2|   |2M3|2M4|2M5|2M6|2M7| UP|2M8|   |2M9|2N0| 2N1 |
   |-----------------------------------------------------------|
   | 1M0  |2N2|2N3|2N4|2N5|   |HOM|LFT|DWN|RGT|END|   |  TRN   |
   |-----------------------------------------------------------|
   | TRN   |   |DEL|2N6|2N7|   |   |   |PRV|PLY|NXT|TRN|PGP|2N8|
   |-----------------------------------------------------------|
   | TRN| TRN| TRN|   2N9  | TRN|   3N0    |TRN|TRN|HOM|PGD|END|
   +-----------------------------------------------------------+

   2M0: ALT+F4
   2M1: ALT+PRTSC
   2M2: CTRL+SHIFT+TAB
   2M3: CTRL+TAB
   2M4: CTRL+R
   2M5: CTRL+SHIFT+T
   2M6: YANK (COPY LINE)
   2M7: NEW LINE UP
   2M8: NEW LINE DOWN
   2M9: CTRL+SHIFT+LEFT
   2N0: CTRL+SHIFT+RIGHT
   2N1: DELETE RIGHT
   2N2: CTRL+LEFT
   2N3: CTRL+RIGHT
   2N4: DELETE LINE
   2N5: CTRL+F
   2N6: CTRL+INS
   2N7: SHIFT+INS
   2N8: TOGGLE LAYER 4 (RGB LAYER)
   2N9: DELETE LEFT
   3N0: TOGGLE LAYER 1 (GAMER LAYER) (SPACEBAR ON LEFT)

LAYER 4 (RGB LAYER):
   +-----------------------------------------------------------+
   |TG3| RP| RB| RR|RSW|RSN| RK| RX| RG|   |   |   |   |DEB|RES|
   |-----------------------------------------------------------|
   |     |   |   |   |   |   |   |   |   |   |   |EF-|EF+| TG3 |
   |-----------------------------------------------------------|
   |      |   |   |   |   |   |   |   |   |   | R-| R+|        |
   |-----------------------------------------------------------|
   |       |   |   |   |   |   |   |   |   |   | H+|RTG| B+|TG3|
   |-----------------------------------------------------------|
   |    |    |    |        |    |          |   | H-| S-| B-| S+|
   +-----------------------------------------------------------+

   TG3: TOGGLE LAYER 4 (RGB LAYER)
   RP: RGB MODE PLAIN
   RB: RGB MODE BREATHE
   RR: RGB MODE RAINBOW
   RSW: RGB MODE SWIRL
   RSN: RGB MODE SNAKE
   RK: RGB MODE KNIGHT RIDER
   RX: RGB MODE CHRISTMAS
   RG: RGB MODE GRADIENT
   EF +/-: EFFECT SPEED
   R +/-: NEXT/PREV RGB MODE
   H +/-: HUE
   RTG: RGB TOGGLE
   B +/-: BRIGHTNESS
   S +/-: SATURATION
   DEB: DEBUG
   RES: RESET

*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   // base layer
   [0] = LAYOUT_directional(
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_DEL,
      LCTL_T(KC_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_MS_BTN1,
      KC_LCTL, KC_LGUI, KC_LALT, KC_BSPC, TT(3), KC_SPC, KC_RALT, KC_RCTRL, KC_LEFT, KC_DOWN, KC_RGHT
   ),
   // gamer layer
   [1] = LAYOUT_directional(
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_DEL,
      LCTL_T(KC_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_MS_BTN1,
      KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, TT(3), KC_BSPC, KC_RALT, KC_RCTRL, KC_LEFT, KC_DOWN, KC_RGHT
   ),
   // numpad layer
   [2] = LAYOUT_directional(
      KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LPRN, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_INS,
      KC_TRNS, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_NO, KC_NO, KC_PAST, KC_7, KC_8, KC_9, KC_PMNS, KC_COLN, KC_TRNS,
      TG(2), KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO, KC_NO, KC_PSLS, KC_4, KC_5, KC_6, KC_PPLS, KC_TRNS,
      KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_0, KC_1, KC_2, KC_3, KC_DOT, KC_UP, KC_EQL,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT
   ),
   // function layer
   [3] = LAYOUT_directional(
      LALT(KC_F4), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, LALT(KC_PSCR), KC_PSCR,
      KC_TRNS, LCTL(LSFT(KC_TAB)), KC_NO, LCTL(KC_TAB), LCTL(KC_R), LCTL(LSFT(KC_T)), YANK_LINE, NEW_LINE_UP, KC_UP, NEW_LINE_DOWN, KC_NO, LCTL(LSFT(KC_LEFT)), LCTL(LSFT(KC_RGHT)), DEL_RIGHT,
      TG(2), LCTL(KC_LEFT), LCTL(KC_RGHT), DEL_LINE, LCTL(KC_F), KC_NO, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_INS, KC_TRNS,
      KC_TRNS, LCTL(KC_Z), KC_DEL, LCTL(KC_INS), LSFT(KC_INS), KC_NO, KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_PGUP, TG(4),
      KC_TRNS, KC_TRNS, KC_TRNS, DEL_LEFT, KC_TRNS, TG(1), KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END
   ),
   // rgb layer
   [4] = LAYOUT_directional(
      TG(4), RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, KC_NO, KC_NO, KC_NO, KC_NO, DEBUG, RESET,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_SPD, RGB_SPI, TG(4),
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_RMOD, RGB_MOD, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_HUI, RGB_TOG, RGB_VAI, TG(4),
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SAI
   )
};
