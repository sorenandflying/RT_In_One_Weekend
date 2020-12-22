#include <iostream>
// #include "ray.h"
#include "include.h"

#include "sphere.h"
#include "hittable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"

/*
vec3 color(const ray& r, hittable *world){
  hit_record rec;
  if (world->hit(r, 0.0, MAXFLOAT, rec)) {
    return 0.5*vec3(rec.normal.x() + 1.0, rec.normal.y() + 1.0, rec.normal.z() + 1.0);
  }
  else {
    vec3 unit_direction = (r.d()).norm();
    float t = 0.5 * (unit_direction.y() + 1.0);
    return lerp(vec3(1.0,1.0,1.0), vec3(0.5, 0.7, 1.0), t);
    // return lerp(vec3(0.5, 0.7, 1.0), vec3(1.0,1.0,1.0), t);
    // return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
  }
}
*/

/*
vec3 color(const ray& r, hittable *world) {
  hit_record rec;
  if (world->hit(r, 0.001, MAXFLOAT, rec)) {
    vec3 target = rec.p + rec.normal + random_in_unit_shpere();
    return 0.5 * color(ray(rec.p, target-rec.p), world);
  }
  else {
    vec3 unit_direction = r.d().norm();
    float t = 0.5*(unit_direction.y() + 1.0);
    return lerp(vec3(1.0,1.0,1.0), vec3(0.5, 0.7, 1.0), t);
  }
}
*/

vec3 color(const ray& r, hittable * world, int depth) {
  hit_record rec;
  if (world->hit(r, 0.001, MAXFLOAT, rec)) {
    ray scattered;
    vec3 attenuation;
    if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
      return attenuation*color(scattered, world, depth + 1);
    }
    else{
      return vec3(0,0,0);
    }
  }
  else {
    vec3 unit_direction = r.d().norm();
    float t = 0.5*(unit_direction.y() + 1.0);
    return lerp(vec3(1.0,1.0,1.0), vec3(0.5, 0.7, 1.0), t);
  }
}

int main() {
  int nx = 400;
  int ny = 200;
  int ns = 50;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  // hittable *list[2];
  // list[0] = new sphere(vec3(0,0,-1), 0.5);
  // list[1] = new sphere(vec3(0,-100.5,-1), 100);
  // hittable *world = new hittable_list(list, 2);

  hittable* list[2];

  vec3 a0 = vec3(.9,.9,.9);
  shared_ptr<material> m0 = make_shared<lambertian>(a0);

  list[0] = new sphere(vec3(0,0,-1), 0.5, m0);

  hittable *world = new hittable_list(list, 1);

  camera cam;

  for(int j = ny-1; j >= 0; j--){
    for(int i  = nx-1; i >= 0; i--){
      vec3 col(0,0,0);
      for(int s = ns - 1; s >= 0; s--){
        float u = float(i + drand48()) / float(nx);
        float v = float(j + drand48()) / float(ny);
        ray r = cam.get_ray(u,v);
        vec3 p = r.point(2.0);
        col += color(r,world,0);
      }

      col /= float(ns);
      // col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
      int ir = int(255.99 * col[0]);
      int ig = int(255.99 * col[1]);
      int ib = int(255.99 * col[2]);

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}