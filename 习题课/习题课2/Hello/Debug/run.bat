@echo off
rem run.bat

rem 设置命令提示符，不带路径，只含驱动器符号及大于符号
prompt $N$G

:menu
choice /m "Your choice " /c 123456780
rem errorlevel 应倒序编写
if errorlevel==9 goto 0
if errorlevel==8 goto 8
if errorlevel==7 goto 7
if errorlevel==6 goto 6
if errorlevel==5 goto 5
if errorlevel==4 goto 4
if errorlevel==3 goto 3
if errorlevel==2 goto 2
if errorlevel==1 goto 1

:p
pause
goto menu

:1
echo on
Hello
@echo off
goto p

:2
echo on
Hello < Input.txt
@echo off
goto p

:3
echo on
Hello > Output.txt
@echo off
goto p

:4
echo on
Hello >> Output.txt
@echo off
goto p

:5
echo on
Hello < Input.txt > Output.txt
@echo off
goto p

:6
echo on
Hello < Input.txt >> Output.txt
@echo off
goto p

:7
echo on
type Input.txt | Hello
@echo off
goto p

:8
echo on
type Input.txt | Hello > Output.txt
@echo off
goto p

:0
echo Bye-bye
pause
