#!/bin/bash
# ============================================================
#  run-stack-manual.sh
#  Full Computing Stack Manual launcher
#  Covers: RAM Hardware (V0-V4) + Assembly Language (v0.1-v0.3)
#  Repo: Assembler
# ============================================================

set -e

MANUAL_URL="https://raw.githubusercontent.com/KARAN-D05/Assembler/main/stack-manual/stack-manual.c"
BINARY="./stack-manual"
SOURCE="stack-manual.c"

# Check if compiled binary already exists
if [ ! -f "$BINARY" ]; then
    echo "Fetching stack-manual..."
    curl -fsSL "$MANUAL_URL" -o "$SOURCE"

    echo "Compiling..."
    gcc "$SOURCE" -o "$BINARY"

    echo "Done. Launching manual..."
    echo ""
fi

$BINARY "$@"
