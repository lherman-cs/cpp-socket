include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(cpp-socket main.cc)
target_link_libraries(cpp-socket cpp-socket-lib)

add_executable(server server.cc)
target_link_libraries(server cpp-socket-lib)

add_executable(client client.cc)
target_link_libraries(client cpp-socket-lib)