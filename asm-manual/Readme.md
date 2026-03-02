# asm-manual

A built-in reference manual for the custom ASM language
designed for custom hardware. Query the full instruction
set, mnemonics and machine code mapping directly from
your terminal.

---

## Run on Linux / Mac (Bash)

**Step 1 - Download the script**
```bash
curl -O https://raw.githubusercontent.com/KARAN-D05/Assembler/main/asm-manual/run-asm-manual.sh
```

**Step 2 - Give it permission to execute**
```bash
chmod +x run-asm-manual.sh
```

**Step 3 - Run it**
```bash
./run-asm-manual.sh
```

---

## Run on Windows (PowerShell)

**Step 1 - Download the script**
```powershell
Invoke-WebRequest -Uri "https://raw.githubusercontent.com/KARAN-D05/Assembler/main/asm-manual/run-asm-manual.ps1" -OutFile "run-asm-manual.ps1"
```

**Step 2 - Run it**
```powershell
powershell -ExecutionPolicy Bypass -File run-asm-manual.ps1
```

---

## Requirements

GCC must be installed. Check if you have it:
```
gcc --version
```

If not installed:

| OS            | Command / Link                              |
|---------------|---------------------------------------------|
| Ubuntu/Debian | `sudo apt install gcc`                      |
| Mac           | `xcode-select --install`                    |
| Windows       | https://www.mingw-w64.org then add `C:\MinGW\bin` to PATH |

---

## After First Run

Once compiled you do not need the script again.
Just run the binary directly:

**Linux / Mac:**
```bash
./asm-manual
```

**Windows:**
```powershell
.\asm-manual.exe
```

---

## Usage

Once the program is running, type the ASM version you want:

| Command | Description                          |
|---------|--------------------------------------|
| v0.1    | Data Load & Store Mnemonics          |
| v0.2    | Full Machine Code & Mnemonic Mapping |
| v0.3    | Syntax & Semantic Analysis           |
| all     | Show all versions at once            |
| search  | Search for a specific mnemonic       |
| exit    | Quit the program                     |

You can also search directly from the terminal:
```bash
./asm-manual --search LOAD
./asm-manual --search SUB
```

---

## Files

| File                  | Description                        |
|-----------------------|------------------------------------|
| `asm-manual.c`        | Source code of the manual          |
| `run-asm-manual.sh`   | Bash script for Linux / Mac        |
| `run-asm-manual.ps1`  | PowerShell script for Windows      |

---

*Part of the Assembler project by KARAN-D05*

# 📖 stack-manual

Full computing stack reference manual for the **Assembler** project and its underlying hardware — the **Repeated Arithmetic Machine (R.A.M)**.

Covers the complete stack bottom to top:

| Layer | Covers |
|---|---|
| Layer 1 — RAM Hardware | RAM Engine (V0), V1, V2, V3, V4 |
| Layer 2 — Assembly Language | asm-v0.1, asm-v0.2, asm-v0.3 + Sample Programs |

Baked directly into the toolchain. One command gives you the full reference — no browser, no file explorer.

## ▸ Quick Start

**Linux / Mac:**
```bash
curl -O https://raw.githubusercontent.com/KARAN-D05/Assembler/main/stack-manual/run-stack-manual.sh
chmod +x run-stack-manual.sh
./run-stack-manual.sh
```

**Windows:**
```powershell
Invoke-WebRequest -Uri "https://raw.githubusercontent.com/KARAN-D05/Assembler/main/stack-manual/run-stack-manual.ps1" -OutFile "run-stack-manual.ps1"
powershell -ExecutionPolicy Bypass -File run-stack-manual.ps1
```

## ▸ Search a Term Directly

```bash
# Linux / Mac
./run-stack-manual.sh --search overflow

# Windows
powershell -ExecutionPolicy Bypass -File run-stack-manual.ps1 --search overflow
```

Search spans both layers — returns matching RAM hardware components and ASM mnemonics in one result.

## ▸ Menu

```
 [Layer 1 - RAM]
  Available: V0 | V1 | V2 | V3 | V4 | ram-all

 [Layer 2 - ASM]
  Available: v0.1 | v0.2 | v0.3 | asm-all | samples

 [Other]
  Available: search | exit
```

## ▸ Files

| File | Description |
|---|---|
| `stack-manual.c` | Manual source — compile and run |
| `run-stack-manual.sh` | Linux / Mac launcher |
| `run-stack-manual.ps1` | Windows launcher |
