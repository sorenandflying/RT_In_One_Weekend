#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "include.h"

struct hit_record;

class material {
public:
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
public:
// Variables
  vec3 albedo;

// Constructors
  lambertian(const vec3& a) : albedo(a) {}

// Functions
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override {
    vec3 scatter_dir = rec.normal + random_in_unit_shpere();
    scattered = ray(rec.p, scatter_dir);
    attenuation = albedo;
    return true;
  }
};

class metal : public material {
public:
// Variables
  vec3 albedo;

// Constructors
  metal(const vec3& a) : albedo(a) {}

// Functions
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
    vec3 reflected = reflect(r_in.d().norm(), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.d(), rec.normal) > 0);
  }
};

#endif
