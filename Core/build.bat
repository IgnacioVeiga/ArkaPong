@echo off
REM Build script for the Core library (Windows cmd)
if not exist build mkdir build
cd build
cmake ..
cmake --build . -- /m
echo Core built in %cd%