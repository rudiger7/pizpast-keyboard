# CLAUDE.md — PizPast Keyboard

Context for any new Claude session (Claude Code, Cowork, chat). Read this first, then `docs/translator.md`.

## The project

A self-built 59-key keyboard (project restarted in Nov 2026).

- PCB: KiCad (`hardware/kicad/`), made by JLCPCB. **Keep the PCB as-is.**
- MCU: Waveshare RP2040-Zero. MX switches soldered (no hotswap), 1N4148 THT diodes.
- Matrix 5x12, COL2ROW. Cols GP5 GP6 GP15 GP26 GP27 GP28 GP29 GP4 GP3 GP2 GP1 GP0, rows GP13 GP14 GP9 GP8 GP7.
- Row 4 has 11 keys (no 4,5). Space (4,4) and Enter (4,6) are 1.5u.
- Plate: `hardware/layout/plate.dxf` from the ai03 plate generator. KLE legends: `hardware/layout/kle-layout.json` (current).
- Old case made in Fusion 360 (`case/legacy-fusion/` STLs). Printer: Bambu Lab P1P (no AMS).

## Goals

1. Works on **standard** OS layouts (Windows + Linux), no custom layout to install. Priority: **US-International** and **Italian**. UK/French later. The symbol layout may still change.
2. Own configurator app (Tauri: Rust backend + web UI), replacing Vial for the main job: show/edit each key's Normal / Shift / AltGr output like a keycap. Lives in its **own repo**, `../pizpast-vial` (decided 2026-11-10): a vial-gui rewrite that works with any Vial keyboard, with the PizPast editor enabled by the `"pizpast"` field.
3. Understand/own the QMK side (done: firmware lives in this repo).
4. Case: smaller, separate riser, redo in FreeCAD (or code CAD like build123d). Better printable keycaps (uniform profile like DSA/XDA, KeyV2).

## Decisions so far

- **One firmware per OS layout** (`keymaps/us_intl`, `keymaps/it`). Not one layer per language. User selects the matching OS layout.
- Characters the OS layout can't type are simply unsupported (same as stock keyboards).
- Italian capitals È/É/À/Ò/Ù: Caps Lock + AltGr+vowel (libxkbcommon uppercases è etc.). Linux only, accepted (2026-11-10); no firmware macro.
- **vial-qmk used unmodified**, pinned to commit `dd43959ae5c08d8a28d38a1acf7b04e86b14a344` (2026-07-26). `firmware/pizpast/` is copied into `vial-qmk/keyboards/` at build time. No QMK fork.
- **No vial-gui fork.** vial-gui is barely maintained (3 commits in the year to Nov 2026, Python 3.6 + fbs toolchain). An earlier fork is abandoned. Use the official repo https://github.com/vial-kb/vial-gui only as protocol reference (`src/main/python/protocol/`, `keycodes/`), and vial-qmk `quantum/vial.c`, `quantum/via.c`.
- Firmware stays Vial-compatible, so stock Vial still works for macros/combos/tap dance. The own app doesn't need feature parity.

## Firmware design (the translator)

Files: `firmware/pizpast/ol/{keyboard.json, translate.h, ol.c, keymaps/<lang>/{keymap.c, config.h, rules.mk, vial.json}}`.

| Layer | Role |
|---|---|
| 0 NORMAL | what each key sends with no modifier |
| 1 SHIFT | table: output while Shift held |
| 2 ALTGR | table: output while AltGr (RALT) held |
| 3 SHIFT_ALTGR | table |
| 4 FN | real layer, `MO(L_FN)` on key (4,8) |
| 5-7 | free (`DYNAMIC_KEYMAP_LAYER_COUNT 8`) |

- Tables are never activated. `KC_TRNS` = no translation. Other entries are sent with the user's Shift/RALT removed and the entry's own mods applied (`register_code16`).
- Engine is in `process_record_kb` (`ol.c`). It only applies to keys resolving to layer 0 and is skipped while Ctrl/LAlt/GUI are held. One active translated key at a time. Suppressed mods are restored on release, and modifier releases are tracked. Auto-repeat works.
- Keymaps use QMK `keymap_extras` names (`IT_*` from `keymap_italian.h`).
- `vial.json` has an extra field for the future app: `"pizpast": {"firmware", "host_layout", "tables": {"shift":1,"altgr":2,"shift_altgr":3}, "fn_layer": 4}`. vial-qmk embeds vial.json LZMA-compressed, extra fields preserved.
- USB VID 0x5050 PID 0x0001. Vial UID `D8 26 35 56 38 02 96 48`. Vial unlock = ESC (0,0) + bottom-right (4,11). Bootmagic = hold ESC while plugging in.
- `keymaps/*/keymap.c` were generated from a table, but they're plain C now: edit them directly.

## Build

- CI: `.github/workflows/build.yml` uses the `ghcr.io/qmk/qmk_cli` container, checks out pinned vial-qmk, builds `us_intl` + `it`, and uploads `.uf2` artifacts.
- Local (Linux): `git clone --recurse-submodules https://github.com/vial-kb/vial-qmk ~/vial-qmk`, `qmk setup -H ~/vial-qmk` (or install the qmk CLI + arm-none-eabi toolchain), then `VIAL_QMK=~/vial-qmk tools/build.sh`. Output goes in `build/` (gitignored).
- Flash: hold ESC while plugging in (or hold BOOT on the RP2040-Zero), then copy the `.uf2` to the `RPI-RP2` drive.

## Status (2026-11-10)

- Both firmwares flashed and tested on hardware (Linux, US-International and Italian): they behave correctly.
- Main development OS: Linux.

## Next steps

### 1. Flash and test the firmware
- [x] Flash `pizpast_ol_us_intl.uf2`, set the OS to US-International (Linux: "English (US, intl., with dead keys)").
- [x] All letters/digits work, plus Fn layer (F1-F12, Del, arrows).
- [x] Each Shift symbol: `! " @ $ % ^ & ( ) =`, `+ ?`, `[ { ] }`, `, ; . : - _`, `< >`, `' *`, `/ \ |`, `€ #`.
- [x] Shortcuts untouched: Ctrl+Shift+T, Shift+arrows, Ctrl+C.
- [x] Hold a translated key (repeat). Type `()` and `@=` with Shift held. Release Shift before the symbol key.
- [x] Repeat on Italian (`pizpast_ol_it.uf2`): also AltGr+a/e/i/o/u = à è ì ò ù, Shift+AltGr+E = é.
- [ ] Open stock Vial: unlock works, layers 1-3 show tables, edits take effect.
- [ ] Linux needs the Vial udev rule for hidraw access (see get.vial.today Linux instructions).

### 2. Configurator
- Moved to the separate repo `../pizpast-vial`. Its `CLAUDE.md` has the stack, protocol plan and next steps.
- Firmware-side contract the app relies on: the `"pizpast"` field in `vial.json` and the table layers 1-3. Change them together with the app.

### 3. Later
- UK and French firmwares (French: digits need Shift, dead keys ^ ¨).
- Case in FreeCAD (KiCad StepUp workbench, or a STEP exported from KiCad), riser, keycaps.

## Conventions

- Own tools are written in Rust.
- Explain QMK concepts as you go: one goal of the project is to understand QMK properly.
- Public repo: no personal information in files (names, emails, personal details).

## License

GPL-3.0-or-later (`LICENSE`). Firmware files carry `SPDX-License-Identifier: GPL-3.0-or-later`.
