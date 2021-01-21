/**********************************
 * File:     main.cpp
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2021/1/20
 ***********************************/

#include "Vector.h"
#include "Matrix.h"
#include "LinearSystem.h"
#include "Linalg.h"

void myVectorTest() {
  std::vector<double> v = {1,2,3,4};
  LinearAlgebra::Vector<double> v1(v);

  std::cout << "v1 size: " << v1.size() << std::endl;
  std::cout << "v1 = " << v1 << std::endl;
  std::cout << "v1[0] = " << v1[0] << std::endl;
  std::cout << "v1[3] = " << v1[3] << std::endl;

  std::vector<double> vec2{5,6,7,8};
  LinearAlgebra::Vector<double> v2(vec2);

  std::cout << v1 << " + " << v2 << " = " << v1 + v2 << std::endl;
  std::cout << v1 << " - " << v2 << " = " << v1 - v2 << std::endl;
  std::cout << v1 << " *" << " 5 " << " = " << v1 * 5 << std::endl;
  std::cout << 5 << " * " << v1 << " = " <<  5 * v1 << std::endl;
  std::cout << v1 << " /" << " 5 " << " = " <<  v1 / 5 << std::endl;
  std::cout << v1 << ".dot" << v2 << "=" << v1.dot(v2) << std::endl;

  std::cout << "+" << v1 << "=" << +v1 << std::endl;
  std::cout << "-" << v1 << "=" << -v1 << std::endl;

  LinearAlgebra::Vector<double> zero4 = LinearAlgebra::Vector<double>::zero(4);
  std::cout << "zero4: " << zero4 << std::endl;

  std::cout << v1 << " + " << zero4 << " = " << v1 + zero4 << std::endl;

  std::cout << "v1.norm() = " << v1.norm() << std::endl;

  std::cout << "v1.normalize() = " << v1.normalize() << std::endl;
  std::cout << "v1.normalize().norm() = " << v1.normalize().norm() << std::endl;

  //std::cout << "zero4.normalize() = " << zero4.normalize() << std::endl;
}

void myMatrixTest() {

  std::vector<std::vector<double>> vec = {{1,2,3},{4,5,6}};
  LinearAlgebra::Matrix<double> mat(vec);
  std::cout << mat << std::endl;

  std::cout << "mat[0][1] = " << mat[0][1] << std::endl;
  std::cout << "row size = " << mat.row_num() << std::endl;
  std::cout << "col size = " << mat.col_num() << std::endl;
  std::cout << "mat size = " << mat.size() << std::endl;
  std::cout << "row 0 = " << mat.row_vector(0) << std::endl;
  std::cout << "col 0 = " << mat.col_vector(0) << std::endl;
  std::tuple<int, int> tp = mat.shape();
  std::tuple<int, int> shape = mat.shape();
  std::cout << "shape: (" << std::get<0>(shape) << "," << std::get<1>(shape) << ")" << std::endl;


  std::vector<std::vector<double>> vec2{{2,3,5},{1,4,9}};
  LinearAlgebra::Matrix<double> mat2(vec2);
  std::cout << mat << " + " << mat2 << " = " << mat + mat2 << std::endl;
  std::cout << mat << " - " << mat2 << " = " << mat - mat2 << std::endl;

  std::cout << mat << " * " << 5 << " = " << mat * 5 << std::endl;
  std::cout << 5 << " * " << mat << " = " << 5 * mat << std::endl;
  std::cout << mat << " / " << 5 << " = " << mat / 5 << std::endl;

  std::cout << "+mat" << " = " << +mat << std::endl;
  std::cout << "-mat" << " = " << -mat << std::endl;

  std::vector<double> v1{2,2,3};
  LinearAlgebra::Vector<double> v(v1);
  std::cout << mat << " * "  << v << " = " << mat.dot(v) << std::endl;

  std::vector<std::vector<double>> v3{{1,2},{3,4},{5,6}};
  LinearAlgebra::Matrix<double> mat3(v3);
  std::cout << mat << " * " << mat3 << " = " << mat.dot(mat3) << std::endl;

  std::cout << mat << ".T" << " = " << mat.T() << std::endl;

  std::cout << LinearAlgebra::Matrix<double>::zero(5,6) << std::endl;
  std::cout << LinearAlgebra::Matrix<double>::identify(5) << std::endl;
}

void linearSystemTest() {
  std::vector<double> b = {7,-11,1};
  std::vector<std::vector<double>> A = {{1, 2, 4}, {3, 7, 2}, {2, 3, 3}};
  LinearAlgebra::Matrix<double> mat(A);
  LinearAlgebra::Vector<double> v(b);
  LinearAlgebra::LinearSystem<double> ls(mat, v);
  //std::cout << ls << std::endl;
  ls.gauss_jordan_elimination();
  std::cout << ls << std::endl;

  std::vector<double> b2 = {-9, 19, -13};
  std::vector<std::vector<double>> A2 = {{1, -3, 5}, {2, -1, -3}, {3, 1, 4}};
  LinearAlgebra::Matrix<double> mat2(A2);
  LinearAlgebra::Vector<double> v2(b2);
  LinearAlgebra::LinearSystem<double> ls2(mat2, v2);
  //std::cout << ls2 << std::endl;
  ls2.gauss_jordan_elimination();
  std::cout << ls2 << std::endl;

  std::vector<double> b3 = {6, -10, -16};
  std::vector<std::vector<double>> A3 = {{1, 2, -2}, {2, -3, 1}, {3, -1, 3}};
  LinearAlgebra::Matrix<double> mat3(A3);
  LinearAlgebra::Vector<double> v3(b3);
  LinearAlgebra::LinearSystem<double> ls3(mat3, v3);
  //std::cout << ls3 << std::endl;
  ls3.gauss_jordan_elimination();
  std::cout << ls3 << std::endl;

  std::vector<double> b4 = {4, 32, 13};
  std::vector<std::vector<double>> A4 = {{3, 1, -2}, {5, -3, 10}, {7, 4, 16}};
  LinearAlgebra::Matrix<double> mat4(A4);
  LinearAlgebra::Vector<double> v4(b4);
  LinearAlgebra::LinearSystem<double> ls4(mat4, v4);
  //std::cout << ls4 << std::endl;
  ls4.gauss_jordan_elimination();
  std::cout << ls4 << std::endl;


  std::vector<double> b5 = {31, 36, 11};
  std::vector<std::vector<double>> A5 = {{6, -3, 2}, {5, 1, 12}, {8, 5, 1}};
  LinearAlgebra::Matrix<double> mat5(A5);
  LinearAlgebra::Vector<double> v5(b5);
  LinearAlgebra::LinearSystem<double> ls5(mat5, v5);
  //std::cout << ls5 << std::endl;
  ls5.gauss_jordan_elimination();
  std::cout << ls5 << std::endl;

  std::vector<double> b6 = {3, -1, 8};
  std::vector<std::vector<double>> A6 = {{1, 1, 1}, {1, -1, -1}, {2, 1, 5}};
  LinearAlgebra::Matrix<double> mat6(A6);
  LinearAlgebra::Vector<double> v6(b6);
  LinearAlgebra::LinearSystem<double> ls6(mat6, v6);
  //std::cout << ls6 << std::endl;
  ls6.gauss_jordan_elimination();
  std::cout << ls6 << std::endl;

  std::vector<double> b7 = {5, 6};
  std::vector<std::vector<double>> A7 = {{2, 3}, {3, 2}};
  LinearAlgebra::Matrix<double> mat7(A7);
  LinearAlgebra::Vector<double> v7(b7);
  LinearAlgebra::LinearSystem<double> ls7(mat7, v7);
  std::cout << ls7 << std::endl;
  ls7.gauss_jordan_elimination();
  std::cout << ls7 << std::endl;


  std::vector<double> b8 = {3, 2.5, 7};
  std::vector<std::vector<double>> A8 = {{2, 2},{2, 1},{1, 2}};
  LinearAlgebra::Matrix<double> mat8(A8);
  LinearAlgebra::Vector<double> v8(b8);
  LinearAlgebra::LinearSystem<double> ls8(mat8, v8);
  //std::cout << ls8 << std::endl;
  if (!ls8.gauss_jordan_elimination())
    std::cout << "No Solution!" << std::endl;
  std::cout << ls8 << std::endl;

  std::vector<double> b9 = {1, 0, 0};
  std::vector<std::vector<double>> A9 = {{2, 0, 1}, {-1, -1, -2}, {-3, 0, 1}};
  LinearAlgebra::Matrix<double> mat9(A9);
  LinearAlgebra::Vector<double> v9(b9);
  LinearAlgebra::LinearSystem<double> ls9(mat9, v9);
  //std::cout << ls9 << std::endl;
  if (ls9.gauss_jordan_elimination()) {
    std::cout << "No Solution!" << std::endl;
  }
  std::cout << ls9 << std::endl;

  std::vector<double> b10 = {0.2, -1.4, 0.6};
  LinearAlgebra::Vector<double> V10(b10);
  std::cout << mat9.dot(V10) << std::endl;

  std::vector<std::vector<double>> A11 = {{1,2}, {3,4}};
  LinearAlgebra::Matrix<double> mat11(A11);

}

int main() {

  std::vector<std::vector<double>> v2d = {{1,2}, {3,4}};
  bool isExist = false;
  LinearAlgebra::Matrix<double> mat(v2d);
  LinearAlgebra::Matrix<double> invMat = LinearAlgebra::Linalg<double>::inv(mat, &isExist);
  if (isExist) {
    std::cout << mat << ".inv = " << invMat << std::endl;
    std::cout << mat << ".dot = " << invMat << mat.dot(invMat) << std::endl;
  }else {
    std::cout << mat << "no inv mat" << std::endl;
  }

  return 0;
}