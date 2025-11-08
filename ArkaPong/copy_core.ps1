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

if (Test-Path (Join-Path $srcBuild 'libCore.so')) {
    Copy-Item (Join-Path $srcBuild 'libCore.so') (Join-Path $dest 'lib') -Force
} elseif (Test-Path (Join-Path $srcBuild 'Core.dll')) {
    Copy-Item (Join-Path $srcBuild 'Core.dll') (Join-Path $dest 'lib') -Force
} else {
    Write-Warning "No binaries found in $srcBuild. Ensure Core was built."
}
Write-Host "Core copied to $dest"