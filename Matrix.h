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
#include "Vector.h"
#include <tuple>

namespace LinearAlgebra {
class Matrix1d;
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

  /// 返回矩阵的第index个行向量
  Vector<E> row_vector(int index) {
    return rowArr[index];
  }

  /// 返回矩阵的第index个列向量
  Vector<E> col_vector(int index) {
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
    return std::make_tuple(row, rowArr[0].size());
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
