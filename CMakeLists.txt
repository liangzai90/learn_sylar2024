cmake_minimum_required(VERSION 3.0)
project(sylar2023)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")


set(LIB_SRC
    sylar2023/log.cpp
    sylar2023/util.cpp
    sylar2023/config.cpp
    )
    
add_library(sylar2023 SHARED ${LIB_SRC})

add_executable(test tests/test.cpp)
add_dependencies(test sylar2023)
target_link_libraries(test sylar2023)

add_executable(test_config tests/test_config.cpp)
add_dependencies(test_config sylar2023)
target_link_libraries(test_config sylar2023)



SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

