project(main)
include_directories(include)
file(GLOB SOURCES "*.cpp")
add_executable(main ${SOURCES})