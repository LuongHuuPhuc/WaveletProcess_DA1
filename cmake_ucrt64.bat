::File build cmake cho thu vien chua ma nguon C/C++ thuong
@echo off
setlocal

::Thiet lap trinh bien dich su dung MSYS2 ucrt64 (khong thi se mac dinh la duong dan cua MSVC)
set CC="C:/msys64/ucrt64/bin/gcc.exe"
set CXX="C:/msys64/ucrt64/bin/g++.exe"

::Set duong dan toi CMakeLists tong 
set cmake_path="D:/C-C++_project/WaveletProcess"
set build_path="%cmake_path%/build"

::Di chuyen vao thu muc chua file
cd /d "%~dp0"
if not exist "%build_path%" mkdir "%build_path%"
cd "%build_path%"

:: Cau hinh CMake cho chuong trinh tu cac file CMakeLists.txt trong folder de tao ra Makefiles phuc vu cho build
cmake "%cmake_path%" -G "MinGW Makefiles" ^
  -DCMAKE_C_COMPILER=%CC% ^
  -DCMAKE_CXX_COMPILER=%CXX% 
 
if errorlevel 1 (
  echo [ERROR] Cau hinh CMake voi ucrt64 that bai !
  exit /b %errorlevel%
) else (
  echo [SUCCESS] Cau hinh CMake voi ucrt64 thanh cong !
)

endlocal