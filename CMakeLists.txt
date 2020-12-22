#---------------------------------------------------------------------------------------------------
# CMake Build Configuration for the Ray Tracing Weekend Series
#
# See README.md for guidance.
#---------------------------------------------------------------------------------------------------

cmake_minimum_required ( VERSION 3.1.0 )

project ( RTWeekend
  VERSION 3.0.0
  LANGUAGES CXX
)

# Set to c++11
set ( CMAKE_CXX_STANDARD 11 )

# Source
set ( COMMON_SRC
  src/common/camera.h
  src/common/color.h
  src/common/include.h
  src/common/ray.h
  src/common/vec3.h
)

set ( ONEWEEKEND_SRC
  ${COMMON_SRC}
  src/InOneWeekend/hittable.h
  src/InOneWeekend/hittable_list.h
  src/InOneWeekend/material.h
  src/InOneWeekend/sphere.h

  src/InOneWeekend/main.cpp
  src/InOneWeekend/helloworld.cpp
)

# add_library(common_lib
#   ${COMMON_SRC}
#   ${COMMON_INCLUDE}
# )

# Main Executables
add_executable(inOneWeekend src/InOneWeekend/main.cpp)

# Example Executables
add_executable(helloworld src/InOneWeekend/helloworld.cpp)

# target_link_libraries(inOneWeekend common_lib)
# target_link_libraries(helloworld common_lib)

include_directories(
  src/common
)
