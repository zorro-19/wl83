






@echo off

@echo *********************************************************************
@echo AC792N SDK
@echo *********************************************************************
@echo %date%

cd /d %~dp0

echo %*


set OBJDUMP=C:\JL\pi32\bin\llvm-objdump.exe
set OBJCOPY=C:\JL\pi32\bin\llvm-objcopy.exe
set ELFFILE=sdk.elf

REM %OBJDUMP% -D -address-mask=0x1ffffff -print-dbg %ELFFILE% > sdk.lst
%OBJCOPY% -O binary -j .text %ELFFILE% text.bin
%OBJCOPY% -O binary -j .data %ELFFILE% data.bin
%OBJCOPY% -O binary -j .ram0_data %ELFFILE% ram0_data.bin
%OBJCOPY% -O binary -j .dcache_ram_data %ELFFILE% dcache_ram_data.bin
%OBJCOPY% -O binary -j .video_ram_data %ELFFILE% video_ram_data.bin

%OBJDUMP% -section-headers -address-mask=0x1ffffff %ELFFILE%
%OBJDUMP% -t %ELFFILE% > symbol_tbl.txt

copy /b text.bin+data.bin+ram0_data.bin+dcache_ram_data.bin+video_ram_data.bin app.bin
set UI_RES_PREFIX=dvr_ly_




packres\packres.exe -n tone -o packres/AUPACKRES dvr_aud_res
packres\packres.exe -n ui -o packres/UIPACKRES %UI_RES_PREFIX%ui_res



packres\packres.exe -n logo -o packres/LOGOPACKRES poweronoff_res






REM set KEY_FILE=-key JL_792N-XXXX.key
REM set KEY_FILE=-key1 JL_792N-XXXX.key1 -mkey JL_792N-XXXX.mkey

set CFG_FILE=cfg

REM ����²���-update_files˵��
REM 1/normal������ͨ���ļ�Ŀ¼�ṹ
REM 2/embedded����ÿ���ļ�����ǰ������һ��ͷ

REM ֻ����code + res�����ļ�
REM -update_files normal
REM ���ɵ��ļ�����Ϊ��db_update_files_data.bin

REM ֻ����Ԥ������Դ�����ļ�
REM -update_files embedded_only $(files) ,����$(files)Ϊ��Ҫ��ӵ���Դ�ļ�
REM ���ɵ��ļ�����Ϊ��db_update_files_data.bin

REM ����code + res + Ԥ������Դ�����ļ�
REM -update_files embedded $(files) ,����$(files)Ϊ��Ҫ��ӵ���Դ�ļ�
REM ���ɵ��ļ�����Ϊ��db_update_files_data.bin
isd_download.exe isd_config.ini -gen2 -tonorflash -dev wl83 -boot 0x103000 -div1 -wait 300 -uboot uboot.boot -app app.bin cfg_tool.bin -res %AUDIO_RES% %UI_RES% %CFG_FILE% %MEDIA_RES% -reboot 50 %KEY_FILE% %UPDATE_FILES% -extend-bin %EXFLASH_FILES% -output-ufw jl_isd.ufw
@REM ��������˵��
@rem -format vm
@rem -format all
@rem -reboot 500

echo %errorlevel%

@REM ɾ����ʱ�ļ�
if exist *.mp3 del *.mp3
if exist *.PIX del *.PIX
if exist *.TAB del *.TAB
if exist *.res del *.res
if exist *.sty del *.sty
@REM ���ɹ̼������ļ�
fw_add.exe -noenc -fw jl_isd.fw -add ota.bin -type 100 -out jl_isd.fw


@REM ������ýű��İ汾��Ϣ�� FW �ļ���
fw_add.exe -noenc -fw jl_isd.fw -add script.ver -out jl_isd.fw

@REM ���SDK softwate�ŵ��� FW �ļ���
fw_add.exe -noenc -fw jl_isd.fw -add version.ver -out jl_isd.fw

ufw_maker.exe -fw_to_ufw jl_isd.fw


@REM ���������ļ������ļ�
rem ufw_maker.exe -chip AC792N %ADD_KEY% -output config.ufw -res bt_cfg.cfg

ping /n 2 127.1>null
IF EXIST null del null

::del app.bin
del video_ram_data.bin
del dcache_ram_data.bin
del data.bin
del ram0_data.bin
del text.bin
::�˳���ǰ������ӷ���ֵ(0),���ܶ��������Ƕ�׵���������
exit /b 0
