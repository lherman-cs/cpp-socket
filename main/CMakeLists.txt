include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(cpp-socket main.cc)
target_link_libraries(cpp-socket cpp-socket-lib)