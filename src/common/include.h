#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <thread>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.141592653589;

// Utilities

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double clamp(double x, double min, double max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

inline double random_double() {
  return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max){
  return min + (max-min)*random_double();
}

inline int random_int(int min, int max){
  return static_cast<int>(random_double(min,max+1));
}

#include "ray.h"
#include "vec3.h"

vec3 random_in_unit_sphere() {
  vec3 p;
  do {
    p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
  } while (p.squared_length() >= 1.0);
  return p;
}

vec3 random_in_unit_disc(){
  vec3 p;
  do{
    p = vec3(random_double(-1,1), random_double(-1,1), 0);
  } while (p.length() > 1.0);
  return p;
}

#endif