# The translator

A keyboard never sends characters. It sends key positions ("the key right of P") plus modifiers, and the OS layout turns them into characters. So a standard US-International, Italian or UK extended layout plus the right firmware can give any symbol arrangement, with nothing installed.

## Layers

| Layer | Name | Meaning |
|---|---|---|
| 0 | NORMAL | what each key sends with no modifier |
| 1 | SHIFT | what each key sends while Shift is held |
| 2 | ALTGR | what each key sends while AltGr (right Alt) is held |
| 3 | SHIFT+ALTGR | Shift and AltGr together |
| 4 | FN | the real Fn layer (FN key) |
| 5-7 | free | |

Layers 1-3 are **tables**, never switched on. Shift is still a normal modifier.

- `_______` (transparent) in a table = no change: the key acts like a normal key with Shift/AltGr held.
- Any other keycode = sent instead. Your Shift/AltGr is removed and the entry's own modifiers are used.

Example, Italian firmware, the `0` key:

| | NORMAL | SHIFT table | Result |
|---|---|---|---|
| Italian keyboard | `KC_0` | `_______` | `0` / `=` (Italian already has `=` on Shift+0) |
| US-Intl firmware | `KC_0` | `KC_EQL` | `0` / `=` (US has `)` on Shift+0, so the table fixes it) |

Rules:

- Only keys coming from layer 0 are translated. Fn-layer keys (arrows, F-keys) are untouched.
- No translation while Ctrl, left Alt or Win/GUI is held, so shortcuts like Ctrl+Shift+T keep working.
- Holding a translated key auto-repeats. Rolling several translated keys with Shift held (`()`) works.

## Editing in Vial

Select the layer (1 = Shift, 2 = AltGr, 3 = Shift+AltGr) and set a key. Use the **Any** field for keycodes with modifiers, e.g. `S(KC_0)` or `RALT(KC_E)`. In Vial's settings, set the keyboard layout to the one your OS uses, so the labels match.

## Limits

- Characters the OS layout can't produce can't be sent: `` ` `` and `~` on Windows Italian, `è` on plain US, and so on.
- US-International has dead keys: `'` `"` `` ` `` `~` `^` wait for the next key. Press Space after them to get the plain symbol.
- Standard Italian has no keys for capital accented letters (`È`, `À`...).
- UK extended: `` ` `` is a dead key too (Fn+Esc on this keyboard). Press Space after it to get the plain symbol.
- On the plain UK layout the keycap legends still come out, but AltGr+vowel differs between Windows and Linux, and there are no grave vowels.
- Not yet tested on the real keyboard: check every symbol on Windows and Linux after flashing.

## Default symbol layout (all three firmwares)

Physical key -> normal / Shift (/ AltGr):

- number row: `1 !` `2 "` `3 @` `4 $` `5 %` `6 ^` `7 &` `8 (` `9 )` `0 =`
- right of P: `+ ?`
- right of L: `[ {` and `] }`
- bottom row right of M: `, ;` `. :` `- _`
- left of Space: `< >`
- right of Fn: `' *`, `/ \ |`, `€ #`
- AltGr + vowel: á é í ó ú (US-Intl and UK, native) / à è ì ò ù, Shift+AltGr+E = é (Italian)
- UK: à è ì ò ù with Fn+Esc, then the vowel
- AltGr + `€ #` key: `~` (UK only)
- Fn: F1-F12 on the number row and Q/W, Del on Backspace, arrows on `-` `'` `/` `€`, `` ` `` on Esc (US-Intl and UK; UK also `¬` with Shift, `¦` with AltGr)
