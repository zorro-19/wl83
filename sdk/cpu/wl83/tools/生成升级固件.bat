@echo off

call .\download.bat
cls

if exist upgrade\*.ufw del upgrade\*.ufw
if not exist upgrade md upgrade

start "" "note.txt"

@echo *********************************************************************
@echo 			        AC791N SDK �����ļ�����
@echo %date%
@echo *********************************************************************

echo [ ������ʽѡ�� ]
echo 1: SD��������U��������ʽ��[֧�ֵ�˫����]
echo 2: HTTP OTA��FTP����������U��������ʽ��[ֻ֧��˫����]
echo q: ȡ��
echo .

set /p var=����ǰ����ϸ�Ķ�note.txt, ��ѡ��������ʽ��    

if %var% EQU 1 (
	copy jl_isd.ufw upgrade\update.ufw
	if exist upgrade\update.ufw (
		echo -----------------------------------------------------------------
		echo .
		echo .
		echo [OK]�����ļ��Ѿ��ڵ�ǰupgradeĿ¼�����ɣ������ļ����ƣ�update.ufw
		echo .
		echo -----------------------------------------------------------------
	) else (
		echo -----------------------------------------------------------------
		echo .
		echo .
		echo [ERR]�����ļ�����ʧ�ܣ�����ϸ�Ķ�note.txt
		echo .
		echo -----------------------------------------------------------------
	)
) else if %var% EQU 2 (
	copy db_update_files_data.bin upgrade\update-ota.ufw
	if exist upgrade\update-ota.ufw (
		echo -----------------------------------------------------------------
		echo .
		echo .
		echo [OK]�����ļ��Ѿ��ڵ�ǰupgradeĿ¼�����ɣ������ļ����ƣ�update-ota.ufw
		echo .
		echo -----------------------------------------------------------------
	) else (
		echo -----------------------------------------------------------------
		echo .
		echo .
		echo [ERR]�����ļ�����ʧ�ܣ�����ϸ�Ķ�note.txt
		echo .
		echo -----------------------------------------------------------------
	)
) else if %var% EQU q (
    exit
)

pause