/**********************************
 * File:     Vector.h
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2021/1/20
 ***********************************/

#ifndef LINEARAIGEBRA_VECTOR_H
#define LINEARAIGEBRA_VECTOR_H

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <exception>

namespace LinearAlgebra {

struct ZeroDivisionError : public std::exception
{
public:
  ZeroDivisionError(const char *msg) : msg(msg) {
  }
  const char * what () const throw ()
  {
    return msg;
  }

private:
  const char *msg;
};

template <typename E>
class Vector {
private:
  E *value;
  int len;
public:
  Vector() : len(0), value(nullptr) {
  }

  Vector(std::vector<E> &vec) {
    assert(vec.size() > 0 && "vec must greater zero");
    len = vec.size();
    value = new E[len];
    for (int i = 0; i < len; ++i)
      value[i] = vec[i];
  }

  ~Vector() {
    if (value == nullptr)
      delete[] value;
  }

  /// 拷贝构造 (深拷贝)
  Vector(const Vector &other) : len(other.len), value(new E[other.len]) {
    for (int i = 0; i < len; ++i)
      value[i] = other[i];
  }

  /// 拷贝赋值运算符
  Vector &operator=(const Vector &other) {

    /// 先将值拷贝到临时位置（防止是自己赋值给自己）
    E *temp = new E[other.len];
    for (int i = 0; i < other.len; ++i)
      temp[i] = other[i];

    /// 释放旧数据
    if (value)
      delete [] value;

    /// 赋值新值
    len = other.len;
    value = temp;

    return *this;
  }

  Vector *operator=(const Vector *other) {

    if (this == other)
      return this;

    /// 先将值拷贝到临时位置
    E *temp = new E[other->len];
    for (int i = 0; i < other->len; ++i)
      temp[i] = other->value[i];

    /// 释放旧对象
    if (value)
      delete [] value;

    /// 赋值新值
    len = other->len;
    value = temp;

    return this;
  }

  /// 返回向量的模
  double norm() {

    double sum = 0;
    for (int i = 0; i < len; ++i)
      sum += value[i] * value[i];
    return sqrt(sum);
  }

  /// 归一化, 单位向量
  Vector normalize() {

    double normVal = norm();
    if (normVal < 1e-8) {
      throw ZeroDivisionError("Normalize error! norm is zero.");
    }

    std::vector<E> res(len);
    for (int i = 0; i < len; ++i)
      res[i] = value[i] / normVal;
    return Vector(res);
  }

  /// 向量点乘，返回结果标量
  double dot(const Vector &other) {

    assert(len == other.len && "Error in dot product. Length of vectors must be same.");

    double res = 0.0;
    for (int i = 0; i < len; ++i) {
      res += other[i] * value[i];
      if (abs(res) < 1e-8)
        res = 0;
    }
    return res;
  }

  /// 返回一个dim维的零向量
  static Vector zero(int dim) {
    std::vector<E> res(dim, 0);
    return Vector(res);
  }

  /// getItem
  E& operator[](int index) {
    assert(index>=0 && index<len && "out of index");
    return value[index];
  }

  /// getItem const
  const E& operator[](int index) const{
    assert(index>=0 && index<len && "out of index");
    return value[index];
  }

  /// 向量加法，返回结果向量
  Vector<E> operator+(const Vector<E>& other) {

    assert(len == other.size() && "Error in adding. Length of vectors must be same.");

    std::vector<E> res(len);
    for (int i = 0; i < len; ++i)
      res[i] = value[i] + other[i];
    return Vector(res);
  }

  /// 向量减法，返回结果向量
  Vector<E> operator-(const Vector<E>& other) {

    assert(len == other.size() && "Error in subbing. Length of vectors must be same.");

    std::vector<E> res(len);
    for (int i = 0; i < len; ++i)
      res[i] = value[i] - other[i];
    return Vector(res);
  }

  /// neg
  const Vector operator-() const {

    std::vector<E> res(len);
    for (int i = 0; i < len; ++i)
      res[i] = value[i] * -1.0;
    return Vector(res);
  }

  /// pos
  const Vector operator+() const {

    std::vector<E> res(len);
    for (int i = 0; i < len; ++i)
      res[i] = value[i];
    return Vector(res);
  }

  /// len
  int size() const{
    return len;
  }

  /// friend 向量加法
  friend Vector<E> operator+(const Vector<E> &self, const Vector<E>& other) {
    return self + other;
  }

  /// friedn 向量减法
  friend Vector<E> operator-(const Vector<E> &self, const Vector<E>& other) {
    return self - other;
  }

  /// 返回数量乘法的结果向量: self * k
  friend Vector<E> operator*(const Vector<E> &self, const E k) {

    std::vector<E> res(self.len);
    for (int i = 0; i < self.len; ++i)
      res[i] = self[i] * k;
    return Vector(res);
  }

  /// 返回数量乘法的右乘结果: k * self
  friend Vector<E> operator*(const E k, const Vector<E> &self) {
    return self * k;
  }

  /// 返回数量除法 self / k
  friend Vector<E> operator/(const Vector<E> &self, const E k) {

    assert(k != 0);

    return (1 / k) * self;
  }

  /// output
  friend std::ostream& operator<<(std::ostream &os, const Vector &v) {
    os << "(";
    int sz = v.len;
    for (int i = 0; i < sz - 1; ++i)
      os << v.value[i] << ",";
    os << v.value[sz-1] << ")";
    return os;
  }
};
}



#endif // LINEARAIGEBRA_VECTOR_H
