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

*Part of the Assembler project by KARAN-D05*