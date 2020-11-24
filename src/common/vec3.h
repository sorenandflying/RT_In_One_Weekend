#ifndef __VEC3_H__
#define __VEC3_H__

#include <math.h>
#include <stdlib.h>
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

#endif
