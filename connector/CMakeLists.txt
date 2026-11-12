cmake_minimum_required(VERSION 3.20)

project(Color_Picker CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT MSVC)
    message(FATAL_ERROR "MSVC only.")
endif()

find_package(wxWidgets CONFIG REQUIRED)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_subdirectory(${ROOT_DIR}/include/aviutl2-wx-utils ${CMAKE_BINARY_DIR}/aviutl2-wx-utils)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    src/ui/mainframe.cpp
    src/ipc/host_client.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".aux2")

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${ROOT_DIR}/common
)

target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE _UNICODE $<$<CONFIG:Debug>:_DEBUG>)
target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)

# 静的ランタイム (Conan プロファイルの compiler.runtime=static と合わせる)
set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_link_libraries(${PROJECT_NAME} PRIVATE aviutl2_wx_utils::aviutl2_wx_utils wxWidgets::wxWidgets comctl32 ws2_32)
