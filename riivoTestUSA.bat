cls
@echo off

python make.py clean

if [%1]==[] goto standard
python make.py --region USA --flags=%1
goto copy

:standard
python make.py --region USA

:copy
xcopy "build/main_USA.dol" "riivo/caddie/sys/main.dol" /y /f /i
xcopy "build/modules/Caddie_USA.bin" "riivo/caddie/files/modules/main.bin" /y /f /i