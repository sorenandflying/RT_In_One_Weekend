#include "include.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "bvh.h"
#include "bvh_node.h"

#include <iostream>
#include <chrono>

using namespace std::chrono;

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
  hittable_list world = hittable_list();

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

hittable_list get_random_scene() {
  hittable_list world;
  int nx = 10;
  int ny = 10;

  auto ground_material = make_shared<lambertian>(color(0.5,0.5,0.5));
  world.add(make_shared<sphere>(point3(0,-1000,1), 1000, ground_material));

  auto big_sphere_material = make_shared<metal>(color(0.6,0.6,0.5));
  world.add(make_shared<sphere>(point3(20,4,1), 4, big_sphere_material));

  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      // Get random material
      int material_num = floor(random_double(0,2.5));
      shared_ptr<material> sphere_material; 
      switch(material_num){
        case 0:{
          color c(random_double() * random_double(), random_double()*random_double(), random_double()*random_double());
          sphere_material = make_shared<lambertian>(c);
          break;
        }
        case 1:{
          color c(random_double(), random_double(), random_double());
          sphere_material = make_shared<metal>(c,0.0);
          break;
        }
        case 2:{
          sphere_material = make_shared<dielectric>(1.5);
          break;
        }
      }

      // Get position

      float radius = 0.5 + random_double(-.1,.4);

      float pos_x = (i*2 - nx) * 1.1 + random_double(-0.4,0.4);
      float pos_y = radius + random_double(0,0.5) * random_double(0,1.0);
      float pos_z = j*2 - ny+random_double(-.5,.5);

      point3 position(pos_x, pos_y, pos_z);

      world.add(make_shared<sphere>(position, radius, sphere_material));
      // world.add(make_shared<sphere>(point3(-n+2*i,0,0), 1.0, sphere_material));

    }
  }

  // auto world_ptr = make_shared<bvh_node>(world, 0.0, 1.0);
  // hittable_list world_bvh(world_ptr);
  // return world_bvh;
  return world;
}

int main_basic() {
  int nx = 800;
  int ny = 600;
  int ns = 25;
  int max_depth = 50;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  // camera cam();
  camera cam(vec3(-15,4,-3), vec3(0,0,0), vec3(0,1,0), 45, float(nx)/float(ny));

  // auto world = get_scene();
  auto world = get_random_scene();

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
  return 0;
}

void pixel_color(hittable_list world, camera cam, int nx, int ny, int ns, int s, int max_depth, std::vector<color> const & color_ref)
{
  std::vector<color> & local_colors = const_cast<std::vector<color> &>(color_ref);
  for (int j = ny-1; j >= 0; j--){
    if (s==0) std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for(int i = nx-1; i >= 0; i--){
      vec3 col(0,0,0);
      float u = float(i + random_double()) / float(nx);
      float v = float(j + random_double()) / float(ny);
      ray r = cam.get_ray(u,v);
      vec3 p = r.point(2.0);
      col += ray_color(r, world, max_depth);
      local_colors[i + j * nx] += col;
    }
  }
}

int main_threaded() {

  std::cerr << "\nStarting main";
  int nx = 800;
  int ny = 600;
  int ns = 100;
  int max_depth = 50;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  // camera cam();
  camera cam(vec3(-15,4,-3), vec3(0,0,0), vec3(0,1,0), 45, float(nx)/float(ny));

  // auto world = get_scene();
  auto world = get_random_scene();

  std::vector<std::thread> threads;
  std::vector<color> colors;
  colors.resize(nx*ny);

  std::cerr << "\nStarting Render Loop\n";

  for(int s = ns-1; s >= 0; s--){
    threads.push_back(std::thread(pixel_color, world, cam, nx, ny, ns, s, max_depth, std::ref(colors)));
  }
  for (auto&th : threads) {
    th.join();
  }
  std::cerr << "\nWriting image\n";
  for(int i = nx*ny-1; i >= 0; i--){
    write_color(std::cout, colors[i], ns);
  }
  std::cerr << "\nDone.\n";
  return 0;
}

int main()
{
  auto start = high_resolution_clock::now();

  bool use_threads = true;

  if(use_threads) main_threaded();
  else main_basic();

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<seconds>(stop-start);
  std::cerr << "Duration: " << duration.count() << " seconds\n";
  return 0;
}
