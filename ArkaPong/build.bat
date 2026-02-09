@echo off
REM Build ArkaPong (Windows cmd). Usage: build.bat [path_to_core_root]
if not exist build mkdir build
cd build
if "%1"=="" (
  cmake ..
) else (
  set CORE_ROOT=%~1
  set CORE_INC=%CORE_ROOT%\include
  set CORE_LIB=
  if exist "%CORE_ROOT%\build\Core.lib" set CORE_LIB=%CORE_ROOT%\build\Core.lib
  if not defined CORE_LIB if exist "%CORE_ROOT%\build\libCore.lib" set CORE_LIB=%CORE_ROOT%\build\libCore.lib
  if not defined CORE_LIB if exist "%CORE_ROOT%\build\Core.dll" set CORE_LIB=%CORE_ROOT%\build\Core.dll
  if not defined CORE_LIB if exist "%CORE_ROOT%\build\libCore.so" set CORE_LIB=%CORE_ROOT%\build\libCore.so
  if not defined CORE_LIB if exist "%CORE_ROOT%\build\libCore.dylib" set CORE_LIB=%CORE_ROOT%\build\libCore.dylib
  if defined CORE_LIB (
    cmake .. -DCORE_INCLUDE_DIR="%CORE_INC%" -DCORE_LIBRARY="%CORE_LIB%"
  ) else (
    echo Core library not found in %CORE_ROOT%\build. Configuring with include path only.
    cmake .. -DCORE_INCLUDE_DIR="%CORE_INC%"
  )
)
cmake --build . -- /m
echo ArkaPong built in %cd%
