include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE SRCS *.cc)
add_library(cpp-socket-lib ${SRCS})