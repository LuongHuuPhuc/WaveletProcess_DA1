cmake_minimum_required(VERSION 3.30)

project(WaveletProcess C CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

# Them subdirectory chua chuong trinh chinh
add_subdirectory(main) # Tach rieng logic build chinh (main) qua add_subdirectory()
