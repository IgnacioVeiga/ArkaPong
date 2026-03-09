@echo off
REM Copy Core (headers + library) into core_local\
if "%1"=="" (
  echo Usage: copy_core.bat C:\\path\\to\\Core
  exit /b 1
)
set CORE_ROOT=%~1
set CORE_BUILD=%CORE_ROOT%\build
if not exist "%CORE_ROOT%\include" (
  echo Missing %CORE_ROOT%\include
  exit /b 1
)
if not exist core_local\include mkdir core_local\include
if not exist core_local\lib mkdir core_local\lib
xcopy /E /I "%CORE_ROOT%\include\*" "core_local\include\" >nul
set FOUND_BIN=0
if exist "%CORE_BUILD%\lib\Core.lib" (
  copy "%CORE_BUILD%\lib\Core.lib" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_BUILD%\lib\libCore.lib" (
  copy "%CORE_BUILD%\lib\libCore.lib" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_BUILD%\lib\libCore.so" (
  copy "%CORE_BUILD%\lib\libCore.so" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_BUILD%\lib\libCore.dylib" (
  copy "%CORE_BUILD%\lib\libCore.dylib" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_BUILD%\lib\libCore.a" (
  copy "%CORE_BUILD%\lib\libCore.a" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_BUILD%\bin\Core.dll" (
  copy "%CORE_BUILD%\bin\Core.dll" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_BUILD%\bin\libCore.dll" (
  copy "%CORE_BUILD%\bin\libCore.dll" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_BUILD%\Core.lib" (
  copy "%CORE_BUILD%\Core.lib" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_BUILD%\libCore.lib" (
  copy "%CORE_BUILD%\libCore.lib" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_BUILD%\Core.dll" (
  copy "%CORE_BUILD%\Core.dll" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_BUILD%\libCore.so" (
  copy "%CORE_BUILD%\libCore.so" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_BUILD%\libCore.dylib" (
  copy "%CORE_BUILD%\libCore.dylib" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_BUILD%\libCore.a" (
  copy "%CORE_BUILD%\libCore.a" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if "%FOUND_BIN%"=="0" (
  echo No binaries found in %CORE_BUILD%. Ensure Core was built.
)
echo Core copied to core_local\
