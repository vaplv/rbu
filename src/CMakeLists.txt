# Copyright (c) 2013 Vincent Forest
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
# EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
cmake_minimum_required(VERSION 2.6)
project(rbu C)

################################################################################
# Setup compiler
################################################################################
if(NOT CMAKE_COMPILER_IS_GNUCC)
  message(FATAL_ERROR "Unsupported compiler")
endif(NOT CMAKE_COMPILER_IS_GNUCC)

set(CMAKE_C_FLAGS "-pedantic -std=c99 -Wall -Wextra -Wcast-align -Wmissing-declarations -Wmissing-prototypes -fvisibility=hidden -fstrict-aliasing -Wl,-z,defs")
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

check_dependency(sys sys/sys.h)
check_dependency(rbi rb/rbi.h)

################################################################################
# Target
################################################################################
add_library(rbu SHARED rbu_geometry.c rbu.h)
target_link_libraries(rbu ${sys_LIBRARY} ${rbi_LIBRARY} m)
set_target_properties(rbu PROPERTIES DEFINE_SYMBOL RBU_SHARED_BUILD)

################################################################################
# Outputs
################################################################################
install(TARGETS rbu LIBRARY DESTINATION lib)
install(FILES rbu.h DESTINATION include/rb)
