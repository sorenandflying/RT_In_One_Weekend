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

  auto ground_material = make_shared<lambertian>(color(0.8,0.8,0));
  world.add(make_shared<sphere>(point3(0,-100.5,-1), 100, ground_material));

  auto sphere_material = make_shared<lambertian>(color(0.8,0.3,0.3));
  world.add(make_shared<sphere>(point3(0,0,-1), 0.5, sphere_material));

  auto metal_material_1 = make_shared<metal>(color(0.8,0.6,0.2), 0.3);
  world.add(make_shared<sphere>(point3(1,0,-1), 0.5, metal_material_1));

  auto dielectric_material = make_shared<dielectric>(1.5);
  world.add(make_shared<sphere>(point3(-1,0,-1), 0.5, dielectric_material));
  world.add(make_shared<sphere>(point3(-1,0,-1), -0.45, dielectric_material));

  return world;
}

hittable_list get_scene2() {
  hittable_list world;

  float radius = cos(pi/4);

  auto sphere_material_1 = make_shared<lambertian>(color(0,0,1));
  auto sphere_material_2 = make_shared<lambertian>(color(1,0,0));

  world.add(make_shared<sphere>(point3(-radius, 0, -1), radius, sphere_material_1));
  world.add(make_shared<sphere>(point3(radius, 0, -1), radius, sphere_material_2));

  return world;
}

int main() {
  int nx = 800;
  int ny = 400;
  int ns = 100;
  int max_depth = 50;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  // camera cam();
  camera cam(vec3(-2,2,1), vec3(0,0,-1), vec3(0,1,0), 90, float(nx)/float(ny));

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
