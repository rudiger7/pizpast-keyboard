# PizPast Keyboard

A 59-key keyboard: custom KiCad PCB, RP2040-Zero, MX switches, 3D-printed case and keycaps, QMK + Vial firmware.

It works with the **standard** OS layout (US-International, Italian or UK extended) on Windows and Linux. No custom layout to install: the firmware decides what every key sends, including with Shift and AltGr.

## Repo layout

```
hardware/
  kicad/          schematic, PCB, JLCPCB production files
  layout/         keyboard-layout-editor files (kle-layout.json is current), ai03 plate.dxf
case/
  legacy-fusion/  old Fusion 360 STLs (to be replaced by a FreeCAD model)
keycaps/
  legacy/         old printable keycaps + legend SVGs
firmware/
  pizpast/ol/     QMK keyboard (copied into vial-qmk at build time)
docs/
  translator.md   how the Shift / AltGr tables work
  legacy-windows-layout/   the old .klc Windows layouts (no longer needed)
tools/build.sh    local build
tools/github-build.yml   GitHub Actions build -> move to .github/workflows/build.yml
```

## Firmware

| File | OS layout to select |
|---|---|
| `pizpast_ol_us_intl.uf2` | English (US, International) / Linux: "English (US, intl., with dead keys)" |
| `pizpast_ol_it.uf2` | Italian |
| `pizpast_ol_uk.uf2` | Windows: "United Kingdom Extended" / Linux: "English (UK, extended, Windows)". The plain UK layout also types the keycap legends. |

### Flash

1. Hold **ESC** while plugging in the keyboard (or hold BOOT on the RP2040-Zero). A drive called `RPI-RP2` appears.
2. Copy the `.uf2` onto it. The keyboard reboots.

### Build

- **GitHub:** every push builds the three files. Download them from the Actions run ("Artifacts").
- **Locally:** set up [vial-qmk](https://github.com/vial-kb/vial-qmk) with `qmk setup` (Linux/WSL) or QMK MSYS (Windows), then run `VIAL_QMK=~/vial-qmk tools/build.sh`. Output goes in `build/`.

The keyboard code lives only in this repo. vial-qmk is used unmodified, pinned in the GitHub workflow.

### Configure

Open [Vial](https://get.vial.today/). Unlock with **ESC + bottom-right key**. Layers 1-3 are the Shift / AltGr translation tables, layer 4 is Fn. See [docs/translator.md](docs/translator.md).

## Hardware

- Matrix 5x12, COL2ROW, 1N4148 diodes
- Cols: GP5 GP6 GP15 GP26 GP27 GP28 GP29 GP4 GP3 GP2 GP1 GP0
- Rows: GP13 GP14 GP9 GP8 GP7
- PCB 3D model: export from KiCad (`File > Export > STEP`). It's not in git because it's 37 MB.

## License

GPL-3.0-or-later. See [LICENSE](LICENSE).
