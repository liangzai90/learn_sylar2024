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
message("****  ${YAMLCPP}")

set(LIB_SRC
    sylar2023/log.cpp
    sylar2023/fiber.cpp
    sylar2023/fd_manager.cpp
    sylar2023/hook.cpp
    sylar2023/util.cpp
    sylar2023/scheduler.cpp
    sylar2023/iomanager.cpp
    sylar2023/timer.cpp
    sylar2023/config.cpp
    sylar2023/thread.cpp
    sylar2023/address.cpp
    sylar2023/bytearray.cpp
    )
    
add_library(sylar2023 SHARED ${LIB_SRC})

set(LIB_LIB
    dl
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

add_executable(test_util tests/test_util.cpp)
add_dependencies(test_util  sylar2023)
force_redefine_file_macro_for_sources(test_util)
target_link_libraries(test_util  ${LIB_LIB})

add_executable(test_fiber tests/test_fiber.cpp)
add_dependencies(test_fiber  sylar2023)
force_redefine_file_macro_for_sources(test_fiber)
target_link_libraries(test_fiber  ${LIB_LIB})

add_executable(test_scheduler tests/test_scheduler.cpp)
add_dependencies(test_scheduler  sylar2023)
force_redefine_file_macro_for_sources(test_scheduler)
target_link_libraries(test_scheduler  ${LIB_LIB})

add_executable(test_iomanager tests/test_iomanager.cpp)
add_dependencies(test_iomanager  sylar2023)
force_redefine_file_macro_for_sources(test_iomanager)
target_link_libraries(test_iomanager  ${LIB_LIB})

add_executable(test_hook tests/test_hook.cpp)
add_dependencies(test_hook  sylar2023)
force_redefine_file_macro_for_sources(test_hook)
target_link_libraries(test_hook  ${LIB_LIB})

add_executable(test_address tests/test_address.cpp)
add_dependencies(test_address  sylar2023)
force_redefine_file_macro_for_sources(test_address)
target_link_libraries(test_address  ${LIB_LIB})

add_executable(test_bytearray tests/test_bytearray.cpp)
add_dependencies(test_bytearray  sylar2023)
force_redefine_file_macro_for_sources(test_bytearray)
target_link_libraries(test_bytearray  ${LIB_LIB})



SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
