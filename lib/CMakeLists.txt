option(BUILD_SHARED_LIBS "" OFF)
option(BUILD_CLAR "" OFF)
option(THREADSAFE "" ON)
add_subdirectory(libgit2)

add_subdirectory(GSL)
