
@echo off

SET SCRIPT_PATH=..\/..\/..\/..\/tools
set PATH=%SCRIPT_PATH%\utils

set target_dir=..\/..\/..\/..\/apps\/wifi_camera\/lvgl_v8_ui_app
set make_file=Makefile
set orig_make_file=Makefile_orig

if not exist %target_dir% (
    echo Ŀ��Ŀ¼�����ڣ��˳�
    goto :EOF
)

if not exist %orig_make_file% (
    copy /b %make_file% %orig_make_file%
) else (
    copy /b %orig_make_file% %make_file%
)

REM ɾ��Ŀ¼�������
sed.exe -i "/%target_dir%/d" %make_file%


REM �������c�ļ�
set c_src_files="c_SRC_FILES"
for /F "usebackq delims=" %%i in (`find %target_dir% -type f -name "*.c"`) do (
	echo %%i
    sed.exe -i "/^%c_src_files%/a\\\t%%i \\\\" %make_file%
)

REM ���includeĿ¼
set inc_dir="INCLUDES"
for /F "usebackq delims=" %%i in (`find %target_dir% -type d`) do (
    sed.exe -i "/^%inc_dir%/a\\\t%%i \\\\" %make_file%
)
cd ../../../../
SET SCRIPT_PATH=tools
set PATH=%SCRIPT_PATH%\utils
make "clean_ac792n_wifi_camera"
make "ac792n_wifi_camera" -j 12
pause

