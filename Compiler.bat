@echo off
set codename=GreatCalculator
set exename=GreatCalculator
set command=-static -O2 -Wall -std=c++14

echo 检查变量:
if not defined codename (
	echo   错误: 源代码名称为空
	pause
	exit
)
if not defined exename (
	echo   警告: 未指定程序名称，默认与源代码名称相同
	set exename=%codename%
)
echo   变量无问题

echo 检查文件:
if not exist "%codename%.cpp" (
	echo   错误: %codename%.cpp不存在
	pause
	exit
)
if not exist "icon.ico" (
	echo   错误: icon.ico不存在
	pause
	exit
)
echo   文件无问题

echo 生成资源文件
if not exist "%codename%.rc" (
	echo MAINICON ICON "icon.ico" > "%codename%.rc"
)
echo 编译图标文件:
windres "%codename%.rc" -O coff -o "%codename%.res"
if not errorlevel 1 (
	echo   图标编译成功
) else (
	echo   图标编译失败
	pause
	exit
)

echo 开始编译:
g++ "%codename%.cpp" "%codename%.res" -o "%exename%.exe" %command%
if not errorlevel 1 (
	echo   源代码编译成功
) else (
	echo   源代码编译失败
)
REM errorlevel: 上一行程序返回的值, 0代表正常。
REM if not errorlevel 1的意思是!(errorlevel >= 1)
pause