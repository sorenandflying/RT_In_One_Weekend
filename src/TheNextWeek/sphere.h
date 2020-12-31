#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "include.h"
#include "hittable.h"

class sphere: public hittable {
public:
// Variables
  vec3 center;
  float radius;
  shared_ptr<material> mat_ptr;

// Constructors
  sphere() {}
  sphere(vec3 c, float r) : center(c), radius(r) {};
  sphere(vec3 c, float r, shared_ptr<material> m) : center(c), radius(r), mat_ptr(m) {};

// Functions
  virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;
  virtual bool bounding_box(float t0, float t1, aabb& box) const override;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  vec3 oc = r.o() - center;
  // float a = dot(r.d(), r.d());
  float a = r.d().squared_length();
  float b = dot(oc, r.d());
  float half_b = dot(oc, r.d());
  float c = dot(oc, oc) - radius*radius;

  float discriminant = half_b*half_b - a*c;

  if (discriminant > 0) {
    float root = sqrt(discriminant);
    float temp = (-half_b - root) / a;

    if (temp < t_max && temp > t_min){
      rec.t = temp;
      rec.p = r.point(rec.t);
      rec.normal = (rec.p - center) / radius;
      rec.mat_ptr = mat_ptr;
      return true;
    }

    temp = (-b + sqrt(discriminant))/a;
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = r.point(rec.t);
      rec.normal = (rec.p  - center) / radius;
      rec.mat_ptr = mat_ptr;
      return true;
    }
  }
  return false;
}

bool sphere::bounding_box(float t0, float t1, aabb& box) const
{
  box = aabb(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
  return true;
}

#endif