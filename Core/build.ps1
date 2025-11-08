param()

# Build script for the Core library (PowerShell)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

if (-not (Test-Path -Path build)) { New-Item -ItemType Directory -Path build | Out-Null }
Push-Location build
cmake ..
cmake --build .
Write-Host "Core built in $(Get-Location)"
Pop-Location