#ifndef POINT2_H
#define POINT2_H
#include<iostream>
#include<vector>
#include<cassert>

template <typename T>
class Point2{
public:
  Point2() { x = y = 0; }
  Point2(T xx, T yy) : x(xx), y(yy) { }
  Point2(const Point2<T> &p){
    x = p.x;
    y = p.y;
  }


  Point2<T> &operator=(const Point2<T> &p){
    x = p.x;
    y = p.y;
    return *this;
  }
  
  Point2<T> operator+(const Point2<T> &p){
    return Point2<T>(x + p.x, y + p.y);
  }

  Point2<T> operator-(const Point2<T> &p){
    return Point2<T>(x - p.x, y - p.y);
  }

  Point2<T> operator-() const{
    return Point2<T>(-x, -y);
  }
  
  Point2<T>& operator+=(const Point2<T> &p){
    x += p.x;
    y += p.y;
    return *this;
  }

  Point2<T>& operator-=(const Point2<T> &p){
    x -= p.x;
    y -= p.y;
    return *this;
  }

  template <typename U>
  Point2<T> operator*(U f) const{
    return Point2<T> (f * x, f * y);
  }
  
  template <typename U>
  Point2<T> operator/(U f) const{
    if(f == 0) std::cerr << "divisor cannot be 0.";
    double inv = (double)1 / f;
    return Point2<T> (inv * x, inv * y);
  }
  
  template <typename U>
  Point2<T> &operator*=(U f) {
    x *= f;
    y *= f;
    return *this;
  }
  template <typename U>
  Point2<T> &operator/=(U f) const {
    if(f == 0) std::cerr << "divisor cannot be 0.";
    double inv = (double)1 / f;
    return Point2<T>(inv * x, inv * y);
  }
  
  T operator[](int i) const{
    if(i != 0 && i != 1) std::cerr << "index error.";
    if(i == 0) return x;
    return y;
  }

  T &operator[](int i) {
    if(i != 0 && i != 1) std::cerr << "index error.";
    if(i == 0) return x;
    return y;
  }

  //comparison operations
  bool operator==(const Point2<T> &p) const {
    return x == p.x && y == p.y;
  }
  
  bool operator!=(const Point2<T> &p) const {
    return x != p.x || y == p.y;
  }

  bool operator>(const Point2<T> &p) const {
    return x > p.x;
  }

  bool operator<(const Point2<T> &p) const {
    return x < p.x;
  }

  bool operator>=(const Point2<T> &p) const {
    return x >= p.x;
  }

  bool operator<=(const Point2<T> &p) const {
    return x <= p.x;
  }

  friend std::ostream& operator<< (std::ostream& stream, const Point2<T> &p){
    stream << "(" << p[0] << ", " << p[1] << ")";
    return stream;
  }
  
  // member data
    
  T x, y;
};

#endif // POINT2_H
