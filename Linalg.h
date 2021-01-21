/**********************************
 * File:     Linalg.h
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2021/1/21
 ***********************************/

#ifndef LA_LINALG_H
#define LA_LINALG_H

#include "LinearSystem.h"

namespace LinearAlgebra {
template <typename E>
class Linalg {
public:
  static Matrix<E> inv(Matrix<E> &A, bool *isExist) {

    assert(A.row_num() == A.col_num());

    int n = A.row_num();
    Matrix<E> identifyMat = Matrix<E>::identify(n);
    LinearSystem<E> ls(A, identifyMat);

    if (!ls.gauss_jordan_elimination()) {
      if (isExist)
        *isExist = false;
      return Matrix<E>::identify(n);
    }

    if (isExist)
      *isExist = true;
    return ls.getMatrixSolution();
  }
};
}

#endif // LA_LINALG_H
