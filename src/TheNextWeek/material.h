#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "include.h"

struct hit_record;

float schlick(float cosine, float ref_idx){
  float r0 = (1.0-ref_idx) / (1.0+ref_idx);
  r0 = r0*r0;
  return r0 + (1-r0) * pow((1.0-cosine),5.0);
}

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
    vec3 scatter_dir = rec.normal + random_in_unit_sphere();
    scattered = ray(rec.p, scatter_dir);
    attenuation = albedo;
    return true;
  }
};

class metal : public material {
public:
// Variables
  vec3 albedo;
  float fuzz;

// Constructors
  metal(const vec3& a, float f = 0) : albedo(a) { if (f <= 1 && f >= -1) fuzz = f; else fuzz = 0;}

// Functions
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
    vec3 reflected = reflect(r_in.d().norm(), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;
    return (dot(scattered.d(), rec.normal) > 0);
  }
};

class dielectric : public material {
public: 
// Variables
  float ref_idx;

// Constructors
  dielectric(float ri) : ref_idx(ri){}

// Functions
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.d(), rec.normal);
    float ni_over_nt;
    attenuation = vec3(1.0,1.0,1.0);
    vec3 refracted;
    float reflect_prob;
    float cosine;

    if(dot(r_in.d(), rec.normal) > 0){
      outward_normal = -rec.normal;
      ni_over_nt = ref_idx;
      cosine = ref_idx * dot(r_in.d(), rec.normal) / r_in.d().length();
    }
    else {
      outward_normal = rec.normal;
      ni_over_nt = 1.0 / ref_idx;
      cosine = -dot(r_in.d(), rec.normal) / r_in.d().length();
    }
    if (refract(r_in.d(), outward_normal, ni_over_nt, refracted)){
      // scattered = ray(rec.p, refracted);
      reflect_prob = schlick(cosine, ref_idx);
    }
    else {
      scattered = ray(rec.p, reflected);
      reflect_prob = 1.0;
    }
    if(drand48() < reflect_prob) {
      scattered = ray(rec.p, reflected);
    }
    else {
      scattered = ray(rec.p, refracted);
    }
    return true;
  }
};

#endif
