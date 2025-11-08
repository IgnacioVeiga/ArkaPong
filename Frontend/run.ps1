if (-not (Test-Path -Path build\Frontend.exe -PathType Leaf -ErrorAction SilentlyContinue) -and -not (Test-Path -Path build\Frontend -ErrorAction SilentlyContinue)) {
    Write-Host "No encuentro el ejecutable en build/. Compila primero."; exit 1
}
Set-Location build
    if (Test-Path -Path build\bin\Frontend\Frontend.exe) {
        Set-Location build\bin\Frontend; .\Frontend.exe; exit
    } elseif (Test-Path -Path build\bin\Frontend\Frontend) {
        Set-Location build\bin\Frontend; .\Frontend; exit
    } elseif (Test-Path -Path build\bin\Frontend.exe) {
        Set-Location build\bin; .\Frontend.exe; exit
    } elseif (Test-Path -Path build\Frontend.exe) {
        Set-Location build; .\Frontend.exe; exit
    } elseif (Test-Path -Path build\Frontend) {
        Set-Location build; .\Frontend; exit
    }

    Write-Host "Executable not found in build\bin or build\. Please build first."; exit 1
Pop-Location