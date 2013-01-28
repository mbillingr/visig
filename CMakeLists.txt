project(visig)
cmake_minimum_required(VERSION 2.8)

#aux_source_directory(src SRC_LIST)
#add_executable(${PROJECT_NAME} ${SRC_LIST} )

file (GLOB HDR_LIST "src/*.h")
file (GLOB SRC_LIST "src/*.cpp")
add_executable(${PROJECT_NAME} ${SRC_LIST} ${HDR_LIST})
