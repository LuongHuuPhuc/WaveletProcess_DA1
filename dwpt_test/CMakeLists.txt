# Tao executable tu file main
add_executable(dwpt_test "dwpt_test.c")

# Include tat ca cac thu muc co header 
target_include_directories(dwpt_test PRIVATE ${WAVELIB_INCLUDE_DIRS})

# Chi dinh thu muc chua file.a
# link_directories(${WAVELIB_LIB_DIR})

# Link thu vien wavelib va thu vien toan hoc chuan 
target_link_libraries(dwpt_test PRIVATE 
  "${WAVELIB_LIB_DIR}/libwauxlib.a"
  "${WAVELIB_LIB_DIR}/libwavelib.a"
  m
)
