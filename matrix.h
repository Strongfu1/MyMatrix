#ifndef MATRIX_H
#define MATRIX_H

#define EPS 1e-6
#include <cmath>
namespace s21 {
class Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void initMatrix();
  void delMatrix();
  bool diffDimensions(const Matrix& other);
  bool notSquare();
  void copyPart(const Matrix& src, const int rows, const int cols);
  void copyMatrix(const Matrix& src);
  void swapRows(int one, int two);
  Matrix scratch(int row, int col);
  double minor(int row, int col);

 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix&);
  Matrix(Matrix&&);
  ~Matrix();

  int rows() { return rows_; }
  int cols() { return cols_; }
  void setCols(int cols);
  void setRows(int rows);

  bool eq_matrix(const Matrix&);
  void sum_matrix(const Matrix&);
  void sub_matrix(const Matrix&);
  void mul_number(const double);
  void mul_matrix(const Matrix&);
  Matrix transpose();
  Matrix calc_complements();
  double determinant();
  Matrix inverse_matrix();

  bool operator==(const Matrix&);
  Matrix& operator=(const Matrix&);
  Matrix& operator+=(const Matrix&);
  Matrix operator+(const Matrix&);
  Matrix& operator-=(const Matrix&);
  Matrix operator-(const Matrix&);
  Matrix& operator*=(const Matrix&);
  Matrix& operator*=(const double);
  Matrix operator*(const Matrix&);
  double& operator()(const int row, const int col);
};

Matrix operator*(const Matrix& lhs, const double rhs);
Matrix operator*(const double lhs, const Matrix& rhs);
}  // namespace s21

#endif  // MATRIX_H
