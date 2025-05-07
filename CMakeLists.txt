cmake_minimum_required(VERSION 3.25)
project(file_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE H_FILES    ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SRC_FILES  ${PROJECT_SOURCE_DIR}/source/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
    ${H_FILES}
    ${SRC_FILES})