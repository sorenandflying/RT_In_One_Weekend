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
  # src/common/camera.cpp
  # src/common/scene.cpp
  # src/common/sphere.cpp
  src/common/vec3.h
  src/common/ray.h
)

# set ( COMMON_INCLUDE
#   include/common/camera.h
#   include/common/common.h
#   include/common/ray.h
#   include/common/geometry.h
#   include/common/material.h
#   include/common/sphere.h
#   include/common/scene.h
#   include/common/vec3.h
# )

# add_library(common_lib
#   ${COMMON_SRC}
#   ${COMMON_INCLUDE}
# )


set ( SOURCE_ONE_WEEKEND
  # ${COMMON_ALL}
  ${COMMON_SRC}
  # ${INCLUDE_ALL}
  # src/InOneWeekend/hittable.h
  src/InOneWeekend/main.cpp
  src/InOneWeekend/helloworld.cpp
)

# Main Executables
add_executable(inOneWeekend src/InOneWeekend/main.cpp)

# Example Executables
add_executable(helloworld src/InOneWeekend/helloworld.cpp)

# target_link_libraries(inOneWeekend common_lib)
# target_link_libraries(helloworld common_lib)

include_directories(
  src/common
  # include/common
)