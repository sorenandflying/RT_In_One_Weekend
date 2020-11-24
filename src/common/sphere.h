#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "hittable.h"

class sphere: public hittable {
public:
// Variables
  vec3 center;
  float radius;

// Constructors
  sphere() {}
  sphere(vec3 c, float r) : center(c), radius(r) {};

// Functions
  virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  vec3 oc = r.o() - center;
  float a = dot(r.d(), r.d());
  float b = dot(oc, r.d());
  float c = dot(oc, oc) - radius*radius;
  float discriminant = b*b - a*c;
  if (discriminant > 0) {
    float temp = (-b - discriminant) / a;
    if (temp < t_max && temp > t_min){
      rec.t = temp;
      rec.p = r.point(rec.t);
      rec.normal = (rec.p - center) / radius;
      return true;
    }
    temp = (-b + sqrt(discriminant))/a;
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = r.point(rec.t);
      rec.normal = (rec.p  - center) / radius;
      return true;
    }
  }
  return false;
}

#endif