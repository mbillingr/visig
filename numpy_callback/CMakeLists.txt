project(numpy_callback)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package( PythonLibs REQUIRED )
find_package( NumPy REQUIRED )

include_directories (
    ${PYTHON_INCLUDE_DIR}
    ${NUMPY_INCLUDE_DIRS}
)

message (
    ${NUMPY_INCLUDE_DIRS}
)

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries( ${PROJECT_NAME} ${PYTHON_LIBRARIES} )
