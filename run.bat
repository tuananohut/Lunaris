@echo off

if not exist build mkdir build
pushd build

rasterizer.exe

popd
