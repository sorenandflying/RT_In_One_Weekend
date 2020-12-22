#ifndef __HITTABLE_LIST_H__
#define __HITTABLE_LIST_H__

#include "hittable.h"

#include <memory>
#include <vector>

class hittable_list: public hittable {
public:
// Variables
  hittable **list;
  int list_size;
  std::vector<shared_ptr<hittable>> objects;

// Constructors
  hittable_list() {}
  hittable_list(hittable **l, int n) { list = l; list_size = n; }
  hittable_list(shared_ptr<hittable> object) {objects.push_back(object); }

// Functions
  virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;

  void clear() {objects.clear();}
  void add(shared_ptr<hittable> object) { objects.push_back(object); }
};

bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  hit_record temp_rec;
  bool hit_anything = false;
  double closest_hit = t_max;

  for (const auto& object :objects){
    if(object->hit(r, t_min, closest_hit, temp_rec)){
      hit_anything = true;
      closest_hit = temp_rec.t;
      rec = temp_rec;
    }
  }

  /*
  for (int i = 0; i < list_size; i++){
    if (list[i]->hit(r, t_min, closest_hit, temp_rec)){
      hit_anything = true;
      closest_hit = temp_rec.t;
      rec = temp_rec;
    }
  }
  */

  return hit_anything;
}

#endif
