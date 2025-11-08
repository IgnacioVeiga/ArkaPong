# Run ArkaPong: prefer build\bin\ArkaPong.exe, then build\bin\ArkaPong, then build\
if (Test-Path -Path build\bin\ArkaPong\ArkaPong.exe) {
    Set-Location build\bin\ArkaPong; .\ArkaPong.exe; exit
} elseif (Test-Path -Path build\bin\ArkaPong\ArkaPong) {
    Set-Location build\bin\ArkaPong; .\ArkaPong; exit
} elseif (Test-Path -Path build\bin\ArkaPong.exe) {
    Set-Location build\bin; .\ArkaPong.exe; exit
} elseif (Test-Path -Path build\ArkaPong.exe) {
    Set-Location build; .\ArkaPong.exe; exit
} elseif (Test-Path -Path build\ArkaPong) {
    Set-Location build; .\ArkaPong; exit
}

Write-Host "Executable not found in build\bin or build\. Please build first."; exit 1