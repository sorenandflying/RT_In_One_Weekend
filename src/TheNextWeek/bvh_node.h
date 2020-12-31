#ifndef __BVH_NODE_H__
#define __BVH_NODE_H__

#include "include.h"
#include "bvh.h"
#include "hittable.h"

#include <algorithm>

class bvh_node : public hittable {
public:
// Variables
  hittable * left;
  hittable * right;
  aabb box;

// Constructors
  bvh_node() {}
  bvh_node(hittable **l, int n, float time0, float time1);

// Functions
  virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
  virtual bool bounding_box(float t0, float t1, aabb& box) const;
};

int box_compare(const void * a, const void * b, int axis){
  aabb box_left, box_right;
  hittable *ah = *(hittable**)a;
  hittable *bh = *(hittable**)b;

  if(!ah->bounding_box(0,0, box_left) || !bh->bounding_box(0,0,box_right)){
    std::cerr << "no bounding box in bvh_node constructor\n";
  }
  if(box_left.min()[axis] - box_right.min()[axis] < 0.0 ) return -1;
  else return 1;
}

int box_x_compare(const void * a, const void * b){
  return box_compare(a,b,0);
}

int box_y_compare(const void * a, const void * b){
  return box_compare(a,b,1);
}

int box_z_compare(const void * a, const void * b){
  return box_compare(a,b,2);
}

bvh_node::bvh_node(hittable **l, int n, float time0, float time1) {
  // Select random axis to split
  int axis = int(3*random_double());
  // Sort hittables along this axis
  if (axis == 0){
    qsort(l, n, sizeof(hittable *), box_x_compare);
  }
  else if (axis == 1){
    qsort(l, n, sizeof(hittable *), box_y_compare);
  }
  else{
    qsort(l, n, sizeof(hittable *), box_z_compare);
  }
  // Split into smaller groups, assign to child nodes
  if (n==1){
    left = right = l[0];
  }
  else if (n == 2){
    left = l[0];
    right = l[1];
  }
  else {
    left = new bvh_node(l, n/2, time0, time1);
    right = new bvh_node(l + n/2, n - n/2, time0, time1);
  }
  aabb box_left, box_right;
  if(!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right)){
    std::cerr << "no bounding bos in bvh_node constructor\n";
  }
  box = surrounding_box(box_left, box_right);
}

bool bvh_node::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  if (box.hit(r, t_min, t_max)){
    hit_record left_rec, right_rec;
    bool hit_left = left->hit(r, t_min, t_max, left_rec);
    bool hit_right = right->hit(r, t_min, t_max, right_rec);
    if (hit_left && hit_right){
      if (left_rec.t < right_rec.t){
        rec = left_rec;
      }
      else {
        rec = right_rec;
      }
      return true;
    }
    else if (hit_left){
      rec = left_rec;
      return true;
    }
    else if (hit_right){
      rec = right_rec;
      return true;
    }
    else return false;
  }
  return false;
}

bool bvh_node::bounding_box(float t0, float t1, aabb& b) const {
  b = box;
  return true;
}

#endif
