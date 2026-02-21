@echo off

if not exist build mkdir build
pushd build

cl ..\src\main.cpp ..\src\tgaimage.cpp ..\src\model.cpp ..\src\renderer.cpp /EHsc /O2 /MD /Fe:rasterizer.exe
@ cl ..\src\test.cpp ..\src\tgaimage.cpp ..\src\renderer.cpp /EHsc /O2 /W3 /MD /Fe:rasterizer_test.exe

popd
