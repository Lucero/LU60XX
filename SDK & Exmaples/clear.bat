@echo off

set rfile=debug
echo remove all "%rfile%"
forfiles /p .\ /s /m %rfile% /c "cmd /c rd /q /s @path"

set rfile=release
echo remove all "%rfile%"
forfiles /p .\ /s /m %rfile% /c "cmd /c rd /q /s @path"

set rfile=x64
echo remove all "%rfile%"
forfiles /p .\ /s /m %rfile% /c "cmd /c rd /q /s @path"

set rfile=.vs
echo remove all "%rfile%"
forfiles /p .\ /s /m %rfile% /c "cmd /c rd /q /s @path"

set rfile=ipch
echo remove all "%rfile%"
forfiles /p .\ /s /m %rfile% /c "cmd /c rd /q /s @path"


set rfile=*.sdf
echo remove all "%rfile%"
del .\%rfile% /f /s /q /a


