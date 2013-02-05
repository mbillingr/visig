project(visig)
cmake_minimum_required(VERSION 2.8)

#aux_source_directory(src SRC_LIST)
#add_executable(${PROJECT_NAME} ${SRC_LIST} )

find_package( Boost REQUIRED )

include_directories(
  ${Boost_INCLUDE_DIR}
)

file (GLOB HDR_LIST "src/*.h")
file (GLOB SRC_LIST "src/*.cpp")
add_executable(${PROJECT_NAME} ${SRC_LIST} ${HDR_LIST})
