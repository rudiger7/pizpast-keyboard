// Copyright 2026 PizPast
// SPDX-License-Identifier: GPL-3.0-or-later
//
// PizPast OL - UK firmware.
// Set the OS keyboard layout to "United Kingdom Extended" on Windows,
// "English (UK, extended, Windows)" on Linux.
// The plain UK layout types the same keycap legends; only AltGr+vowel and the
// dead keys differ.
// Layers 1-3 are translation tables, not real layers: see ../../translate.h

#include QMK_KEYBOARD_H
#include "translate.h"
#include "keymap_uk.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // NORMAL: what each key sends with no modifier
    [L_NORMAL] = LAYOUT(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSPC,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     UK_PLUS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     UK_LBRC,  UK_RBRC,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     UK_COMM,  UK_DOT,   UK_MINS,  KC_RSFT,
        KC_LCTL,  KC_LGUI,  KC_LALT,  UK_LABK,  KC_SPC,   KC_ENT,   KC_RALT,  MO(L_FN), UK_QUOT,  UK_SLSH,  UK_EURO
    ),
    // SHIFT table: _______ = normal Shift behaviour
    [L_SHIFT] = LAYOUT(
        _______, _______, _______, UK_AT,   _______, _______, _______, _______, UK_LPRN, UK_RPRN, UK_EQL,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, UK_QUES,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, UK_SCLN, UK_COLN, _______, _______,
        _______, _______, _______, UK_RABK, _______, _______, _______, _______, UK_ASTR, UK_BSLS, UK_HASH
    ),
    // ALTGR table: _______ = the OS layout's own AltGr character
    [L_ALTGR] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, UK_PIPE, UK_TILD
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
        UK_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
        _______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT
    )
};
