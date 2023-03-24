cls
@echo off

python make.py clean

if [%1]==[] goto standard
python make.py --region NTSC_U --flags=%1
REM python make.py --region PAL --flags=%1
goto copy

:standard
python make.py --region NTSC_U
REM python make.py --region PAL

:copy
xcopy "build/main_NTSC_U.dol" "romfs/NTSC_U/sys/main.dol" /y /f /i
xcopy "build/main_NTSC_U.dol" "romfs/NTSC_U/files/modules/for_restart.dol" /y /f /i
xcopy "build/modules/Caddie_NTSC_U.bin" "romfs/NTSC_U/files/modules/main_NTSC_U.bin" /y /f /i
xcopy "build/modules/Caddie_NTSC_U.map" "romfs/NTSC_U/files/modules/main_NTSC_U.map" /y /f /i
