param([Parameter(Mandatory=$true)][string]$CoreRoot)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$coreRootPath = Resolve-Path $CoreRoot
$srcInc = Join-Path $coreRootPath 'include'
$srcBuild = Join-Path $coreRootPath 'build'
$srcLib = Join-Path $srcBuild 'lib'
$srcBin = Join-Path $srcBuild 'bin'
$dest = Join-Path (Get-Location) 'core_local'

if (-not (Test-Path $srcInc)) { Write-Error "Missing $srcInc"; exit 1 }

New-Item -ItemType Directory -Path (Join-Path $dest 'include') -Force | Out-Null
New-Item -ItemType Directory -Path (Join-Path $dest 'lib') -Force | Out-Null
Copy-Item -Recurse (Join-Path $srcInc '*') (Join-Path $dest 'include') -Force

@(
    (Join-Path $srcLib 'Core.lib'),
    (Join-Path $srcLib 'libCore.lib'),
    (Join-Path $srcLib 'libCore.so'),
    (Join-Path $srcLib 'libCore.dylib'),
    (Join-Path $srcLib 'libCore.a'),
    (Join-Path $srcBin 'Core.dll'),
    (Join-Path $srcBin 'libCore.dll'),
    (Join-Path $srcBuild 'Core.lib'),
    (Join-Path $srcBuild 'libCore.lib'),
    (Join-Path $srcBuild 'Core.dll'),
    (Join-Path $srcBuild 'libCore.so'),
    (Join-Path $srcBuild 'libCore.dylib'),
    (Join-Path $srcBuild 'libCore.a')
) | ForEach-Object {
    if (Test-Path $_) {
        Copy-Item $_ (Join-Path $dest 'lib') -Force
    }
}

$copiedBinaries = Get-ChildItem -Path (Join-Path $dest 'lib') -File -ErrorAction SilentlyContinue
if (-not $copiedBinaries) {
    Write-Warning "No binaries found in $srcBuild. Ensure Core was built."
}
Write-Host "Core copied to $dest"
