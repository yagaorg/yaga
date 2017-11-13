cmake_minimum_required(VERSION 3.5)
project(yaga LANGUAGES C CXX)

include(cmake/yaga-files.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_subdirectory(lib)
add_subdirectory(ui)
add_subdirectory(src)

add_executable(${PROJECT_NAME} "")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
target_sources(${PROJECT_NAME}
  PUBLIC
    ${UI}
    ${SRCS}
  INTERFACE
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    src
    lib/libgit2/include
    lib/GSL/include
)
target_link_libraries(${PROJECT_NAME} git2 Qt5::Core Qt5::Quick)
