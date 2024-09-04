cmake_minimum_required(VERSION 3.5.0)
project(gvdbutil VERSION 0.1.0 LANGUAGES C)

add_library(gvdb SHARED IMPORTED GLOBAL)
set_property(TARGET gvdb PROPERTY
             IMPORTED_LOCATION "/usr/lib64/libgvdb.so")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED IMPORTED_TARGET "gtk+-2.0")

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.c)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "/usr/include/gvdb")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)

target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::GTK)
target_link_libraries(${PROJECT_NAME} PRIVATE gvdb)