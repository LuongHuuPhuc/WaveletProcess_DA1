project(WaveletMain)

# Tao executable tu file main
add_executable(wavelet_main "${CMAKE_CURRENT_SOURCE_DIR}/MainProcess.c")

# Duong dan toi thu vien wavelib va header 
set(WAVELIB_ROOT "${CMAKE_SOURCE_DIR}/../wavelib")
set(WAVELIB_INCLUDE_DIRS PRIVATE
    "${WAVELIB_ROOT}/header"
    "${WAVELIB_ROOT}/src"
    "${WAVELIB_ROOT}/auxiliary"
)

set(WAVELIB_LIB "${WAVELIB_ROOT}/test/libwavelib.a")

message(STATUS "WAVELIB_LIB = ${WAVELIB_LIB}")

# Include tat ca cac thu muc co header 
target_include_directories(wavelet_main PRIVATE ${WAVELIB_INCLUDE_DIRS})

# Link thu vien wavelib va thu vien toan hoc chuan 
target_link_libraries(wavelet_main PRIVATE ${WAVELIB_LIB} m)
