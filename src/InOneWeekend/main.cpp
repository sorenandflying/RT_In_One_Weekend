#include <iostream>
#include "ray.h"

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