#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "ray.h"

class camera {
public:
// Variables
  vec3 origin;
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;

// Constructors
  camera(){
    lower_left_corner = vec3(-2.0, -1.0, -1.0);
    horizontal = vec3(4.0,0.0,0.0);
    vertical = vec3(0.0,2.0,0.0);
    origin = vec3(0.0,0.0,0.0);
  }

  camera (vec3 llc, vec3 o, vec3 h, vec3 v){
    lower_left_corner = llc;
    horizontal = h;
    vertical = v;
    origin = o;
  }

// Functions
  ray get_ray(float u, float v){
    return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
  }
};

#endif