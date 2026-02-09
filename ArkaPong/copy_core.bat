@echo off
REM Copy Core (headers + library) into core_local\
if "%1"=="" (
  echo Usage: copy_core.bat C:\\path\\to\\Core
  exit /b 1
)
set CORE_ROOT=%~1
if not exist "%CORE_ROOT%\include" (
  echo Missing %CORE_ROOT%\include
  exit /b 1
)
if not exist core_local\include mkdir core_local\include
if not exist core_local\lib mkdir core_local\lib
xcopy /E /I "%CORE_ROOT%\include\*" "core_local\include\" >nul
set FOUND_BIN=0
if exist "%CORE_ROOT%\build\Core.lib" (
  copy "%CORE_ROOT%\build\Core.lib" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_ROOT%\build\libCore.lib" (
  copy "%CORE_ROOT%\build\libCore.lib" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_ROOT%\build\Core.dll" (
  copy "%CORE_ROOT%\build\Core.dll" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_ROOT%\build\libCore.so" (
  copy "%CORE_ROOT%\build\libCore.so" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_ROOT%\build\libCore.dylib" (
  copy "%CORE_ROOT%\build\libCore.dylib" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if exist "%CORE_ROOT%\build\libCore.a" (
  copy "%CORE_ROOT%\build\libCore.a" "core_local\lib\" >nul
  set FOUND_BIN=1
)
if "%FOUND_BIN%"=="0" (
  echo No binaries found in %CORE_ROOT%\build. Ensure Core was built.
)
echo Core copied to core_local\
