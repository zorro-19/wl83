@echo off
setlocal enabledelayedexpansion

rem 检查是否提供了文件夹路径参数
if "%~1"=="" (
    echo 请提供要处理的文件夹路径。
    exit /b 1
)

rem 配置文件夹路径和文件后缀
set "folder_path=%~1"
set "prefix_text=#ifdef CONFIG_UI_STYLE_LY_ENABLE"
set "suffix_text=#endif"

for %%f in (c h cpp hpp) do (
    for /r "%folder_path%" %%g in (*.%%f) do (

        rem 创建一个临时文件来存储修改后的内容
        set "temp_file=%%~dpg_temp.%%~xg"
        
        rem 写入前缀文本到临时文件
        (
		echo #include "app_config.h"
		echo %prefix_text% 
		)> "!temp_file!"

        rem 追加原文件内容到临时文件
        type "%%g" >> "!temp_file!"

        rem 追加后缀文本到临时文件
        (
		echo(
		echo %suffix_text%
		) >> "!temp_file!"

        rem 替换原文件为修改后的文件
        move /y "!temp_file!" "%%g"
    )
)

echo 完成处理！