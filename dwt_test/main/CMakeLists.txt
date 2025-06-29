# Tao executable tu file main
add_executable(dwt_test "dwt_test.c")

# Include tat ca cac thu muc co header 
target_include_directories(dwt_test PRIVATE 
  ${WAVELIB_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/../Signal_Erreck)

# Chi dinh thu muc chua file.a
# link_directories(${WAVELIB_LIB_DIR})

# Link thu vien wavelib va thu vien toan hoc chuan 
target_link_libraries(dwt_test PRIVATE 
  "${WAVELIB_LIB_DIR}/libwauxlib.a"
  "${WAVELIB_LIB_DIR}/libwavelib.a"
  Signal_Erreck
  m
)
