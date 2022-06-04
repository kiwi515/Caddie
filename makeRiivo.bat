cls
@echo off

python make.py clean

if [%1]==[] goto standard
python make.py --region NTSC_U --flags=%1
python make.py --region PAL --flags=%1
goto copy

:standard
python make.py --region NTSC_U
python make.py --region PAL

:copy
xcopy "build/main_NTSC_U.dol" "riivo/caddie/sys/main_NTSC_U.dol" /y /f /i
xcopy "build/modules/Caddie_NTSC_U.bin" "riivo/caddie/files/modules/main_NTSC_U.bin" /y /f /i
xcopy "build/main_PAL.dol" "riivo/caddie/sys/main_PAL.dol" /y /f /i
xcopy "build/modules/Caddie_PAL.bin" "riivo/caddie/files/modules/main_PAL.bin" /y /f /i
