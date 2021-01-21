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

void myVectorTest() {
  std::vector<double> vec{1,2,3,4};
  LinearAlgebra::Vector<double> v1(vec);

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

  std::vector<std::vector<double>> vec{{1,2,3},{4,5,6}};
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

int main() {


  return 0;
}