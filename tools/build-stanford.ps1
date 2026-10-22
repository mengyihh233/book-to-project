param([string]$Source='D:\Book-Learning\cpp\stanford-console\example.cpp')
$ErrorActionPreference='Stop'
$library='D:\Book-Learning\vendor\stanford-original\cpplib'
$bin='D:\c++\MYSYS2\ucrt64\bin'
$out='D:\Book-Learning\build\stanford-console'
New-Item -ItemType Directory -Path $out -Force | Out-Null
$sources=@('error','startup','simpio','strlib','hashmap','tokenscanner','random') | ForEach-Object { Join-Path $library "src\$_.cpp" }
& "$bin\g++.exe" '-std=c++11' '-g' '-I' "$library\include" $Source @sources '-o' "$out\example.exe"
if($LASTEXITCODE -ne 0){throw 'Stanford console build failed'}
$env:PATH="$bin;"+$env:PATH
& "$out\example.exe"
if($LASTEXITCODE -ne 0){throw 'Stanford console program failed'}
