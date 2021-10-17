cls
python make.py clean
python make.py --region USA
xcopy "build/main_USA.dol" "romfs/USA/sys/main.dol" /y /f /i
xcopy "build/modules/Caddie_USA.bin" "romfs/USA/files/modules/main.bin" /y /f /i