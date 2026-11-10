// Copyright 2026 PizPast
// SPDX-License-Identifier: GPL-3.0-or-later
//
// PizPast OL - US-International firmware.
// Set the OS keyboard layout to "US-International" on Windows / Linux.
// Layers 1-3 are translation tables, not real layers: see ../../translate.h

#include QMK_KEYBOARD_H
#include "translate.h"
#include "keymap_us_international.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // NORMAL: what each key sends with no modifier
    [L_NORMAL] = LAYOUT(
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_BSPC,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_PLUS,
        KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_LBRC,    KC_RBRC,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_MINS,    KC_RSFT,
        KC_LCTL,    KC_LGUI,    KC_LALT,    KC_LT,      KC_SPC,     KC_ENT,     KC_RALT,    MO(L_FN),   KC_QUOT,    KC_SLSH,    RALT(KC_5)
    ),
    // SHIFT table: _______ = normal Shift behaviour
    [L_SHIFT] = LAYOUT(
        _______, _______, KC_DQUO, KC_AT,   _______, _______, _______, _______, KC_LPRN, KC_RPRN, KC_EQL,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_QUES,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_SCLN, KC_COLN, _______, _______,
        _______, _______, _______, KC_GT,   _______, _______, _______, _______, KC_ASTR, KC_BSLS, KC_HASH
    ),
    // ALTGR table: _______ = the OS layout's own AltGr character
    [L_ALTGR] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PIPE, _______
    ),
    // SHIFT+ALTGR table
    [L_SHIFT_ALTGR] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    // FN layer (real layer, held with the FN key)
    [L_FN] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
        _______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT
    )
};
