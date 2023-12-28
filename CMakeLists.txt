cmake_minimum_required(VERSION 3.0)
project(sylar2023)

include (cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")


include_directories(.)
#添加(yaml)头文件目录
include_directories(/usr/local/include)
#添加(yaml)链接库目录
link_directories(/usr/local/lib64)

find_library(YAMLCPP yaml-cpp)
message("***", ${YAMLCPP})

set(LIB_SRC
    sylar2023/log.cpp
    sylar2023/util.cpp
    sylar2023/config.cpp
    sylar2023/thread.cpp
    )
    
add_library(sylar2023 SHARED ${LIB_SRC})

set(LIB_LIB
    sylar2023
    pthread
    ${YAMLCPP}
    )

#重定义宏
force_redefine_file_macro_for_sources(sylar2023)   # __FILE__
add_executable(test tests/test.cpp)
add_dependencies(test sylar2023)
force_redefine_file_macro_for_sources(test)   # __FILE__
# test工程依赖于sylar2023库 ，sylar2023库需要链接yaml-cpp库
target_link_libraries(test ${LIB_LIB})

add_executable(test_config tests/test_config.cpp)
add_dependencies(test_config  sylar2023)
force_redefine_file_macro_for_sources(test_config)   # __FILE__
#链接yaml-cpp库(yaml)
target_link_libraries(test_config  ${LIB_LIB})

add_executable(test_thread tests/test_thread.cpp)
add_dependencies(test_thread  sylar2023)
force_redefine_file_macro_for_sources(test_thread)
target_link_libraries(test_thread  ${LIB_LIB})



SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

