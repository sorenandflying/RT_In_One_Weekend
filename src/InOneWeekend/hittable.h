#ifndef __HITTABLE_H__
#define __HITTABLE_H__

#include "include.h"
#include "ray.h"

class material;

struct hit_record {
  float t;
  vec3 p;
  vec3 normal;
  shared_ptr<material> mat_ptr;
};

class hittable {
public:
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif
