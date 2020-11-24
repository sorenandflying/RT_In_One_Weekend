#ifndef __RAY_H__
#define __RAY_H__

#include "vec3.h"

class ray{
public:
// Variables
  vec3 origin;
  vec3 direction;

// Constructors
  ray(){}
  ray(const vec3& o, const vec3& d){
    origin = o;
    direction = d;
  }

// Getter Functions
  vec3 o() const { return origin; }
  vec3 d() const { return direction; }

// Functions
  vec3 point (float t) const {
    return origin + t * direction;
  }
};

#endif