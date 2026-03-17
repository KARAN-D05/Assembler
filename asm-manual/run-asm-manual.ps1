Write-Host "+--------------------------------------------------+"
Write-Host "|        asm-manual - PowerShell Installer         |"
Write-Host "+--------------------------------------------------+"

# Check GCC
Write-Host ""
Write-Host "Checking for GCC..."
$gcc = Get-Command gcc -ErrorAction SilentlyContinue
if (-not $gcc) {
    Write-Host "[ERROR] GCC not found!"
    Write-Host "  Download MinGW from: https://www.mingw-w64.org"
    Write-Host "  Then add C:\MinGW\bin to your system PATH."
    exit 1
}
Write-Host "[OK] GCC found."

# Download
Write-Host ""
Write-Host "Downloading asm-manual.c from GitHub..."
try {
    Invoke-WebRequest `
        -Uri "https://raw.githubusercontent.com/KARAN-D05/Assembler/main/asm-manual/asm-manual.c" `
        -OutFile "asm-manual.c" `
        -ErrorAction Stop
    Write-Host "[OK] Download complete."
} catch {
    Write-Host "[ERROR] Download failed. Check your internet connection."
    exit 1
}

Write-Host ""
Write-Host "Downloading ram-manual.bat from GitHub..."
try {
    Invoke-WebRequest `
        -Uri "https://raw.githubusercontent.com/KARAN-D05/Computing_Machinery_from_Scratch/main/ram-manual/ram-manual.bat" `
        -OutFile "ram-manual.bat" `
        -ErrorAction Stop
    Write-Host "[OK] Batch file download complete."
} catch {
    Write-Host "[ERROR] Batch file download failed."
    exit 1
}

# Compile
Write-Host ""
Write-Host "Compiling..."
gcc asm-manual.c -o asm-manual.exe

if ($LASTEXITCODE -ne 0) {
    Write-Host "[ERROR] Compilation failed."
    exit 1
}
Write-Host "[OK] Compilation successful."

# Run
Write-Host ""
Write-Host "Launching asm-manual..."
Write-Host "+--------------------------------------------------+"
Write-Host ""
.\asm-manual.exe
