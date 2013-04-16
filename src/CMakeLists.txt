cmake_minimum_required(VERSION 2.6)
project(rbu C)

################################################################################
# Setup compiler
################################################################################
if(NOT CMAKE_COMPILER_IS_GNUCC)
  message(FATAL_ERROR "Unsupported compiler")
endif(NOT CMAKE_COMPILER_IS_GNUCC)

set(CMAKE_DEBUG_POSTFIX "-dbg")

set(CMAKE_C_FLAGS "-pedantic -std=c99 -Wall -Wextra -Wcast-align -Wmissing-declarations -Wmissing-prototypes -fvisibility=hidden -fstrict-aliasing -Wl,-z,defs -Wconversion")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

################################################################################
# Check dependencies
################################################################################
macro(check_dependency lib header)
  find_path(${lib}_INCLUDE_DIR ${header})
  find_library(${lib}_LIBRARY ${lib})

  if(NOT ${lib}_INCLUDE_DIR OR NOT ${lib}_LIBRARY)
    message(FATAL_ERROR "Can't find ${lib} header/library")
  else()
    message(STATUS "${lib} found: ${${lib}_LIBRARY}")
  endif()

  include_directories(${${lib}_INCLUDE_DIR})
endmacro()

check_dependency(snlsys snlsys/snlsys.h)
check_dependency(rbi rb/rbi.h)

################################################################################
# Target
################################################################################
add_library(rbu SHARED rbu_geometry.c rbu.h)
target_link_libraries(rbu ${snlsys_LIBRARY} ${rbi_LIBRARY} m)
set_target_properties(rbu PROPERTIES DEFINE_SYMBOL RBU_SHARED_BUILD)

################################################################################
# Outputs
################################################################################
install(TARGETS rbu LIBRARY DESTINATION lib)
install(FILES rbu.h DESTINATION include/rb)

