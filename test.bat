@echo off
:loop
gcc main.c header.h -o main.exe
chcp 65001
main.exe
@pause
goto loop
