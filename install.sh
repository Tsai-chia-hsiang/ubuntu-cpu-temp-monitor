#!/bin/bash

set -e

SRCDIR=./
SHARE="$HOME/.local/share"
APPDIR="$SHARE/applications"
ICONDIR="$SHARE/icons/hicolor/64x64/apps"
DESKTOP_FILE="$APPDIR/cputemp.desktop"

if [ ! -d "$APPDIR" ]; then
    echo "Creating App Dir: $APPDIR..."
    mkdir -p "$APPDIR"
fi

cat > "$DESKTOP_FILE" <<EOF
[Desktop Entry]
Type=Application
Name=CPU Temp Monitor
Comment=Simple CPU temperature monitor
Exec=$(realpath "$SRCDIR")/cputemp_monitor
Icon=$(realpath "$SRCDIR")/pics/icon.png
Terminal=false
Categories=Utility;
StartupWMClass=cputemp_monitor
EOF

echo "Desktop entry installed at $DESKTOP_FILE"

if [ ! -d "$ICONDIR" ]; then
    echo "Creating Icon Dir: $ICONDIR ..."
    mkdir -p "$ICONDIR"
fi

if [ ! -L "$ICONDIR/cputemp.png" ] && [ ! -e "$ICONDIR/cputemp.png" ]; then
    echo "Creating symlink: $ICONDIR/cputemp.png -> $(realpath "$SRCDIR")/pics/icon.png"
    ln -s "$(realpath "$SRCDIR")/pics/icon.png" "$ICONDIR/cputemp.png"
else
    echo "$ICONDIR/cputemp.png already exists (file or symlink)"
fi

echo "Run 'kbuildsycoca6' to refresh KDE application cache."
kbuildsycoca6
