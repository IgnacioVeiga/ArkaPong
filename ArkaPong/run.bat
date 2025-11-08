@echo off
setlocal
REM Run ArkaPong: prefer build\bin\ArkaPong.exe, fallback to build\
if exist build\bin\ArkaPong\ArkaPong.exe (
  cd build\bin\ArkaPong
  ArkaPong.exe
  goto :eof
)
if exist build\bin\ArkaPong\ArkaPong (
  cd build\bin\ArkaPong
  ArkaPong
  goto :eof
)
if exist build\bin\ArkaPong.exe (
  cd build\bin
  ArkaPong.exe
  goto :eof
)
if exist build\ArkaPong.exe (
  cd build
  ArkaPong.exe
  goto :eof
)
if exist build\ArkaPong (
  cd build
  ArkaPong
  goto :eof
)
echo Executable not found in build\bin or build\. Please build first.
exit /b 1
