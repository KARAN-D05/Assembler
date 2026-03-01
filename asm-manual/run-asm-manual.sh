#!/bin/bash

# ============================================================
#  run-asm-manual.sh
# ------------------------------------------------------------
#  This script downloads, compiles and runs asm-manual.c
#  directly from GitHub. No manual steps needed.
#
# ------------------------------------------------------------
#  HOW TO RUN THIS SCRIPT
# ------------------------------------------------------------
#
#  STEP 1 - Download this script:
#
#    curl -O https://raw.githubusercontent.com/KARAN-D05/Assembler/main/asm-manual/run-asm-manual.sh
#
#  STEP 2 - Give it permission to execute:
#
#    chmod +x run-asm-manual.sh
#
#  STEP 3 - Run it:
#
#    ./run-asm-manual.sh
#
# ------------------------------------------------------------
#  REQUIREMENTS
# ------------------------------------------------------------
#
#  - GCC must be installed.
#
#  Check if you have it:
#    gcc --version
#
#  If not installed:
#    Ubuntu/Debian -> sudo apt install gcc
#    Mac           -> xcode-select --install
#
# ------------------------------------------------------------
#  AFTER FIRST RUN
# ------------------------------------------------------------
#
#  Once compiled you do not need this script again.
#  Just run the binary directly:
#
#    ./asm-manual
#
# ============================================================

echo "+--------------------------------------------------+"
echo "|           asm-manual - Bash Installer            |"
echo "+--------------------------------------------------+"

# Check if GCC is installed
echo ""
echo "Checking for GCC..."
if ! command -v gcc &> /dev/null; then
    echo "[ERROR] GCC not found!"
    echo "Install it with:"
    echo "  Ubuntu/Debian -> sudo apt install gcc"
    echo "  Mac           -> xcode-select --install"
    exit 1
fi
echo "[OK] GCC found: $(gcc --version | head -1)"

# Check if curl is installed
echo ""
echo "Checking for curl..."
if ! command -v curl &> /dev/null; then
    echo "[ERROR] curl not found!"
    echo "Install it with:"
    echo "  Ubuntu/Debian -> sudo apt install curl"
    exit 1
fi
echo "[OK] curl found."

# Download
echo ""
echo "Downloading asm-manual.c from GitHub..."
curl -fsSL -o asm-manual.c \
    https://raw.githubusercontent.com/KARAN-D05/Assembler/main/asm-manual/asm-manual.c

if [ $? -ne 0 ]; then
    echo "[ERROR] Download failed. Check your internet connection."
    exit 1
fi
echo "[OK] Download complete."

# Compile
echo ""
echo "Compiling..."
gcc asm-manual.c -o asm-manual

if [ $? -ne 0 ]; then
    echo "[ERROR] Compilation failed."
    exit 1
fi
echo "[OK] Compilation successful."

# Run
echo ""
echo "Launching asm-manual..."
echo "+--------------------------------------------------+"
echo ""
./asm-manual
