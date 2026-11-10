#!/usr/bin/env bash
# Build the firmware locally (Linux / WSL / QMK MSYS).
# Usage: tools/build.sh [keymap...]      default: us_intl it
# Needs a vial-qmk checkout set up with `qmk setup` (or the QMK MSYS tools).
# VIAL_QMK=/path/to/vial-qmk tools/build.sh    to point at a different checkout.
set -euo pipefail
REPO="$(cd "$(dirname "$0")/.." && pwd)"
VIAL_QMK="${VIAL_QMK:-$HOME/vial-qmk}"
if [ $# -gt 0 ]; then KEYMAPS=("$@"); else KEYMAPS=(us_intl it); fi

rm -rf "$VIAL_QMK/keyboards/pizpast"
cp -r "$REPO/firmware/pizpast" "$VIAL_QMK/keyboards/"
mkdir -p "$REPO/build"
for km in "${KEYMAPS[@]}"; do
  (cd "$VIAL_QMK" && QMK_HOME="$VIAL_QMK" qmk compile -kb pizpast/ol -km "$km")
  cp "$VIAL_QMK/pizpast_ol_${km}.uf2" "$REPO/build/"
done
echo "Firmware in $REPO/build/"
