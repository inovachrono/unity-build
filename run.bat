@echo off

set projectDir=%~dp0
cd %projectDir%
.\build\main.exe
IF EXIST imgui.ini del imgui.ini