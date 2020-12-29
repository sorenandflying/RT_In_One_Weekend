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
  vec3 u,v,w;
  float lens_radius;

// Constructors
  camera(){
    lower_left_corner = vec3(-2.0, -1.0, -1.0);
    horizontal = vec3(4.0,0.0,0.0);
    vertical = vec3(0.0,2.0,0.0);
    origin = vec3(0.0,0.0,0.0);
  }

  camera(vec3 llc, vec3 o, vec3 h, vec3 v){
    lens_radius = 0;
    lower_left_corner = llc;
    horizontal = h;
    vertical = v;
    origin = o;
  }

  camera(float vfov, float aspect){
    lens_radius = 0;
    float theta = vfov * pi / 180;
    float half_height = tan(theta/2);
    float half_width = aspect * half_height;
    lower_left_corner = vec3(-half_width, -half_height, -1.0);
    horizontal = vec3(2*half_width, 0.0, 0.0);
    vertical = vec3(0.0, 2*half_height, 0.0);
    origin = vec3(0,0,0);
  }

  camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect) {
    lens_radius = 0;
    float theta = vfov * pi / 180.0;
    float half_height = tan(theta/2.0);
    float half_width = aspect * half_height;
    origin = lookfrom;
    w = (lookfrom - lookat).norm();
    u = (cross(vup, w)).norm();
    v = (cross(w,u)).norm();
    lower_left_corner = origin - half_width * u - half_height * v - w;
    horizontal = 2.0*half_width*u;
    vertical = 2.0*half_height*v;
  }

  camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist) {
    lens_radius = aperture / 2.0;
    float theta = vfov * pi / 180.0;
    float half_height = tan(theta/2.0);
    float half_width = aspect * half_height;
    origin = lookfrom;
    w = (lookfrom - lookat).norm();
    u = (cross(vup, w)).norm();
    v = (cross(w,u)).norm();
    lower_left_corner = origin - focus_dist * (half_width * u - half_height * v - w);
    horizontal = 2.0*half_width*focus_dist*u;
    vertical = 2.0*half_height*focus_dist*v;
  }

// Functions
  // ray get_ray(float s, float t){
  //   return ray(origin, lower_left_corner + s*horizontal + t*vertical - origin);
  // }

  ray get_ray(float s, float t){
    vec3 rd = lens_radius * random_in_unit_disc();
    vec3 offset = u * rd.x() + v * rd.y();
    return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
  }
};

#endif
