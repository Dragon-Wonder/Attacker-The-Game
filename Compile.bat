@echo off
:: A few quick notes about this. 
:: %~dp0 is the directory the batch file is in, and it ends with a '\' so don't add it
:: The Batch file has to stay in the main to work as it is written right now

:: This will create the final program not a debug verison

echo Deleting old files...
::Delete the debug .exe if it exists
IF EXIST Attacker-The-Game.exe del /F Attacker-The-Game.exe
::Delete debug Stackdump if it exists (so as to not confuse me later)
IF EXIST Attacker-The-Game.exe.stackdump del /F Attacker-The-Game.exe.stackdump
echo.

::Move to the Resources directory
cd %~dp0res
echo Compiling Resources...
::Compile the resource files of the icon and boilerplate
windres my_icon.rc -O coff my_icon.res
windres boilerplate.rc -O coff boilerplate.res
echo.


::Move to the source folder
cd %~dp0src
echo Compiling source files...
::Complie each of the cpp files
echo Compiling main.cpp...
g++ -w -Os -s -c main.cpp
echo Compiling basic.cpp...
g++ -w -Os -s -c basic.cpp
echo Compiling battle.cpp
g++ -w -Os -s -c battle.cpp
echo Compiling rooms.cpp
g++ -w -Os -s -c rooms.cpp
echo Compiling save.cpp
g++ -w -Os -s -c save.cpp
echo Compiling spells.cpp
g++ -w -Os -s -c spells.cpp


::Move back to the main directory
cd %~dp0

echo.

::Complie everything together!
echo Linking everything together...
g++ -w -Os -s -o Attacker-The-Game.exe %~dp0src\main.o %~dp0src\basic.o %~dp0src\rooms.o %~dp0src\battle.o %~dp0src\save.o %~dp0src\spells.o %~dp0res\my_icon.res %~dp0res\boilerplate.res

echo. 
::Delete all the leftover parts
echo Deleting object files...
IF EXIST %~dp0res\boilerplate.res del /F %~dp0res\boilerplate.res
IF EXIST %~dp0res\my_icon.res del /F %~dp0res\my_icon.res
IF EXIST %~dp0src\main.o del /F %~dp0src\main.o
IF EXIST %~dp0src\basic.o del /F %~dp0src\basic.o
IF EXIST %~dp0src\battle.o del /F %~dp0src\battle.o
IF EXIST %~dp0src\rooms.o del /F %~dp0src\rooms.o
IF EXIST %~dp0src\save.o del /F %~dp0src\save.o
IF EXIST %~dp0src\spells.o del /F %~dp0src\spells.o
echo. 

echo Done!

