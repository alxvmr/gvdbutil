cmake_minimum_required(VERSION 3.5.0)
project(gvdbutil VERSION 0.1.0 LANGUAGES C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED "glib-2.0")
pkg_check_modules(GVDB REQUIRED "gvdb")

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${GLIB_INCLUDE_DIRS} ${GVDB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLIB_LIBRARIES} ${GVDB_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${GLIB_CFLAGS} ${GVDB_CFLAGS})
