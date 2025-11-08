@echo off
setlocal
REM Run Frontend: prefer build\bin\Frontend.exe, fallback to build\
if exist build\bin\Frontend\Frontend.exe (
  cd build\bin\Frontend
  Frontend.exe
  goto :eof
)
if exist build\bin\Frontend\Frontend (
  cd build\bin\Frontend
  Frontend
  goto :eof
)
if exist build\bin\Frontend.exe (
  cd build\bin
  Frontend.exe
  goto :eof
)
if exist build\Frontend.exe (
  cd build
  Frontend.exe
  goto :eof
)
if exist build\Frontend (
  cd build
  Frontend
  goto :eof
)
echo Executable not found in build\bin or build\. Please build first.
exit /b 1
