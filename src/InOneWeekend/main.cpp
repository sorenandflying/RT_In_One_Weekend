#include <iostream>
// #include "ray.h"
#include "sphere.h"
#include "hittable_list.h"
#include "float.h"
#include "camera.h"

/*
float hit_sphere(const vec3& center, float radius, const ray& r){
  vec3 oc = r.o() - center;
  float a = dot(r.d(), r.d());
  float b = 2.0 * dot(oc, r.d());
  float c = dot(oc,oc) - radius * radius;
  float discriminant = b*b - 4*a*c;
  if (discriminant < 0) {
    return -1.0;
  }
  else {
    return (-b - sqrt(discriminant)) / (2.0 * a);
  }
}
*/

/*
vec3 color(const ray& r) {
  float t = hit_sphere(vec3(0,0,-1), 0.5, r);
  if (t > 0.0){
    vec3 p = r.point(t);
    vec3 n = (p - vec3(0,0,-1)).norm();
    return 0.5 * vec3(n.x() + 1, n.y() + 1, n.z() + 1);
  }
  vec3 unit_dir = r.d().norm();
  t = 0.5*(unit_dir.y() + 1.0);
  return (1.0 - t) * vec3(1.0,1.0,1.0) + t*vec3(0.5, 0.7, 1.0);
}
*/

/*
int main(){
  int nx = 200;
  int ny = 100;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);
  for(int j = ny-1; j >= 0; j--){
    for(int i  = nx-1; i >= 0; i--){
      float u = float(i) / float(nx);
      float v = float(j) / float(ny);

      ray r(origin, lower_left_corner + u*horizontal + v*vertical);
      vec3 col = color(r);

      int ir = int(255.99*col[0]);
      int ig = int(255.99*col[1]);
      int ib = int(255.99*col[2]);
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
*/

vec3 color(const ray& r, hittable *world){
  hit_record rec;
  if (world->hit(r, 0.0, MAXFLOAT, rec)) {
    return 0.5*vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z()+1);
  }
  else {
    vec3 unit_direction = (r.d()).norm();
    float t = 0.5 * (unit_direction.y() + 1.0);
    return lerp(vec3(1.0,1.0,1.0), vec3(0.5, 0.7, 1.0), t);
    // return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
  }
}

int main() {
  int nx = 400;
  int ny = 200;
  int ns = 50;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  hittable *list[2];
  list[0] = new sphere(vec3(0,0,-1), 0.5);
  list[1] = new sphere(vec3(0,-100.5,-1), 100);
  hittable *world = new hittable_list(list, 2);
  camera cam;

  for(int j = ny-1; j >= 0; j--){
    for(int i  = nx-1; i >= 0; i--){
      vec3 col(0,0,0);
      for(int s = ns - 1; s >= 0; s--){
        float u = float(i + drand48()) / float(nx);
        float v = float(j + drand48()) / float(ny);
        ray r = cam.get_ray(u,v);
        vec3 p = r.point(2.0);
        col += color(r,world);
      }

      col /= float(ns);
      int ir = int(255.99 * col[0]);
      int ig = int(255.99 * col[1]);
      int ib = int(255.99 * col[2]);

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}