/**********************************
 * File:     LinearSystem.h
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2021/1/21
 ***********************************/

#ifndef LA_LINEARSYSTEM_H
#define LA_LINEARSYSTEM_H

#include "Vector.h"
#include "Matrix.h"
#include <cassert>
#include <vector>
#include <cmath>
#include <iostream>

namespace LinearAlgebra {
template <typename E>
class LinearSystem {
private:
  int row, col;
  Matrix<E> *Ab;
  std::vector<int> pivots;
public:
  LinearSystem(Matrix<E> &A, Vector<E> &b) {

    assert(A.row_num() == b.size() && "row number of A must be equal to the length of b");

    row = A.row_num();
    col = A.col_num();

    std::vector<std::vector<E>> res(row, std::vector<E>(col + 1, 0));

    for (int i = 0; i < row; ++i)
      for (int j = 0; j < col; ++j) {
        res[i][j] = A[i][j];
      }

    for (int i = 0; i < row; ++i) {
      res[i][col] = b[i];
    }

    Ab = new Matrix<E>(res);
  }

  ~LinearSystem() {
    if (Ab) {
      delete Ab;
    }
  }

  /// 求行最简矩阵, 如果有解返回true
  bool gauss_jordan_elimination() {
    forward();
    backward();

    int k = pivots.size();
    /// 最后的行均为0，如果相应的最后一列不为0，那么说明无解了.
    for (int i = k; i < row; ++i) {
      if (abs((*Ab)[i][col]) > 1e-8)
        return false;
    }
    return true;
  }

  friend std::ostream &operator<<(std::ostream &os, const LinearSystem<E> &ls) {
    os << "linear system: " << std::endl;
    for (int i = 0; i < ls.row; ++i) {
      for (int j = 0; j < ls.col + 1; ++j) {
        if (j == ls.col) {
          os << "|" << (*ls.Ab)[i][j];
        }else {
          if (j < ls.col - 1)
            os << (*ls.Ab)[i][j] << ",";
          else
            os << (*ls.Ab)[i][j];
        }
      }
      os << std::endl;
    }
    return os;
  }

private:
  int find_max_row(int r, int tc, int row) {
    int pivot = abs((*Ab)[r][tc]);
    int max_row = r;
    for (int i = r + 1; i < row; ++i) {
      if (abs((*Ab)[i][tc]) > pivot) {
        pivot = abs((*Ab)[i][tc]);
        max_row = i;
      }
    }
    return max_row;
  }

  void exchange_row(int r1, int r2) {
    for (int i = 0; i < col + 1; ++i) {
      E t = (*Ab)[r1][i];
      (*Ab)[r1][i] = (*Ab)[r2][i];
      (*Ab)[r2][i] = t;
    }
  }

  void forward() {

    int i = 0, k = 0;
    while (i < row && k < col){

      int max_row = find_max_row(i, k, row);
      exchange_row(i, max_row);

      E pivot = (*Ab)[i][k];

      if (abs(pivot) < 1e-8)
        k += 1;
      else {
          /// 将主元归一
          for (int j = 0; j < col + 1; ++j) {
            (*Ab)[i][j] = (*Ab)[i][j] / pivot;
            if (abs((*Ab)[i][j]) < 1e-8)
              (*Ab)[i][j] = 0;
          }

          for (int m = i + 1; m < row; ++m) {
            E times = (*Ab)[m][k];
            for (int n = 0; n < col + 1; ++n) {
              (*Ab)[m][n] = (*Ab)[m][n] - times * (*Ab)[i][n];
              if (abs((*Ab)[m][n]) < 1e-8)
                (*Ab)[m][n] = 0;
            }
          }
          pivots.push_back(k);
          i += 1;
        }
    }
  }
  void backward() {

    int n = (int)pivots.size();
    for (int i = n - 1; i > 0; i--) {
      int m = pivots[i];
      for (int j = i - 1; j >= 0; j--) {
        E times = (*Ab)[j][m];
        for (int k = 0; k < col + 1; ++k) {
          (*Ab)[j][k] = (*Ab)[j][k] - times * (*Ab)[i][k];
          if (abs((*Ab)[j][k]) < 1e-8)
            (*Ab)[j][k] = 0;
        }
      }
    }
  }
};
}

#endif // LA_LINEARSYSTEM_H
