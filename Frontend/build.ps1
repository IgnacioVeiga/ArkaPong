param([string]$CoreRoot)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

if (-not (Test-Path -Path build)) { New-Item -ItemType Directory -Path build | Out-Null }
Push-Location build
if ($CoreRoot) {
    $coreInc = Join-Path (Resolve-Path $CoreRoot) 'include'
    $coreLib = Join-Path (Resolve-Path $CoreRoot) 'build\libCore.so'
    cmake .. -DCORE_INCLUDE_DIR="$coreInc" -DCORE_LIBRARY="$coreLib"
} else {
    cmake ..
}
cmake --build .
Pop-Location
Write-Host "Frontend built"