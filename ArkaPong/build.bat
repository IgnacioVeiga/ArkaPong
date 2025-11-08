@echo off
REM Build ArkaPong (Windows cmd). Usage: build.bat [path_to_core_root]
if not exist build mkdir build
cd build
if "%1"=="" (
  cmake ..
) else (
  set CORE_ROOT=%~1
  set CORE_INC=%CORE_ROOT%\include
  REM try to detect the library under CORE_ROOT\build
  cmake .. -DCORE_INCLUDE_DIR="%CORE_INC%" -DCORE_LIBRARY="%CORE_ROOT%\build\libCore.so"
)
cmake --build . -- /m
echo ArkaPong built in %cd%