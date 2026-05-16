@echo off

set codename=GreatCalculator
set exename=GreatCalculator
set command=-static -O2 -Wall -std=c++14

:: ------ 生成 ESC 字符 ------
for /f %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"
set "CERR=%ESC%[31m"
set "CWRN=%ESC%[33m"
set "CSUC=%ESC%[32m"
set "CRST=%ESC%[0m"

echo 检查变量:
if not defined codename (
	echo   %CERR%错误: 源代码名称为空%CRST%
	pause
	exit
)
if not defined exename (
	echo   %CWRN%警告: 未指定程序名称，默认与源代码名称相同%CRST%
	set exename=%codename%
)
echo %CSUC%变量无问题%CRST%
echo.

echo 检查文件:
if not exist "%codename%.cpp" (
	echo   %CERR%错误: %codename%.cpp不存在%CRST%
	pause
	exit
)
if not exist "icon.ico" (
	echo   %CERR%错误: icon.ico不存在%CRST%
	pause
	exit
)
echo %CSUC%文件无问题%CRST%
echo.

echo 生成资源文件
echo MAINICON ICON "icon.ico" > "%codename%.rc"
echo 编译图标文件:
windres "%codename%.rc" -O coff -o "%codename%.res"
if not errorlevel 1 (
	echo   %CSUC%图标编译成功%CRST%
) else (
	echo   %CERR%图标编译失败%CRST%
	pause
	exit
)
echo.

echo 开始编译:
g++ "%codename%.cpp" "%codename%.res" -o "%exename%.exe" %command%
if not errorlevel 1 (
	echo   %CSUC%源代码编译成功%CRST%
) else (
	echo   %CERR%源代码编译失败%CERR%
)
REM errorlevel: 上一行程序返回的值, 0代表正常。
REM if not errorlevel 1的意思是!(errorlevel >= 1)
echo 删除资源文件
del %codename%.rc
del %codename%.res
pause
