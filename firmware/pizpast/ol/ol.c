// Copyright 2026 PizPast
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Translator engine. See translate.h for the idea.

#include "translate.h"

bool pizpast_translate_enabled = true;

#define TRANSLATE_MODS (MOD_MASK_SHIFT | MOD_BIT(KC_RALT))
#define SHORTCUT_MODS (MOD_MASK_CTRL | MOD_MASK_GUI | MOD_BIT(KC_LALT))

// Only one translated key is held at a time (a new one replaces the old one,
// like QMK key overrides), which keeps weak modifiers from mixing.
static bool     active = false;
static keypos_t active_key;
static uint16_t active_out;

// Real modifiers we removed from the report while a translated key is held.
static uint8_t suppressed = 0;

// Keys whose press was translated: swallow their release.
static uint16_t swallow[MATRIX_ROWS];

static uint8_t table_for(uint8_t mods) {
    bool shift = mods & MOD_MASK_SHIFT;
    bool altgr = mods & MOD_BIT(KC_RALT);
    if (shift && altgr) return L_SHIFT_ALTGR;
    if (altgr) return L_ALTGR;
    if (shift) return L_SHIFT;
    return L_NORMAL;
}

static void restore_mods(void) {
    if (suppressed) {
        add_mods(suppressed);
        suppressed = 0;
    }
}

static void release_active(void) {
    if (active) {
        unregister_code16(active_out);
        active = false;
    }
}

static bool same_key(keypos_t a, keypos_t b) {
    return a.row == b.row && a.col == b.col;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) return false;

    keypos_t key     = record->event.key;
    bool     pressed = record->event.pressed;

    // Track real modifier releases so we never restore a modifier the user
    // already let go of.
    if (IS_MODIFIER_KEYCODE(keycode)) {
        if (!pressed) suppressed &= ~MOD_BIT(keycode);
        return true;
    }

    // Combos / encoders etc. have no matrix position.
    if (key.row >= MATRIX_ROWS || key.col >= MATRIX_COLS) return true;

    if (!pressed) {
        if (swallow[key.row] & (1u << key.col)) {
            swallow[key.row] &= ~(1u << key.col);
            if (active && same_key(active_key, key)) release_active();
            if (!active) {
                restore_mods();
                send_keyboard_report();
            }
            return false;
        }
        return true;
    }

    if (!pizpast_translate_enabled) return true;

    // Only translate keys that resolve to the NORMAL layer.
    if (layer_switch_get_layer(key) != L_NORMAL) {
        restore_mods();
        return true;
    }

    uint8_t real_mods = get_mods();
    uint8_t os_mods   = get_oneshot_mods();
    uint8_t eff       = real_mods | suppressed | os_mods;

    if (eff & SHORTCUT_MODS) {
        restore_mods();
        return true;
    }

    uint8_t table = table_for(eff);
    if (table == L_NORMAL) {
        restore_mods();
        return true;
    }

    uint16_t out = keymap_key_to_keycode(table, key);
    if (out == KC_TRNS) {
        // No entry: behave like a normal key with the real modifiers.
        restore_mods();
        return true;
    }

    // Translate.
    release_active();
    uint8_t to_remove = real_mods & TRANSLATE_MODS;
    del_mods(to_remove);
    suppressed |= to_remove;
    if (os_mods & TRANSLATE_MODS) clear_oneshot_mods();

    swallow[key.row] |= (1u << key.col);
    if (out != KC_NO) {
        register_code16(out);
        active     = true;
        active_key = key;
        active_out = out;
    } else {
        send_keyboard_report();
    }
    return false;
}
