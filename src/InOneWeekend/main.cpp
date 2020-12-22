#include "include.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include <iostream>

vec3 ray_color(const ray& r, const hittable& world, int depth){
  hit_record rec;

  if(depth <= 0){
    return color(0,0,0);
  }

  if (world.hit(r, 0.001, infinity, rec)) {
    ray scattered;
    color attenuation;
    if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
      return attenuation * ray_color(scattered, world, depth-1);
    }
    return color(0,0,0);
  }

  vec3 unit_direction = r.d().norm();
  auto t = 0.5*(unit_direction.y() + 1.0);
  return (1.0-t)*color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0);
}

hittable_list get_scene() {
  hittable_list world;

  auto ground_material = make_shared<lambertian>(color(0.5,0.5,0.5));
  world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

  return world;
}

int main() {
  int nx = 400;
  int ny = 200;
  int ns = 50;
  int max_depth = 50;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  camera cam;
  auto world = get_scene();

  for(int j = ny-1; j >= 0; j--){
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for(int i  = nx-1; i >= 0; i--){
      vec3 col(0,0,0);
      for(int s = ns - 1; s >= 0; s--){
        float u = float(i + random_double()) / float(nx);
        float v = float(j + random_double()) / float(ny);
        ray r = cam.get_ray(u,v);
        vec3 p = r.point(2.0);
        col += ray_color(r, world, max_depth);
      }
      write_color(std::cout, col, ns);
    }
  }
  std::cerr << "\nDone.\n";
}
