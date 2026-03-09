@echo off
REM Build ArkaPong (Windows cmd). Usage: build.bat [path_to_core_root]
if not exist build mkdir build
cd build
if "%1"=="" (
  cmake ..
) else (
  set CORE_ROOT=%~1
  set CORE_INC=%CORE_ROOT%\include
  set CORE_BUILD=%CORE_ROOT%\build
  set CORE_LIB=
  if exist "%CORE_BUILD%\lib\Core.lib" set CORE_LIB=%CORE_BUILD%\lib\Core.lib
  if not defined CORE_LIB if exist "%CORE_BUILD%\lib\libCore.lib" set CORE_LIB=%CORE_BUILD%\lib\libCore.lib
  if not defined CORE_LIB if exist "%CORE_BUILD%\lib\libCore.so" set CORE_LIB=%CORE_BUILD%\lib\libCore.so
  if not defined CORE_LIB if exist "%CORE_BUILD%\lib\libCore.dylib" set CORE_LIB=%CORE_BUILD%\lib\libCore.dylib
  if not defined CORE_LIB if exist "%CORE_BUILD%\lib\libCore.a" set CORE_LIB=%CORE_BUILD%\lib\libCore.a
  if not defined CORE_LIB if exist "%CORE_BUILD%\bin\Core.dll" set CORE_LIB=%CORE_BUILD%\bin\Core.dll
  if not defined CORE_LIB if exist "%CORE_BUILD%\Core.lib" set CORE_LIB=%CORE_BUILD%\Core.lib
  if not defined CORE_LIB if exist "%CORE_BUILD%\libCore.lib" set CORE_LIB=%CORE_BUILD%\libCore.lib
  if not defined CORE_LIB if exist "%CORE_BUILD%\Core.dll" set CORE_LIB=%CORE_BUILD%\Core.dll
  if not defined CORE_LIB if exist "%CORE_BUILD%\libCore.so" set CORE_LIB=%CORE_BUILD%\libCore.so
  if not defined CORE_LIB if exist "%CORE_BUILD%\libCore.dylib" set CORE_LIB=%CORE_BUILD%\libCore.dylib
  if not defined CORE_LIB if exist "%CORE_BUILD%\libCore.a" set CORE_LIB=%CORE_BUILD%\libCore.a
  if defined CORE_LIB (
    cmake .. -DCORE_INCLUDE_DIR="%CORE_INC%" -DCORE_LIBRARY="%CORE_LIB%"
  ) else (
    echo Core library not found in %CORE_BUILD%. Configuring with include path only.
    cmake .. -DCORE_INCLUDE_DIR="%CORE_INC%"
  )
)
cmake --build . -- /m
echo ArkaPong built in %cd%
