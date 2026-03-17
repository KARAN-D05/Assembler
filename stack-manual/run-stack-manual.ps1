# ============================================================
#  run-stack-manual.ps1
#  Full Computing Stack Manual launcher
#  Covers: RAM Hardware (V0-V4) + Assembly Language (v0.1-v0.3)
#  Repo: Assembler
# ============================================================

$ManualUrl = "https://raw.githubusercontent.com/KARAN-D05/Assembler/main/stack-manual/stack-manual.c"
$Source    = "stack-manual.c"
$Binary    = ".\stack-manual.exe"

if (-Not (Test-Path $Binary)) {
    Write-Host "Fetching stack-manual..."
    Invoke-WebRequest -Uri $ManualUrl -OutFile $Source

    Write-Host "Compiling..."
    gcc $Source -o stack-manual.exe

    Write-Host ""
Write-Host "Downloading stack-manual.bat from GitHub..."
try {
    Invoke-WebRequest `
        -Uri "https://raw.githubusercontent.com/KARAN-D05/Assembler/main/stack-manual/stack-manual.bat" `
        -OutFile "stack-manual.bat" `
        -ErrorAction Stop
    Write-Host "[OK] Batch file download complete."
} catch {
    Write-Host "[ERROR] Batch file download failed."
    exit 1
}
    
    Write-Host "Done. Launching manual..."
    Write-Host ""
}

& $Binary $args
