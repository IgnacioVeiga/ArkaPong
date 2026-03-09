param([string]$CoreRoot)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

if (-not (Test-Path -Path build)) { New-Item -ItemType Directory -Path build | Out-Null }
Push-Location build
if ($CoreRoot) {
    $coreRootPath = Resolve-Path $CoreRoot
    $coreInc = Join-Path $coreRootPath 'include'
    $coreBuild = Join-Path $coreRootPath 'build'
    $coreLibCandidates = @(
        (Join-Path $coreBuild 'lib\Core.lib'),
        (Join-Path $coreBuild 'lib\libCore.lib'),
        (Join-Path $coreBuild 'lib\libCore.so'),
        (Join-Path $coreBuild 'lib\libCore.dylib'),
        (Join-Path $coreBuild 'lib\libCore.a'),
        (Join-Path $coreBuild 'bin\Core.dll'),
        (Join-Path $coreBuild 'Core.lib'),
        (Join-Path $coreBuild 'libCore.lib'),
        (Join-Path $coreBuild 'Core.dll'),
        (Join-Path $coreBuild 'libCore.so'),
        (Join-Path $coreBuild 'libCore.dylib'),
        (Join-Path $coreBuild 'libCore.a')
    )
    $coreLib = $coreLibCandidates | Where-Object { Test-Path $_ } | Select-Object -First 1

    if ($coreLib) {
        cmake .. -DCORE_INCLUDE_DIR="$coreInc" -DCORE_LIBRARY="$coreLib"
    } else {
        Write-Warning "Core library not found in $coreBuild. Configuring with include path only."
        cmake .. -DCORE_INCLUDE_DIR="$coreInc"
    }
} else {
    cmake ..
}
cmake --build .
Pop-Location
Write-Host "Frontend built"
