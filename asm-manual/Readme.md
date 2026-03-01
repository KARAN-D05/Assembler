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
