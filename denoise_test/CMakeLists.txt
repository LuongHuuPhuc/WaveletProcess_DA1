# Tao executable tu file main
add_executable(denoise_test "${CMAKE_CURRENT_SOURCE_DIR}/denoise_test.c")

# Include tat ca cac thu muc co header 
target_include_directories(denoise_test PRIVATE ${WAVELIB_INCLUDE_DIRS})

# Link thu vien wavelib va thu vien toan hoc chuan 
target_link_libraries(denoise_test PRIVATE ${WAVELIB_LIB} m)
