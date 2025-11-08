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
if exist "%CORE_ROOT%\build\libCore.so" (
  copy "%CORE_ROOT%\build\libCore.so" "core_local\lib\" >nul
) else if exist "%CORE_ROOT%\build\Core.dll" (
  copy "%CORE_ROOT%\build\Core.dll" "core_local\lib\" >nul
) else (
  echo No binaries found in %CORE_ROOT%\build. Ensure Core was built.
)
echo Core copied to core_local\