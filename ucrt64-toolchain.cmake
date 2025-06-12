# Toochain file dung cho msys64 ucrt64 GCC 
# Li do: Mac du da set complier gcc cho cmake roi nhung no van cu lay cl.exe lam minh ko the build cmake duoc

# Set the system name to avoid CMake assuming MVSC 
set(CMAKE_SYSTEM_NAME Windows)  

# Chi dinh trinh bien dich ro rang dung ucrt64 
set(CMAKE_C_COMPILER "C:/msys64/ucrt64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")

# Chi duong dan to msys2 tools
set(CMAKE_RC_COMPILER "C:/msys64/ucrt64/bin/windres.exe")

# Khong cho phep tim kiem duong dan he thong chi dinh cho Visual Studio
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NERVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)