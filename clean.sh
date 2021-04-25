#!/usr/bin/env bash

rm -rf "./target/Icon.iconset"
rm -rf "./target/installer"
rm -rf "./target/PopSim"
rm -rf "./target/PyInstaller"
rm -rf "./target/Icon.icns"
rm -rf "./target/PopSim.app"

find . -type f -name "._*" -delete
find . -type f -name ".DS_Store" -delete

cd "src" || exit

find . -type f -name "*.py[co]" -delete
find . -type d -name "__pycache__" -delete
find . -type d -name ".pytest_cache" -exec rm -rf {} \;
