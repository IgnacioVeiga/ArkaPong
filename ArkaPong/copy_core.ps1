param([Parameter(Mandatory=$true)][string]$CoreRoot)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$coreRootPath = Resolve-Path $CoreRoot
$srcInc = Join-Path $coreRootPath 'include'
$srcBuild = Join-Path $coreRootPath 'build'
$dest = Join-Path (Get-Location) 'core_local'

if (-not (Test-Path $srcInc)) { Write-Error "Missing $srcInc"; exit 1 }

New-Item -ItemType Directory -Path (Join-Path $dest 'include') -Force | Out-Null
New-Item -ItemType Directory -Path (Join-Path $dest 'lib') -Force | Out-Null
Copy-Item -Recurse (Join-Path $srcInc '*') (Join-Path $dest 'include') -Force

@(
    'Core.lib',
    'libCore.lib',
    'Core.dll',
    'libCore.so',
    'libCore.dylib',
    'libCore.a'
) | ForEach-Object {
    $candidate = Join-Path $srcBuild $_
    if (Test-Path $candidate) {
        Copy-Item $candidate (Join-Path $dest 'lib') -Force
    }
}

$copiedBinaries = Get-ChildItem -Path (Join-Path $dest 'lib') -File -ErrorAction SilentlyContinue
if (-not $copiedBinaries) {
    Write-Warning "No binaries found in $srcBuild. Ensure Core was built."
}
Write-Host "Core copied to $dest"
