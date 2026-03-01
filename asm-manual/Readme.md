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

The script will download `asm-manual.c`, compile it and launch it automatically.

---

## Requirements

GCC must be installed. Check if you have it:
```bash
gcc --version
```

If not installed:

| OS            | Command                       |
|---------------|-------------------------------|
| Ubuntu/Debian | `sudo apt install gcc`        |
| Mac           | `xcode-select --install`      |

---

## After First Run

Once compiled you do not need the script again.
Just run the binary directly:
```bash
./asm-manual
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
| exit    | Quit the program                     |

---

## Files

| File                 | Description                        |
|----------------------|------------------------------------|
| `asm-manual.c`       | Source code of the manual          |
| `run-asm-manual.sh`  | Bash script — download and run     |

---

*Part of the Custom Hardware Assembler project by KARAN-D05*
