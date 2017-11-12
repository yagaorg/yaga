cmake_minimum_required(VERSION 3.5)
project(yaga LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

macro (yaga_sources)
    foreach(_file ${ARGN})
      list(APPEND SRCS "${CMAKE_CURRENT_LIST_DIR}/${_file}")
    endforeach()
    set(SRCS ${SRCS} PARENT_SCOPE)
endmacro()

macro (yaga_headers)
    foreach(_file ${ARGN})
      list(APPEND HEADERS "${CMAKE_CURRENT_LIST_DIR}/${_file}")
    endforeach()
    set(HEADERS ${HEADERS} PARENT_SCOPE)
endmacro()

macro (yaga_ui)
    foreach(_file ${ARGN})
      list(APPEND UI "${CMAKE_CURRENT_LIST_DIR}/${_file}")
    endforeach()
    set(UI ${UI} PARENT_SCOPE)
endmacro()

add_subdirectory(lib)
add_subdirectory(ui)
add_subdirectory(src)

add_executable(${PROJECT_NAME} "")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

message("${SRCS}")

target_sources(${PROJECT_NAME}
  PUBLIC
    ${UI}
    ${SRCS}
  INTERFACE
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick)
