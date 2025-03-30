// Copyright 2025 Florian Mounier (https://florian.mounier.dev)

#include QMK_KEYBOARD_H

enum layers {
    L_BASE = 0, // QWERTY
    L_EXTRA,    // ERGO-L on QWERTY emulation
    L_TAP,
    L_BUTTON,
    L_NAV,
    L_MOUSE,
    L_MEDIA,
    L_NUM,
    L_FUN,
    L_SYM,
    L_ELSYM,     // ERGO-L ALTGR emulation
    L_LAFAYETTE, // ERGO-L LAFAYETTE emulation
};

enum tapdance_keycodes {
    TD_BOOT = 0, //
    TD_L_BASE,
    TD_L_EXTRA,
    TD_L_TAP,
    TD_L_BUTTON,
    TD_L_NAV,
    TD_L_MOUSE,
    TD_L_MEDIA,
    TD_L_NUM,
    TD_L_FUN,
    TD_L_SYM,
    TD_CAPS,
    TD_TAB_TAP_UNLOCK
};

void td_boot(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        reset_keyboard();
    }
}
void td_l_base(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        default_layer_set(1UL << L_BASE);
    }
}
void td_l_extra(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        default_layer_set(1UL << L_EXTRA);
    }
}
void td_l_tap(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        default_layer_set(1UL << L_TAP);
    }
}
void td_l_button(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        default_layer_set(1UL << L_BUTTON);
    }
}
void td_l_nav(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        default_layer_set(1UL << L_NAV);
    }
}
void td_l_mouse(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        default_layer_set(1UL << L_MOUSE);
    }
}
void td_l_media(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        default_layer_set(1UL << L_MEDIA);
    }
}
void td_l_num(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        default_layer_set(1UL << L_NUM);
    }
}
void td_l_fun(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        default_layer_set(1UL << L_FUN);
    }
}
void td_l_sym(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        default_layer_set(1UL << L_SYM);
    }
}
void td_tab_tap_unlock(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_TAB);
    } else if (state->count >= 6) {
        default_layer_set(1UL << L_BASE);
    }
}
void td_caps(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        caps_word_on();
    } else if (state->count >= 2) {
        tap_code(KC_CAPS);
    }
}

// clang-format off
tap_dance_action_t tap_dance_actions[] = {
    [TD_BOOT]   = ACTION_TAP_DANCE_FN(td_boot),
    [TD_L_BASE] = ACTION_TAP_DANCE_FN(td_l_base),
    [TD_L_EXTRA] = ACTION_TAP_DANCE_FN(td_l_extra),
    [TD_L_TAP] = ACTION_TAP_DANCE_FN(td_l_tap),
    [TD_L_BUTTON] = ACTION_TAP_DANCE_FN(td_l_button),
    [TD_L_NAV] = ACTION_TAP_DANCE_FN(td_l_nav),
    [TD_L_MOUSE] = ACTION_TAP_DANCE_FN(td_l_mouse),
    [TD_L_MEDIA] = ACTION_TAP_DANCE_FN(td_l_media),
    [TD_L_NUM] = ACTION_TAP_DANCE_FN(td_l_num),
    [TD_L_FUN] = ACTION_TAP_DANCE_FN(td_l_fun),
    [TD_L_SYM] = ACTION_TAP_DANCE_FN(td_l_sym),
    [TD_CAPS] = ACTION_TAP_DANCE_FN(td_caps),
    [TD_TAB_TAP_UNLOCK] = ACTION_TAP_DANCE_FN(td_tab_tap_unlock),
};
// clang-format on

// Caps Word overrides for ergo-l os layout, disable when using QWERTY
bool caps_word_press_user(uint16_t keycode) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);

    if (layer == L_BASE) {
        if (keycode == KC_V && get_mods() & MOD_BIT(KC_RALT)) {
            // underscore
            return true;
        }
        if (keycode == KC_N) {
            // dot
            return false;
        }
        switch (keycode) {
            // Keycodes that continue Caps Word, with shift applied.
            case KC_A ... KC_Z:
            case KC_COMM:                        // g
            case KC_SLSH:                        // k
            case KC_SCLN:                        // u
                add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
                return true;

            // Keycodes that continue Caps Word, without shifting.
            case KC_1 ... KC_0:
            case KC_BSPC:
            case KC_DEL:
                return true;

            default:
                return false; // Deactivate Caps Word.
        }
    } else {
        switch (keycode) {
            // Keycodes that continue Caps Word, with shift applied.
            case KC_A ... KC_Z:
            case KC_MINS:
                add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
                return true;

            // Keycodes that continue Caps Word, without shifting.
            case KC_1 ... KC_0:
            case KC_BSPC:
            case KC_DEL:
            case KC_UNDS:
                return true;

            default:
                return false; // Deactivate Caps Word.
        }
    }
}

// #define C_RDO KC_AGIN
#define C_RDO C(KC_P)
#define C_PST KC_PSTE
#define C_CPY KC_COPY
#define C_CUT KC_CUT
// #define C_UND KC_UNDO
#define C_UND C(KC_Z)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = LAYOUT_split_3x5_3(
KC_Q,              KC_W,               KC_E,               KC_R,               KC_T,                         KC_Y,               KC_U,               KC_I,               KC_O,               KC_P,    
LGUI_T(KC_A),      LALT_T(KC_S),       LCTL_T(KC_D),       LSFT_T(KC_F),       KC_G,                         KC_H,               LSFT_T(KC_J),       LCTL_T(KC_K),       LALT_T(KC_L),       LGUI_T(KC_SCLN),
LT(L_BUTTON,KC_Z), LT(L_SYM,KC_X),     KC_C,               KC_V,               KC_B,                         KC_N,               KC_M,               KC_COMM,            LT(L_SYM,KC_DOT),   LT(L_BUTTON,KC_SLSH),
                                       LT(L_MEDIA,KC_ESC), LT(L_NAV,KC_SPC),   LT(L_MOUSE,KC_TAB),           ALGR_T(KC_ENT),     LT(L_NUM,KC_BSPC),  LT(L_FUN,KC_DEL)
    ),
    [L_EXTRA] = LAYOUT_split_3x5_3(
KC_Q,              KC_C,               KC_O,               KC_P,               KC_W,                         KC_J,               KC_M,               KC_D,               OSL(L_LAFAYETTE),   KC_Y,
LGUI_T(KC_A),      LALT_T(KC_S),       LCTL_T(KC_E),       LSFT_T(KC_N),       KC_F,                         KC_L,               LSFT_T(KC_R),       LCTL_T(KC_T),       LALT_T(KC_I),       LGUI_T(KC_U),
LT(L_BUTTON,KC_Z), ALGR_T(KC_X),       KC_MINUS,           KC_V,               KC_B,                         KC_DOT,             KC_H,               KC_G,               ALGR_T(KC_COMM),    LT(L_BUTTON,KC_K),
                                       LT(L_MEDIA,KC_ESC), LT(L_NAV,KC_SPC),   LT(L_MOUSE,KC_TAB),           LT(L_ELSYM,KC_ENT), LT(L_NUM,KC_BSPC),  LT(L_FUN,KC_DEL)
    ),
    [L_TAP] = LAYOUT_split_3x5_3(
KC_Q,              KC_W,               KC_E,               KC_R,               KC_T,                         KC_Y,               KC_U,               KC_I,               KC_O,               KC_P,
KC_A,              KC_S,               KC_D,               KC_F,               KC_G,                         KC_H,               KC_J,               KC_K,               KC_L,               KC_QUOT,
KC_Z,              KC_X,               KC_C,               KC_V,               KC_B,                         KC_N,               KC_M,               KC_COMM,            KC_DOT,             KC_SLSH,
                                       KC_ESC,             KC_SPC,             TD(TD_TAB_TAP_UNLOCK),        KC_ENT,             KC_BSPC,            KC_DEL
    ),
    [L_BUTTON] = LAYOUT_split_3x5_3(
C_UND,             C_CUT,              C_CPY,              C_PST,              C_RDO,                        C_RDO,              C_PST,              C_CPY,              C_CUT,              C_UND,
KC_LGUI,           KC_LALT,            KC_LCTL,            KC_LSFT,            XXXXXXX,                      XXXXXXX,            KC_LSFT,            KC_LCTL,            KC_LALT,            KC_LGUI,
C_UND,             C_CUT,              C_CPY,              C_PST,              C_RDO,                        C_RDO,              C_PST,              C_CPY,              C_CUT,              C_UND,
                                       KC_BTN3,            KC_BTN1,            KC_BTN2,                      KC_BTN2,            KC_BTN1,            KC_BTN3
    ),
    [L_NAV] = LAYOUT_split_3x5_3(
TD(TD_BOOT),       TD(TD_L_TAP),       TD(TD_L_EXTRA),     TD(TD_L_BASE),      XXXXXXX,                      C_RDO,              C_PST,              C_CPY,              C_CUT,              C_UND,
KC_LGUI,           KC_LALT,            KC_LCTL,            KC_LSFT,            XXXXXXX,                      TD(TD_CAPS),        KC_LEFT,            KC_DOWN,            KC_UP,              KC_RGHT,
XXXXXXX,           KC_ALGR,            TD(TD_L_NUM),       TD(TD_L_NAV),       XXXXXXX,                      KC_INS,             KC_HOME,            KC_PGDN,            KC_PGUP,            KC_END,
                                       XXXXXXX,            XXXXXXX,            XXXXXXX,                      KC_ENT,             KC_BSPC,            KC_DEL   
    ),
    [L_MOUSE] = LAYOUT_split_3x5_3(
TD(TD_BOOT),       TD(TD_L_TAP),       TD(TD_L_EXTRA),     TD(TD_L_BASE),      XXXXXXX,                      C_RDO,              C_PST,              C_CPY,              C_CUT,              C_UND,
KC_LGUI,           KC_LALT,            KC_LCTL,            KC_LSFT,            XXXXXXX,                      XXXXXXX,            KC_MS_L,            KC_MS_D,            KC_MS_U,            KC_MS_R,
XXXXXXX,           KC_ALGR,            TD(TD_L_SYM),       TD(TD_L_MOUSE),     XXXXXXX,                      XXXXXXX,            KC_WH_L,            KC_WH_D,            KC_WH_U,            KC_WH_R,
                                       XXXXXXX,            XXXXXXX,            XXXXXXX,                      KC_BTN2,            KC_BTN1,            KC_BTN3
    ),
    [L_MEDIA] = LAYOUT_split_3x5_3(
TD(TD_BOOT),       TD(TD_L_TAP),       TD(TD_L_EXTRA),     TD(TD_L_BASE),      XXXXXXX,                      RGB_TOG,            RGB_MOD,            RGB_HUI,            RGB_SAI,            RGB_VAI,
KC_LGUI,           KC_LALT,            KC_LCTL,            KC_LSFT,            XXXXXXX,                      XXXXXXX,            KC_MPRV,            KC_VOLD,            KC_VOLU,            KC_MNXT,
XXXXXXX,           KC_ALGR,            TD(TD_L_FUN),       TD(TD_L_MEDIA),     XXXXXXX,                      OU_AUTO,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
                                       XXXXXXX,            XXXXXXX,            XXXXXXX,                      KC_MSTP,            KC_MPLY,            KC_MUTE
    ),
    [L_NUM] = LAYOUT_split_3x5_3(
KC_LBRC,           KC_7,               KC_8,               KC_9,               KC_RBRC,                      XXXXXXX,            TD(TD_L_BASE),      TD(TD_L_EXTRA),     TD(TD_L_TAP),       TD(TD_BOOT),
KC_SCLN,           KC_4,               KC_5,               KC_6,               KC_EQL,                       XXXXXXX,            KC_LSFT,            KC_LCTL,            KC_LALT,            KC_LGUI,
KC_GRV,            KC_1,               KC_2,               KC_3,               KC_BSLS,                      XXXXXXX,            TD(TD_L_NUM),       TD(TD_L_NAV),       KC_ALGR,            XXXXXXX,
                                       KC_DOT,             KC_0,               KC_MINS,                      XXXXXXX,            XXXXXXX,            XXXXXXX
    ),
    [L_SYM] = LAYOUT_split_3x5_3(
KC_LCBR,           KC_AMPR,            KC_ASTR,            KC_LPRN,            KC_RCBR,                      XXXXXXX,            TD(TD_L_BASE),      TD(TD_L_EXTRA),     TD(TD_L_TAP),       TD(TD_BOOT),
KC_COLN,           KC_DLR,             KC_PERC,            KC_CIRC,            KC_PLUS,                      XXXXXXX,            KC_LSFT,            KC_LCTL,            KC_LALT,            KC_LGUI,
KC_TILD,           KC_EXLM,            KC_AT,              KC_HASH,            KC_PIPE,                      XXXXXXX,            TD(TD_L_SYM),       TD(TD_L_MOUSE),     KC_ALGR,            XXXXXXX,
                                       KC_LPRN,            KC_RPRN,            KC_UNDS,                      XXXXXXX,            XXXXXXX,            XXXXXXX 
    ),
    [L_FUN] = LAYOUT_split_3x5_3(
KC_F12,            KC_F7,              KC_F8,              KC_F9,              KC_PSCR,                      XXXXXXX,            TD(TD_L_BASE),      TD(TD_L_EXTRA),     TD(TD_L_TAP),       TD(TD_BOOT),
KC_F11,            KC_F4,              KC_F5,              KC_F6,              KC_SCRL,                      XXXXXXX,            KC_LSFT,            KC_LCTL,            KC_LALT,            KC_LGUI,
KC_F10,            KC_F1,              KC_F2,              KC_F3,              KC_PAUS,                      XXXXXXX,            TD(TD_L_FUN),       TD(TD_L_MEDIA),     KC_ALGR,            XXXXXXX,
                                       KC_APP,             KC_SPC,             KC_TAB,                       XXXXXXX,            XXXXXXX,            XXXXXXX
    ),
    [L_ELSYM] = LAYOUT_split_3x5_3(
    // Ergo-L/Bepolar altGr syms
KC_CIRC,           KC_LABK,            KC_RABK,            KC_DLR,             KC_PERC,                      KC_AT,              KC_AMPR,            KC_ASTR,            KC_QUOT,            KC_GRV,
KC_LCBR,           KC_LPRN,            KC_RPRN,            KC_RCBR,            KC_EQL,                       KC_BSLS,            KC_PLUS,            KC_MINS,            KC_SLSH,            KC_DQUO,
KC_TILD,           KC_LBRC,            KC_RBRC,            KC_UNDS,            KC_HASH,                      KC_PIPE,            KC_EXLM,            KC_SCLN,            KC_COLN,            KC_QUES,
                                       LT(L_MEDIA,KC_ESC), LT(L_NAV,KC_SPC),   LT(L_MOUSE,KC_TAB),           ALGR_T(KC_ENT),     LT(L_NUM,KC_BSPC),  LT(L_FUN,KC_DEL)
    ),
    [L_LAFAYETTE] = LAYOUT_split_3x5_3(
UC(0x00E2),       UC(0x00E7),          UC(0x0153),         UC(0x00F4),         XXXXXXX,                      XXXXXXX,            UC(0x00B5),         UC(0x005F),         XXXXXXX,            UC(0x00FB),
UC(0x00E0),       UC(0x00E9),          UC(0x00E8),         UC(0x00EA),         UC(0x00F1),                   KC_LPRN,            KC_RPRN,            UC(0x00EE),         UC(0x00EF),         UC(0x00F9),
UC(0x00E6),       UC(0x00DF),          UC(0x2011),         UC(0x2013),         UC(0x2014),                   UC(0x2026),         UC(0x00F5),         XXXXXXX,            UC(0x00B7),         XXXXXXX,
                                       XXXXXXX,            UC(0x2019),         XXXXXXX,                      UC_PREV,            UC_NEXT,            XXXXXXX
    )
};
// clang-format on

// RGB matrix rainbow layers
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t mods      = get_mods();
    uint8_t layer     = get_highest_layer(layer_state | default_layer_state);
    led_t   led_state = host_keyboard_led_state();

    for (uint8_t i = led_min; i < led_max; i++) {
        switch (i) {
            case 15:
                rgb_matrix_set_color(i, RGB_RED);
                break;
            case 16:
                rgb_matrix_set_color(i, RGB_ORANGE);
                break;
            case 17:
                rgb_matrix_set_color(i, RGB_YELLOW);
                break;
            case 18:
                rgb_matrix_set_color(i, RGB_GREEN);
                break;
            case 19:
                rgb_matrix_set_color(i, RGB_CYAN);
                break;
            case 20:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            default:
                switch (layer) {
                    case L_MEDIA:
                        rgb_matrix_set_color(i, RGB_RED);
                        break;
                    case L_NAV:
                        rgb_matrix_set_color(i, RGB_ORANGE);
                        break;
                    case L_MOUSE:
                        rgb_matrix_set_color(i, RGB_YELLOW);
                        break;
                    case L_NUM:
                        rgb_matrix_set_color(i, RGB_CYAN);
                        break;
                    case L_FUN:
                        rgb_matrix_set_color(i, RGB_BLUE);
                        break;
                    default:
                        if (is_caps_word_on()) {
                            rgb_matrix_set_color(i, RGB_TURQUOISE);
                        } else if (led_state.caps_lock) {
                            rgb_matrix_set_color(i, RGB_TEAL);
                        } else if (mods & MOD_BIT(KC_LGUI)) {
                            rgb_matrix_set_color(i, RGB_MAGENTA);
                        } else if (mods & MOD_BIT(KC_LALT)) {
                            rgb_matrix_set_color(i, RGB_PINK);
                        } else if (mods & MOD_BIT(KC_LCTL)) {
                            rgb_matrix_set_color(i, RGB_PURPLE);
                        } else if (mods & MOD_BIT(KC_LSFT)) {
                            rgb_matrix_set_color(i, RGB_WHITE);
                        } else if (mods & MOD_BIT(KC_RALT)) {
                            rgb_matrix_set_color(i, RGB_GREEN);
                        }
                        break;
                }
        }
    }
    return false;
}
