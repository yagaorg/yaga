cmake_minimum_required(VERSION 3.5)
project(yaga LANGUAGES C CXX)

include(cmake/add-files.cmake)
include(cmake/compiler-options.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/src/ui CACHE STRING "QML Import path")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/sanitizers-cmake/cmake" ${CMAKE_MODULE_PATH})

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Sanitizers)

add_subdirectory(lib)
add_subdirectory(src)

add_executable(${PROJECT_NAME} "")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
target_sources(${PROJECT_NAME} PUBLIC ${SRCS})

set_common_compiler_options(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}
  PRIVATE
    src
    lib/libgit2/include
    lib/GSL/include
)
target_link_libraries(${PROJECT_NAME} git2 Qt5::Core Qt5::Quick)
add_sanitizers(${PROJECT_NAME})
