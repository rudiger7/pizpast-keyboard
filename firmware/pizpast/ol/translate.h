// Copyright 2026 PizPast
// SPDX-License-Identifier: GPL-3.0-or-later
//
// PizPast translator
// ------------------
// The keyboard never sends characters, only key positions (+ modifiers).
// The OS layout (US-International, Italian, ...) turns them into characters.
//
// To give every key its own Shift / AltGr output without a custom OS layout,
// the firmware keeps three hidden "tables". They are stored as normal keymap
// layers so Vial can read and edit them, but they are never activated:
//
//   layer 0  NORMAL        what a key sends with no modifier
//   layer 1  SHIFT         what a key sends while Shift is held
//   layer 2  ALTGR         what a key sends while AltGr (right Alt) is held
//   layer 3  SHIFT_ALTGR   what a key sends while Shift + AltGr are held
//   layer 4  FN            the real Fn layer (MO(L_FN))
//   layer 5+               free for the user
//
// A table entry of KC_TRNS means "no translation": the key behaves exactly
// like a normal key with the real modifier held. Any other entry is sent
// instead, with the user's Shift/AltGr removed and the entry's own modifiers
// applied. Example on an Italian host: SHIFT table entry for the "0" key is
// S(KC_0) ('='), the NORMAL entry stays KC_0 ('0').
//
// Translation only applies to keys coming from layer 0 and is skipped while
// Ctrl, left Alt or GUI are held, so shortcuts (Ctrl+Shift+T...) keep working.

#pragma once

#include "quantum.h"

enum pizpast_layers {
    L_NORMAL = 0,
    L_SHIFT,
    L_ALTGR,
    L_SHIFT_ALTGR,
    L_FN,
};

// Set to false (e.g. from a keymap) to disable translation at runtime.
extern bool pizpast_translate_enabled;
