cmake_minimum_required(VERSION 3.30)

project(WaveletProcess C CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

# Duong dan toi thu vien wavelib va header de dung cho cac folder con
set(WAVELIB_ROOT "${CMAKE_SOURCE_DIR}/../wavelib")
set(WAVELIB_INCLUDE_DIRS PRIVATE
    "${WAVELIB_ROOT}/header"
    "${WAVELIB_ROOT}/src"
    "${WAVELIB_ROOT}/auxiliary"
    CACHE INTERNAL "Include paths for wavelib"
)
set(WAVELIB_LIB_DIR "${WAVELIB_ROOT}/build/Bin" CACHE INTERNAL "")

# Cho phep cac thu muc con dung cac bien tren 
# set(WAVELIB_INCLUDE_DIRS ${WAVELIB_INCLUDE_DIRS} PARENT_DIRECTORY)
# set(WAVELIB_LIB_DIR ${WAVELIB_LIB_DIR} PARENT_DIRECTORY)
# set(WAVELIB_LIB_NAME ${WAVELIB_LIB_NAME} PARENT_DIRECTORY)

# Them subdirectory chua chuong trinh chinh
# Tach rieng logic build cac chuong trinh thuc thi qua add_subdirectory()
# Trong cac folder nay phai chua cac file CMakeLists.txt
add_subdirectory("denoise_test/main") 
add_subdirectory("dwpt_test/main")
add_subdirectory("dwt_test/main")
add_subdirectory(Signal_Erreck)
