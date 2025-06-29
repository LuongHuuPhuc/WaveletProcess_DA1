@echo off
setlocal enabledelayedexpansion

:: B1 - Di chuyen vao thu muc build
cd build

:: B2 - Build chuong trinh cmake bang mingw32-make
echo === Building project with mingw32-make ===
mingw32-make 
echo.

:: B3 - Hien thi menu luu chon file.exe de chay 
echo === Chon thu muc de chay file.exe ===
echo 1. dwt_test
echo 2. denoise_test
echo 3. dwpt_test
set /p choice="Nhap lua chon (1/2/3): "

:: B4 - Dan den duong link tuong ung 
set exe_path=""
if "%choice%"=="1" set exe_path=dwt_test/main/dwt_test.exe
if "%choice%"=="2" set exe_path=denoise_test/main/denoise_test.exe
if "%choice%"=="3" set exe_path=dwpt_test/main/dwpt_test.exe

:: B5 - Kiem tra va chay
if exist "!exe_path!" (
  echo. 
  echo == Dang chay !exe_path! ====
  call "!exe_path!"
) else (
  echo.
  echo Loi: Khong tim thay file !exe_path!
)

endlocal
pause