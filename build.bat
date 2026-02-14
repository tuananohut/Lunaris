@echo off

if not exist build mkdir build
pushd build

cl ..\src\*.cpp /EHsc /O2 /MD /Fe:rasterizer.exe

popd
