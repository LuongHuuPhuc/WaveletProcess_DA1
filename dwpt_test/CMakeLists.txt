# Tao executable tu file main
add_executable(dwpt_test "${CMAKE_CURRENT_SOURCE_DIR}/dwpt_test.c")

# Include tat ca cac thu muc co header 
target_include_directories(dwpt_test PRIVATE ${WAVELIB_INCLUDE_DIRS})

# Link thu vien wavelib va thu vien toan hoc chuan 
target_link_libraries(dwpt_test PRIVATE ${WAVELIB_LIB} m)
