macro (set_common_compiler_options TGT)
  if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(${TGT} PRIVATE
      -fdiagnostics-color=always
      -Wall
      -Wcast-align
      -Wcast-qual
      -Wconversion
      -Wctor-dtor-privacy
      -Wdisabled-optimization
      -Wdouble-promotion
      -Wduplicated-branches
      -Wduplicated-cond
      -Wextra
      -Wformat=2
      -Winit-self
      -Wlogical-op
      -Wmissing-declarations
      -Wmissing-include-dirs
      -Wno-sign-conversion
      -Wnoexcept
      -Wnull-dereference
      -Wold-style-cast
      -Woverloaded-virtual
      -Wpedantic
      -Wredundant-decls
      -Wrestrict
      -Wshadow
      -Wstrict-aliasing=1
      -Wstrict-null-sentinel
      -Wstrict-overflow=5
      -Wswitch-default
      -Wno-unknown-pragmas
      -Wuseless-cast
      -Wno-missing-field-intiializers
    )
  endif()
endmacro()
