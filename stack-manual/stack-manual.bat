:: Windows Batchfile -> Will create a shortcut to open the manual.
@echo off
start powershell -NoExit -Command "./stack-manual"
exit
