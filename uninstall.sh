#!/bin/bash
set -e

SHARE="$HOME/.local/share"
APPDIR="$SHARE/applications"
ICONDIR="$SHARE/icons/hicolor/64x64/apps"
DESKTOP_FILE="$APPDIR/cputemp.desktop"

if [ -f "$DESKTOP_FILE" ]; then
    echo "Delete desktop entry $DESKTOP_FILE"
    rm -rf "$DESKTOP_FILE"
fi

if [ -e "$ICONDIR/cputemp.png" ]; then
    echo "Delet symbolic link of icon picture: $ICONDIR/cputemp.png"
    rm -f "$ICONDIR/cputemp.png"
fi

echo "Run 'kbuildsycoca6' to refresh KDE application cache."
kbuildsycoca6