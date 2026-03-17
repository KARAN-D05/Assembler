:: Windows Batchfile -> Will create a shortcut to open the manual.
@echo off
start powershell -NoExit -Command "./asm-manual"
exit
