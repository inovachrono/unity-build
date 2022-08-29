@echo off

REM https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-alphabetically?view=msvc-170
REM https://docs.microsoft.com/en-us/cpp/build/reference/linker-options?view=msvc-170
REM Using -MD compiler flags dynamically links to C Runtime Library which could be an issue if the user does not have the same CRT as the dev environment
REM Unable to use -EHa- compiler flag to disable exceptions since C++ libraries use them
REM Unable to use -GR- compiler flag to disable runtime information since C++ libraries use them
REM Use compiler flag -WX to treat warnings as error when writing your from scratch libraries
REM Use compiler flags -experimental:external -external:anglebrackets -external:W0 to disable warning for external files that are include using angular brackets

goto endOfLongComment
REM Project folder structure
    Project
    |------->include
    |        |----------->dependency 1
    |        |            |----------->header1.h
    |        |            |----------->header2.h
    |        |----------->dependency 2
    |                     |----------->header1.h
    |                     |----------->header2.h
    |-------->lib
    |         |-->abc.lib
    |         |-->ijk.lib
    |         |-->xyz.lib
    |-------->src
              |-->hello1.h
              |-->hello2.h
              |-->hello.main
            
:endOfLongComment

set vcvarsallBatchPath="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"
set projectDir=%~dp0
set sourceCodePath="%projectDir%\src"

cd %projectDir%
REM Don't use path with a trailing "\", compilers are stupid
set includePaths=-I "%projectDir%\include" -I "%projectDir%\src"
set libPaths=-LIBPATH:"%projectDir%\lib"
set linkLibs=kernel32.lib user32.lib gdi32.lib shell32.lib opengl32.lib glfw3.lib

set CommonCompilerFlags=-MD -nologo -Gm- -EHa- -GR- -Od -Oi -W4 -wd4201 -wd4100 -FC -Fm -Z7 -D_CRT_SECURE_NO_WARNINGS
set CommonLinkerFlags= -incremental:no -opt:ref -NOLOGO

IF NOT EXIST .\build mkdir .\build
pushd .\build
REM To delete pdb. Piping it to NUL makes the delete message not appear on console
del *.pdb > NUL 2> NUL
call %vcvarsallBatchPath% x64

REM If compiling multiple files then append their path after main.cpp's path
cl %includePaths% %CommonCompilerFlags% "%sourceCodePath%\main.cpp" /link %libPaths% %CommonLinkerFlags% %linkLibs%
popd