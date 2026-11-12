// Copyright 2026 PizPast
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#define VIAL_KEYBOARD_UID {0xD8, 0x26, 0x35, 0x56, 0x38, 0x02, 0x96, 0x48}

// Unlock Vial: hold ESC + bottom-right key
#define VIAL_UNLOCK_COMBO_ROWS { 0, 4 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 11 }

// 0 normal, 1-3 translation tables, 4 Fn, 5-7 free
#define DYNAMIC_KEYMAP_LAYER_COUNT 8
#define DYNAMIC_KEYMAP_MACRO_COUNT 32
