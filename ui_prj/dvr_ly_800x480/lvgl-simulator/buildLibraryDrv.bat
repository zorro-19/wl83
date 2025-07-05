if exist "CMakeLists.txt" (
	DEL /Q "CMakeLists.txt"
)
if exist "CMakeListsDrv.txt" (
	COPY CMakeListsDrv.txt CMakeLists.txt
)
if exist "bin\libdrv.a" (
	DEL /Q "bin\libdrv.a"
)

cmake -G "CodeBlocks - MinGW Makefiles" -B cmake-build-drv-mingw
cmake.exe --build cmake-build-drv-mingw -j 8

if not exist bin (
    mkdir bin
)
COPY cmake-build-drv-mingw\libdrv.a bin\libdrv.a

if exist "CMakeLists.txt" (
	DEL /Q "CMakeLists.txt"
)
