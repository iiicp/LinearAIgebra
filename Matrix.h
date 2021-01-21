/**********************************
 * File:     Matrix.h
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2021/1/20
 ***********************************/

#ifndef LA_MATRIX_H
#define LA_MATRIX_H

#include <vector>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include "Vector.h"
#include <tuple>

namespace LinearAlgebra {
template <typename E>
class Matrix {
private:
  Vector<E> *rowArr;
  int row;
public:

  Matrix(std::vector<std::vector<E>> &vec2d) {

    assert(vec2d.size() > 0);
    row = vec2d.size();
    rowArr = new Vector<E>[row];
    for (int i = 0; i < row; ++i)
        rowArr[i] = new Vector<E>(vec2d[i]);
  }

  ~Matrix() {
    if (rowArr) {
      delete [] rowArr;
    }
  }

  /// copy construct
  Matrix(const Matrix &other) : row(other.row_num()), rowArr(new Vector<E>[other.row_num()]) {

    for (int i = 0; i < row; ++i)
      rowArr[i] = other[i];
  }

  /// zero matrix
  static Matrix zero(int r, int c) {

    std::vector<std::vector<E>> res(r, std::vector<E>(c, 0));
    return Matrix(res);
  }

  /// 单位矩阵, 对角线为1
  static Matrix identify(int n) {

    std::vector<std::vector<E>> res(n, std::vector<E>(n, 0));
    for (int i = 0; i < n; ++i)
      res[i][i] = 1;
    return Matrix(res);
  }

  /// mat * vector
  Vector<E> dot(const Vector<E> &other) {

    assert(col_num() == other.size());

    std::vector<E> res(row);

    for (int i = 0; i < row; ++i) {
      res[i] = rowArr[i].dot(other);
    }
    return Vector<E>(res);
  }

  /// mat * mat
  Matrix dot(const Matrix &other) {

    assert(col_num() == other.row_num());

    std::vector<std::vector<E>> res(row, std::vector<E>(other.col_num(), 0));

    for (int i = 0; i < row; ++i)
      for (int j = 0; j < other.col_num(); ++j)
        res[i][j] = rowArr[i].dot(other.col_vector(j));

    return Matrix(res);
  }

  /// T
  Matrix T() {

    int rowSize = row_num(), colSize = col_num();
    std::vector<std::vector<E>> res(colSize, std::vector<E>(rowSize, 0));

    for (int i = 0; i < colSize; ++i) {
      for (int j = 0; j < rowSize; ++j) {
        res[i][j] = rowArr[j][i];
      }
    }
    return Matrix(res);
  }

  /// 返回矩阵的第index个行向量
  Vector<E> row_vector(int index) const {
    return rowArr[index];
  }

  /// 返回矩阵的第index个列向量
  Vector<E> col_vector(int index) const{
    std::vector<E> cols(row);
    for (int i = 0; i < row; ++i)
      cols[i] = rowArr[i][index];
    return Vector<E>(cols);
  }

  /// getItem
  Vector<E> &operator[](int index) {
    return rowArr[index];
  }

  /// getItem const
  const Vector<E> &operator[](int index) const {
    return rowArr[index];
  }

  /// 返回两个矩阵的加法
  Matrix operator+(const Matrix& other) {

    assert(row == other.row && col_num() && other.col_num());

    std::vector<std::vector<E>> res(row, std::vector<E>(col_num(), 0));

    int colSize = col_num();
    for (int i = 0; i < row; ++i)
      for (int j = 0; j < colSize; ++j)
        res[i][j] = rowArr[i][j] + other[i][j];

    return Matrix(res);
  }

  /// 返回两个矩阵的减法
  Matrix operator-(const Matrix& other) {

    assert(row == other.row && col_num() && other.col_num());

    std::vector<std::vector<E>> res(row, std::vector<E>(col_num(), 0));

    int colSize = col_num();
    for (int i = 0; i < row; ++i)
      for (int j = 0; j < colSize; ++j)
        res[i][j] = rowArr[i][j] - other[i][j];

    return Matrix(res);
  }

  /// 返回数量除法结果
  Matrix operator/(const E k) {

    assert(abs(k - 0) > 1e-8);

    std::vector<std::vector<E>> res(row, std::vector<E>(col_num(), 0));

    int colSize = col_num();
    for (int i = 0; i < row; ++i)
      for (int j = 0; j < colSize; ++j)
        res[i][j] = rowArr[i][j] / k;

    return Matrix(res);
  }

  /// neg
  const Matrix operator-() const{

    std::vector<std::vector<E>> res(row, std::vector<E>(col_num(), 0));

    int colSize = col_num();
    for (int i = 0; i < row; ++i)
      for (int j = 0; j < colSize; ++j)
        res[i][j] = rowArr[i][j] * -1;

    return Matrix(res);
  }

  /// pos
  const Matrix operator+() const{
    return *this;
  }

  /// 返回矩阵元素的个数
  int size() const {
    return row * rowArr[0].size();
  }

  /// 返回矩阵的行数
  int row_num() const {
    return row;
  }

  /// 返回矩阵的列数
  int col_num() const {
    return rowArr[0].size();
  }

  /// 返回矩阵的形状: (行数，列数)
  const std::tuple<int, int> shape() {
    return std::tuple<int, int>(row, rowArr[0].size());
  }

  /// 返回矩阵的数量乘法 self * k
  friend Matrix operator*(const Matrix& self, const E k) {

    int rowSize = self.row_num(), colSize = self.col_num();
    std::vector<std::vector<E>> res(rowSize, std::vector<E>(colSize, 0));
    for (int i = 0; i < rowSize; ++i)
      for (int j = 0; j < colSize; ++j)
        res[i][j] = self[i][j] * k;

    return Matrix(res);
  }

  /// 返回矩阵的数量乘法 k * self
  friend Matrix operator*(const E k, const Matrix& self) {
    return self * k;
  }

  /// 打印矩阵
  friend std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
    os << "Matrix(" << std::endl;
    for (int i = 0; i < mat.row; ++i) {
      os << "[";
      int col = mat.rowArr[i].size();
      for (int j = 0; j < col - 1; ++j) {
        os << mat.rowArr[i][j] << ",";
      }
      os << mat.rowArr[i][col - 1] << "]" << std::endl;
    }
    os << ")" << std::endl;
    return os;
  }
};
}

#endif // LA_MATRIX_H
