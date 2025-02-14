choco install archiver -y
choco install doxygen.install -y
choco install graphviz -y

git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
git checkout tags/2023.04.15
.\bootstrap-vcpkg.bat
(Get-Content scripts\cmake\vcpkg_acquire_msys.cmake) -replace 'grep-3.0-2-x86_64.pkg.tar.xz', 'grep-1~3.0-6-x86_64.pkg.tar.zst' | Set-Content scripts\cmake\vcpkg_acquire_msys.cmake
(Get-Content scripts\cmake\vcpkg_acquire_msys.cmake) -replace 'c784d5f8a929ae251f2ffaccf7ab0b3936ae9f012041e8f074826dd6077ad0a859abba19feade1e71b3289cc640626dfe827afe91c272b38a1808f228f2fdd00', '79b4c652082db04c2ca8a46ed43a86d74c47112932802b7c463469d2b73e731003adb1daf06b08cf75dc1087f0e2cdfa6fec0e8386ada47714b4cff8a2d841e1' | Set-Content scripts\cmake\vcpkg_acquire_msys.cmake
mkdir downloads
Invoke-WebRequest -Uri https://github.com/microsoft/vcpkg/files/7075269/nasm-2.15.05-win32.zip -OutFile downloads\nasm-2.15.05-win32.zip
cd ..

$VCPKG_TRIPLET="x64-windows"

Get-Date | Out-File -FilePath ports\doctotext\disable_binary_cache.tmp
$Env:SOURCE_PATH = "$PWD"
$Env:VCPKG_KEEP_ENV_VARS = "SOURCE_PATH"
vcpkg\vcpkg --overlay-ports=ports install doctotext:$VCPKG_TRIPLET

$version = Get-Content vcpkg\installed\$VCPKG_TRIPLET\share\doctotext\VERSION
vcpkg\vcpkg --overlay-ports=ports export doctotext:$VCPKG_TRIPLET --raw --output=doctotext-$version --output-dir=.

New-Item doctotext-$version\text_extractor.bat -ItemType File -Value "@`"%~dp0\\installed\\x64-windows\\tools\\text_extractor.bat`" %*"
New-Item doctotext-$version\c_text_extractor.bat -ItemType File -Value "@`"%~dp0\\installed\\x64-windows\\tools\\c_text_extractor.bat`" %*"

Compress-Archive -LiteralPath doctotext-$version -DestinationPath doctotext-$version-$VCPKG_TRIPLET.zip
Get-FileHash -Algorithm SHA1 doctotext-$version-$VCPKG_TRIPLET.zip > doctotext-$version-$VCPKG_TRIPLET.zip.sha1
