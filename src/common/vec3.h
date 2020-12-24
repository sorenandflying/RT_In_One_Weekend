#ifndef __VEC3_H__
#define __VEC3_H__

#include <math.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>

class vec3{
public:
// Variables
  float v[3];

// Constructors
  vec3(){}
  vec3(float v0, float v1, float v2) { v[0] = v0; v[1] = v1; v[2] = v2; }

// Get Functions
  inline float x() const { return v[0]; }
  inline float y() const { return v[1]; }
  inline float z() const { return v[2]; }
  inline float r() const { return v[0]; }
  inline float g() const { return v[1]; }
  inline float b() const { return v[2]; }

// Operators
  inline const vec3& operator+() const { return *this; }
  inline vec3& operator-() const { vec3 n(-v[0], -v[1], -v[2]); return n; }
  inline float operator[](int i) const { return v[i]; }
  // inline float& vec3& operator[](int i) const { return e[i]; }

  inline vec3& operator+=(const vec3 &v2);
  inline vec3& operator-=(const vec3 &v2);
  inline vec3& operator*=(const vec3 &v2);
  inline vec3& operator/=(const vec3 &v2);
  inline vec3& operator+=(const float t);
  inline vec3& operator-=(const float t);
  inline vec3& operator*=(const float t);
  inline vec3& operator/=(const float t);

// Functions
  inline float length() const {
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  }
  inline float squared_length() const {
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
  }
  inline void normalize();
  inline vec3 norm();
};

/******** In/Out Operators ********/
inline std::istream& operator>>(std::istream &is, vec3 &t){
  is >> t.v[0] >> t.v[1] >> t.v[2];
  return is;
}

inline std::ostream& operator<<(std::ostream &os, vec3 &t){
  os << t.v[0] << " " << t.v[1] << " " << t.v[2];
  return os;
}

/******** Math Operators ********/

// Vector, Vector operators
inline vec3 operator+(const vec3& v1, const vec3& v2){
  return vec3(v1.v[0] + v2.v[0], v1.v[1] + v2.v[1], v1[2] + v2.v[2]);
}

inline vec3 operator-(const vec3& v1, const vec3& v2){
  return vec3(v1.v[0] - v2.v[0], v1.v[1] - v2.v[1], v1.v[2] - v2.v[2]);
}

inline vec3 operator*(const vec3& v1, const vec3& v2){
  return vec3(v1.v[0] * v2.v[0], v1.v[1] * v2.v[1], v1.v[2] * v2.v[2]);
}

inline vec3 operator/(const vec3& v1, const vec3& v2){
  return vec3(v1.v[0] / v2.v[0], v1.v[1] / v2.v[1], v1.v[2] / v2.v[2]);
}

// Float, Vector operators
inline vec3 operator+(float t, const vec3& v2){
  return vec3(t + v2.v[0], t + v2.v[1], t + v2.v[2]);
}

inline vec3 operator+(const vec3& v2, float t){
  return vec3(t + v2.v[0], t + v2.v[1], t + v2.v[2]);
}

inline vec3 operator-(const vec3& v2, float t){
  return vec3(v2.v[0] - t, v2.v[1] - t, v2.v[2] - t);
}

inline vec3 operator*(float t, const vec3& v2){
  return vec3(t * v2.v[0], t * v2.v[1], t * v2.v[2]);
}

inline vec3 operator*(const vec3& v2, float t){
  return vec3(t * v2.v[0], t * v2.v[1], t * v2.v[2]);
}

inline vec3 operator/(const vec3& v2, float t){
  return vec3(v2.v[0]/t, v2.v[1]/t, v2.v[2]/t);
}

// Self-operators
inline vec3& vec3::operator+=(const vec3& v1){
  v[0] += v1.v[0];
  v[1] += v1.v[1];
  v[2] += v1.v[2];
  return *this;
}

inline vec3& vec3::operator+=(const float t){
  v[0] += t;
  v[1] += t;
  v[2] += t;
  return *this;
}

inline vec3& vec3::operator-=(const vec3& v1){
  v[0] -= v1.v[0];
  v[1] -= v1.v[1];
  v[2] -= v1.v[2];
  return *this;
}

inline vec3& vec3::operator-=(const float t){
  v[0] -= t;
  v[1] -= t;
  v[2] -= t;
  return *this;
}

inline vec3& vec3::operator*=(const vec3& v1){
  v[0] *= v1.v[0];
  v[1] *= v1.v[1];
  v[2] *= v1.v[2];
  return *this;
}

inline vec3& vec3::operator*=(const float t){
  v[0] *= t;
  v[1] *= t;
  v[2] *= t;
  return *this;
}

inline vec3& vec3::operator/=(const vec3& v1){
  v[0] /= v1.v[0];
  v[1] /= v1.v[1];
  v[2] /= v1.v[2];
  return *this;
}

inline vec3& vec3::operator/=(const float t){
  v[0] /= t;
  v[1] /= t;
  v[2] /= t;
  return *this;
}

/******** Vector Math Functions ********/
inline void vec3::normalize(){
  float k = 1.0/this->length();
  v[0] *= k;
  v[1] *= k;
  v[2] *= k;
}

inline vec3 vec3::norm(){
  return vec3(v[0]/this->length(), v[1]/this->length(), v[2]/this->length());
}

inline vec3 normalized(const vec3& v1){
  float k = 1.0/v1.length();
  vec3 v2 = vec3(v1.x()/k, v1.y()/k, v1.z()/k);
  return v2;
}

inline float dot(const vec3& v1, const vec3& v2){
  return v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1] + v1.v[2] * v2.v[2];
}

inline vec3 cross(const vec3& v1, const vec3& v2){
  return vec3(
    v1.v[1]*v2.v[2] - v1.v[2]*v2.v[1],
    v1.v[2]*v2.v[0] - v1.v[0]*v2.v[2],
    v1.v[0]*v2.v[1] - v1.v[1]*v2.v[0]
  );
}

inline vec3 lerp(const vec3& v1, const vec3& v2, float t){
  return t * v2 + (1.0-t) * v1;
}

vec3 random_in_unit_sphere() {
  vec3 p;
  do {
    p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
  } while (p.squared_length() >= 1.0);
  return p;
}

vec3 reflect(const vec3& v, const vec3& n){
  return v - 2.0 * dot(v,n)*n;
}

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted){
  vec3 uv = normalized(v);
  float dt = dot(uv, n);
  float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1.0-dt*dt);
  if(discriminant > 0){
    refracted = ni_over_nt * (uv - n*dt) - n*sqrt(discriminant);
    return true;
  }
  return false;
}

/******** Alternative names ********/
using point3 = vec3;
using color = vec3;

#endif
