# Plan: UK firmware

## Goal

A third firmware, `keymaps/uk`, for a host whose OS layout is **UK extended**
(Windows "United Kingdom Extended", Linux "English (UK, extended, Windows)",
xkb `gb` variant `extd`). Like `it` and `us_intl`: every key types what the
PizPast keycaps show at the Normal, Shift and AltGr levels, on the unmodified
host layout. The keycap legends come out the same on the plain UK layout; UK
extended adds the accented vowels. It builds like the other two
(`tools/build.sh`, CI) and is documented. The app side is the plan
`.claude/plans/uk.md` of `../pizpast-vial` (branch `uk-layout`).

## Read first

`AGENTS.md` (`Firmware design`, `Build`, `Checks`, `Never`),
`docs/translator.md`, `firmware/pizpast/ol/translate.h`,
`keymaps/it/*`, `keymaps/us_intl/keymap.c`,
`hardware/layout/kle-layout.json` (the keycap legends).

Reference: `quantum/keymap_extras/keymap_uk.h` of vial-qmk at the pinned commit
(`git -C ../pizpast-vial/.scratch/ref/vial-qmk show HEAD:quantum/keymap_extras/keymap_uk.h`;
the file is not in that sparse checkout's working tree).

## Background

- **What UK types by itself** (`keymap_uk.h`, the Windows layout; Normal and
  Shift are the same on Linux `gb`, checked with `xkbcli compile-keymap --layout gb`):
  `1 !` `2 "` `3 £` `4 $` (AltGr `€`) `5 %` `6 ^` `7 &` `8 *` `9 (` `0 )`
  `- _` `= +` `[ {` `] }` `; :` `' @` `# ~` (`KC_NUHS`, the ISO key left of
  Enter) `\ |` (`KC_NUBS`, the ISO key right of left Shift) `, <` `. >` `/ ?`
  `` ` ¬ `` (AltGr `¦`). No dead keys.
- **The keycap legends against it** (Normal / Shift; `=` means UK already
  does it, so the table entry stays `_______`):

  | Key | Legend | Layer 0 | Shift table |
  |---|---|---|---|
  | `1` `2` `4` `5` `6` `7` | `! " $ % ^ &` | `KC_n` | = |
  | `3` | `@` | `KC_3` | `UK_AT` (UK has `£`) |
  | `8` `9` `0` | `( ) =` | `KC_n` | `UK_LPRN` `UK_RPRN` `UK_EQL` |
  | right of P | `+ ?` | `UK_PLUS` | `UK_QUES` |
  | right of L | `[ {` `] }` | `UK_LBRC` `UK_RBRC` | = |
  | right of M | `, ;` `. :` `- _` | `UK_COMM` `UK_DOT` `UK_MINS` | `UK_SCLN` `UK_COLN` = |
  | left of Space | `< >` | `UK_LABK` | `UK_RABK` |
  | right of Fn | `' *` | `UK_QUOT` | `UK_ASTR` (UK has `@`) |
  | | `/ \` AltGr `\|` | `UK_SLSH` | `UK_BSLS`, AltGr table `UK_PIPE` |
  | | `€ #` (AltGr `~`, decision 2: not on the keycap) | `UK_EURO` | `UK_HASH`, AltGr table `UK_TILD` |
  | Esc, Fn layer | `` ` `` `¬` `¦` | `UK_GRV` on the Fn layer | (Fn keys are not translated: Shift and AltGr give UK's own `¬` and `¦`) |

  Every legend on the keycaps can be typed on UK: nothing is left out.
- **Plain UK and AltGr.** `keymap_uk.h` describes Windows UK, where
  AltGr+vowel types `á é í ó ú` and AltGr+`` ` `` types `¦`. Plain Linux `gb`
  types `æ e → ø ↓` and `|` there. Only `€` on AltGr+4 is common to both, so
  the tables rely on AltGr only for `€`; `|` is `S(KC_NUBS)`, with the user's
  AltGr removed by the engine.
- **UK extended** (the host this firmware names; Windows "United Kingdom
  Extended" and xkb `gb(extd)` agree on all of this, the Linux side checked
  with `xkbcli compile-keymap --layout gb --variant extd`): Normal and Shift as
  plain UK, except that `` ` `` is a **dead key** (it waits for the next key:
  `` ` `` then `e` types `è`, `` ` `` then Space types `` ` ``). AltGr+vowel
  types `á é í ó ú` (capitals with Shift), AltGr+C `ç`, AltGr+4 `€`,
  AltGr+`` ` `` `¦`; AltGr+2, AltGr+6, AltGr+`'` and AltGr+`#` are the dead
  keys `¨ ^ ´ ~`. `~` itself (Shift+`#`) is not dead.
- **Accented vowels.** The `it` firmware puts `à è ì ò ù` on AltGr+vowel and
  `é` on Shift+AltGr+E; `us_intl` leaves them to the host (`á é í ó ú`). On UK
  extended the host types `á é í ó ú` on AltGr+vowel by itself, so the tables
  stay `_______` there, as in `us_intl`. A grave vowel is two keypresses
  (Fn+Esc, then the vowel): a table entry is one keycode, so it cannot be one.
- **One Vial UID for all firmwares**: `it` and `us_intl` have the same
  `config.h` (same `VIAL_KEYBOARD_UID`) and `rules.mk`; `uk` copies them. The
  app tells the firmwares apart by `pizpast.firmware`.
- **`host_layout`**: the other two use vial-gui's names (`keymaps.py`):
  `"Italian (QWERTY)"`, `"US - International (QWERTY)"`. vial-gui has only
  `"UK (QWERTY)"`, the plain layout, so this firmware names
  `"UK - Extended (QWERTY)"`, in the same pattern. (In stock Vial, pick
  "UK (QWERTY)": its labels differ only at AltGr and for the dead `` ` ``.)

## Decisions (the user's, 2026-11-12)

1. **Host layout: UK extended.** Acute vowels come from the host (AltGr+vowel)
   on Windows and Linux; grave vowels with the dead `` ` `` (Fn+Esc, then the
   vowel); Fn+Esc is therefore a dead key. No table entries for vowels.
2. **`~`** (Shift+`#`, not on any keycap): AltGr on the `€ #` key, `UK_TILD`
   in the AltGr table at (4,11).
3. **Build**: CI after the user pushes. The qmk CLI and a full vial-qmk
   checkout are not on the dev machine; nothing is compiled locally. The names
   are checked against `keymap_uk.h`, and the app's
   `scripts/pizpast-defaults.ts` resolves the whole keymap to keycodes.

## Constraints

- Never flash, never claim a hardware test. No push.
- vial-qmk is not modified; nothing else under `firmware/pizpast/ol/` changes
  (`ol.c`, `translate.h`, `keyboard.json`, the other keymaps).
- No personal information or absolute paths in files.
- One commit per step with the step's heading; tick it here.

## Steps

### [x] 1. `feat(firmware): UK keymap`

Files: new `firmware/pizpast/ol/keymaps/uk/{keymap.c, config.h, rules.mk, vial.json}`.

- `config.h` and `rules.mk`: byte-for-byte copies of `keymaps/it/`.
- `vial.json`: copy of `keymaps/it/vial.json` with `"firmware": "uk"` and
  `"host_layout": "UK - Extended (QWERTY)"`; nothing else differs.
- `keymap.c`: same shape, header comment and column alignment as
  `keymaps/it/keymap.c`, with `#include "keymap_uk.h"` and the comment
  `PizPast OL - UK firmware.` / `Set the OS keyboard layout to "United Kingdom
  Extended" on Windows, "English (UK, extended, Windows)" on Linux.` / `The
  plain UK layout types the same keycap legends; only AltGr+vowel and the dead
  keys differ.` The layers:

  ```c
  [L_NORMAL] = LAYOUT(
      KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSPC,
      KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     UK_PLUS,
      KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     UK_LBRC,  UK_RBRC,
      KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     UK_COMM,  UK_DOT,   UK_MINS,  KC_RSFT,
      KC_LCTL,  KC_LGUI,  KC_LALT,  UK_LABK,  KC_SPC,   KC_ENT,   KC_RALT,  MO(L_FN), UK_QUOT,  UK_SLSH,  UK_EURO
  ),
  [L_SHIFT] = LAYOUT(
      _______, _______, _______, UK_AT,   _______, _______, _______, _______, UK_LPRN, UK_RPRN, UK_EQL,  _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, UK_QUES,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, UK_SCLN, UK_COLN, _______, _______,
      _______, _______, _______, UK_RABK, _______, _______, _______, _______, UK_ASTR, UK_BSLS, UK_HASH
  ),
  [L_ALTGR] = LAYOUT(           // all _______ except (4,10) and (4,11)
      ...
      _______, _______, _______, _______, _______, _______, _______, _______, _______, UK_PIPE, UK_TILD
  ),
  [L_SHIFT_ALTGR] = LAYOUT( all _______ ),
  [L_FN] = LAYOUT(              // as keymaps/us_intl, with UK_GRV on Esc
      UK_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
      _______, KC_F11,  KC_F12,  _______, ...
      ...
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______,
      _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT
  )
  ```

Verify:
- every `UK_*` name used is a `#define` of `keymap_uk.h` at the pinned commit;
- each `LAYOUT(...)` has 59 entries (12, 12, 12, 12, 11);
- `diff keymaps/it/config.h keymaps/uk/config.h` and the same for `rules.mk`
  are empty; `diff keymaps/it/vial.json keymaps/uk/vial.json` shows the two
  `pizpast` lines only; `python3 -m json.tool` accepts `vial.json`.

### [x] 2. `build(firmware): build the uk keymap`

Files: `tools/build.sh`, `.github/workflows/build.yml`.

- `tools/build.sh`: default keymaps `us_intl it uk` (the array and the usage
  comment).
- `build.yml`: `keymap: [us_intl, it, uk]`.

Verify: `bash -n tools/build.sh`; the workflow is still valid YAML
(`python3 -c 'import yaml,sys; yaml.safe_load(open(sys.argv[1]))' …` if PyYAML
is there, else by eye). No local compile (decision 3).

### [x] 3. `docs: UK firmware`

Files: `README.md`, `docs/translator.md`, `AGENTS.md`.

- `README.md`: the intro ("US-International, Italian or UK extended"), the
  firmware table (`pizpast_ol_uk.uf2`: Windows "United Kingdom Extended",
  Linux "English (UK, extended, Windows)"; plain UK works for the keycap
  legends), "every push builds the three files".
- `docs/translator.md`: the intro; `Limits` (UK extended: `` ` `` is a dead
  key, press Space after it; on the plain UK layout the keycap legends still
  come out, but AltGr+vowel differs between Windows and Linux and there are
  no grave vowels); `Default symbol layout` covers the three firmwares: the
  vowel line (UK: `á é í ó ú` native on AltGr+vowel, `à è ì ò ù` with Fn+Esc
  then the vowel), `~` on AltGr of the `€ #` key (UK only), and `` ` `` on
  Fn+Esc for UK too (with Shift `¬`, with AltGr `¦`).
- `AGENTS.md`: `Goals` 1 (UK exists, French later), `Decisions` (three
  keymaps; the UK host is UK extended, the vowels and `~`, dated 2026-11-12),
  `Firmware design` (`UK_*` from `keymap_uk.h`, the `"firmware"` and
  `"host_layout"` values, one Vial UID for all firmwares), `Build` and
  `Checks` (three keymaps), `Status` (uk written, not compiled, not flashed,
  not tested), `Next steps` (a checklist for the UK firmware like the one of
  step 1: CI build green, flash `pizpast_ol_uk.uf2`, set the OS to UK
  extended, every Shift symbol, `€ # | \ @ ~`, AltGr+vowel, Fn+Esc then a
  vowel and then Space; `Later` keeps French only).

Verify: the docs name nothing that does not exist; no build needed.

## Done means

The three steps are committed, the docs say what is true, nothing was flashed
or pushed. Left for the user: push (CI compiles the three keymaps), flash
`pizpast_ol_uk.uf2`, set the OS to UK extended and run the checklist.
