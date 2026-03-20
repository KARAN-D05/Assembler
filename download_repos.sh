#!/usr/bin/env bash

# Linux/macOS Repository Downloader

BASE_URL="https://github.com/KARAN-D05"
RAW_URL="https://raw.githubusercontent.com/KARAN-D05"
BRANCH="main"
REPOS=(
    "Computing_Machinery_from_Scratch"
    "Assembler"
    "Gate-Level-Perceptron"
    "8-Bit-Computer"
    "Artificial-Neuron"
    "portmap-HDL"
)
RED='\033[0;31m'; GREEN='\033[0;32m'
CYAN='\033[0;36m'; BOLD='\033[1m'; RESET='\033[0m'

if command -v curl &>/dev/null; then
    DOWNLOADER="curl"
elif command -v wget &>/dev/null; then
    DOWNLOADER="wget"
else
    echo -e "${RED}Error: Neither curl nor wget is installed.${RESET}"
    exit 1
fi

download_zip() {
    local name="$1"
    local url="${BASE_URL}/${name}/archive/refs/heads/${BRANCH}.zip"
    local out="${name}.zip"
    echo -e "\n${CYAN}  Downloading ${name} ...${RESET}"
    if [ "$DOWNLOADER" = "curl" ]; then
        curl -L -o "$out" "$url" --silent
    else
        wget -O "$out" "$url" -q
    fi
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}  Done. Saved as ${out}${RESET}"
        return 0
    else
        echo -e "${RED}  Failed to download ${name}. Check your connection.${RESET}"
        return 1
    fi
}

download_utils() {
    echo -e "\n${CYAN}  Fetching utils ...${RESET}"
    mkdir -p utils
    if [ "$DOWNLOADER" = "curl" ]; then
        curl -L -o "portmap-temp.zip" "${BASE_URL}/portmap-HDL/archive/refs/heads/${BRANCH}.zip" --silent
    else
        wget -O "portmap-temp.zip" "${BASE_URL}/portmap-HDL/archive/refs/heads/${BRANCH}.zip" -q
    fi
    python3 - <<'EOF'
import zipfile, os, shutil

with zipfile.ZipFile("portmap-temp.zip") as z:
    for member in z.namelist():
        if member.startswith("portmap-HDL-main/utils/") and not member.endswith("/"):
            rel = member[len("portmap-HDL-main/utils/"):]
            dest = os.path.join("utils", rel)
            os.makedirs(os.path.dirname(dest), exist_ok=True)
            with z.open(member) as src, open(dest, "wb") as dst:
                shutil.copyfileobj(src, dst)
EOF
    rm -f "portmap-temp.zip"
    echo -e "${GREEN}  Done.${RESET}"
}

while true; do
    echo ""
    echo -e "${BOLD}============================================${RESET}"
    echo -e "${BOLD}  KARAN-D05  |  Repository Downloader      ${RESET}"
    echo -e "${BOLD}============================================${RESET}"
    echo ""
    for i in "${!REPOS[@]}"; do
        echo "  $((i+1)).  ${REPOS[$i]}"
    done
    echo "  A.  Download ALL repos"
    echo "  Q.  Quit"
    echo ""
    echo "  Enter one number, several (e.g. 1 3 5),"
    echo "  A for all, or Q to quit."
    echo -e "${BOLD}============================================${RESET}"
    echo ""
    read -rp "  Your choice: " INPUT

    if [[ "${INPUT,,}" == "q" ]]; then
        echo -e "\n  Goodbye!\n"
        exit 0
    fi

    if [[ "${INPUT,,}" == "a" ]]; then
        INPUT="1 2 3 4 5 6"
    fi

    DOWNLOADED=0
    FAILED=0

    for TOKEN in $INPUT; do
        if ! [[ "$TOKEN" =~ ^[1-6]$ ]]; then
            echo -e "\n${RED}  \"${TOKEN}\" is not a valid option -- skipping.${RESET}"
            continue
        fi
        INDEX=$((TOKEN - 1))
        RNAME="${REPOS[$INDEX]}"
        if download_zip "$RNAME"; then
            ((DOWNLOADED++))
        else
            ((FAILED++))
        fi
    done

    if [ "$DOWNLOADED" -gt 0 ]; then
        download_utils
    fi

    echo ""
    echo -e "${BOLD}============================================${RESET}"
    echo -e "  Done!  Downloaded: ${GREEN}${DOWNLOADED}${RESET}   Failed: ${RED}${FAILED}${RESET}"
    echo -e "${BOLD}============================================${RESET}"
    echo ""
    read -rp "  Press Enter to return to menu..."
done
