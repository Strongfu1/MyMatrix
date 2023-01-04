#include "matrix.h"
/* START OF SUPPORT FUNCTIONS */

namespace s21 {

inline void Matrix::initMatrix() {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void Matrix::delMatrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  cols_ = 0;
  rows_ = 0;
  matrix_ = nullptr;
}

void Matrix::copyPart(const Matrix& src, const int rows, const int cols) {
  if (rows_ < rows || src.rows_ < rows || cols_ < cols || src.cols_ < cols)
    throw "wrong size";
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j) matrix_[i][j] = src.matrix_[i][j];
}

void Matrix::copyMatrix(const Matrix& src) { copyPart(src, rows_, cols_); }

bool Matrix::diffDimensions(const Matrix& other) {
  return (rows_ != other.rows_ || cols_ != other.cols_);
}

bool Matrix::notSquare() { return (rows_ != cols_); }

Matrix Matrix::scratch(int row, int col) {
  Matrix res(cols_ - 1, rows_ - 1);
  for (int i = 0, x = 0; i < rows_; ++i) {
    if (i == row) continue;
    for (int j = 0, y = 0; j < cols_; ++j) {
      if (j == col) continue;
      res.matrix_[x][y] = matrix_[i][j];
      ++y;
    }
    ++x;
  }
  return res;
}

double Matrix::minor(int row, int col) {
  Matrix temp = scratch(row, col);
  return temp.determinant();
}

void Matrix::swapRows(int one, int two) {
  double* temp = matrix_[one];
  matrix_[one] = matrix_[two];
  matrix_[two] = temp;
}

inline Matrix mulNumber(const Matrix& mat, const double num) {
  Matrix temp(mat);
  return temp *= num;
}

/* END OF SUPPORT FUNCTIONS */

Matrix::Matrix() : rows_(1), cols_(1) { initMatrix(); }

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) { initMatrix(); }

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
  initMatrix();
  copyMatrix(other);
}

Matrix::Matrix(Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

Matrix::~Matrix() { delMatrix(); }

void Matrix::setCols(int cols) {
  if (cols < 1) throw "cols can't be lower than 1";
  Matrix temp(rows_, cols);
  if (cols > cols_) {
    temp.copyPart(*this, rows_, cols_);
  } else {
    temp.copyPart(*this, rows_, cols);
  }
  *this = temp;
}

void Matrix::setRows(int rows) {
  if (rows < 1) throw "rows can't be lower than 1";

  Matrix temp(rows, cols_);
  if (rows > rows_) {
    temp.copyPart(*this, rows_, cols_);
  } else {
    temp.copyPart(*this, rows, cols_);
  }
  *this = temp;
}

bool Matrix::eq_matrix(const Matrix& other) {
  bool res = true;
  if (diffDimensions(other)) {
    res = false;
  } else {
    for (int i = 0; i < rows_ && res; ++i)
      for (int j = 0; j < cols_ && res; ++j)
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) res = false;
  }
  return res;
}

void Matrix::sub_matrix(const Matrix& other) {
  if (diffDimensions(other)) throw "Diff dimensions";

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] -= other.matrix_[i][j];
}

void Matrix::sum_matrix(const Matrix& other) {
  if (diffDimensions(other)) throw "Diff dimensions";

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] += other.matrix_[i][j];
}

void Matrix::mul_number(const double num) {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}

void Matrix::mul_matrix(const Matrix& other) {
  if (cols_ != other.rows_) throw "1st matrix cols != 2nd matrix rows";

  Matrix temp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < other.cols_; j++)
      for (int k = 0; k < cols_; k++)
        temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
  *this = temp;
}

Matrix Matrix::transpose() {
  Matrix newMatrix(cols_, rows_);
  for (int i = 0; i < cols_; ++i)
    for (int j = 0; j < rows_; ++j) newMatrix.matrix_[i][j] = matrix_[j][i];
  return newMatrix;
}

double Matrix::determinant() {  // Bareiss algorithm
  if (notSquare()) throw "Not squared matrix";
  double sign = 1;
  Matrix temp(*this);
  for (int k = 0; k < temp.cols_ - 1; k++) {
    if (temp.matrix_[k][k] == 0) {
      int m;
      for (m = k + 1; m < temp.cols_; m++) {
        if (temp.matrix_[m][k] != 0) {
          temp.swapRows(m, k);
          sign = -sign;
          break;
        }
      }
      if (m == temp.cols_) return 0;
    }
    for (int i = k + 1; i < temp.cols_; ++i) {
      for (int j = k + 1; j < temp.cols_; ++j) {
        temp.matrix_[i][j] = temp.matrix_[k][k] * temp.matrix_[i][j] -
                             temp.matrix_[i][k] * temp.matrix_[k][j];
        if (k != 0) {
          temp.matrix_[i][j] /= temp.matrix_[k - 1][k - 1];
        }
      }
    }
  }
  return temp.matrix_[rows_ - 1][cols_ - 1] * sign;
}

Matrix Matrix::calc_complements() {
  if (notSquare()) throw "matrix is not square";
  Matrix temp(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      temp.matrix_[i][j] = (((i + j) % 2) ? -1 : 1) * minor(i, j);

  return temp;
}

Matrix Matrix::inverse_matrix() {
  double det = determinant();
  if (!det) throw "determinant equals 0";
  Matrix other;
  if (cols_ != 1) {
    Matrix temp = calc_complements();
    other = temp.transpose();
    other.mul_number(1 / det);
  } else {
    other = *this;
    other.matrix_[0][0] = 1 / det;
  }
  return other;
}

bool Matrix::operator==(const Matrix& other) { return eq_matrix(other); }

Matrix& Matrix::operator=(const Matrix& other) {
  if (*this == other) return *this;

  if (rows_ == other.rows_ && cols_ == other.cols_) {
    copyMatrix(other);
  } else {
    delMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    initMatrix();
    copyMatrix(other);
  }
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  this->sum_matrix(other);
  return *this;
}

Matrix Matrix::operator+(const Matrix& rhs) {
  Matrix temp(*this);
  return temp += rhs;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  this->sub_matrix(other);
  return *this;
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix temp(*this);
  return temp -= other;
}

Matrix& Matrix::operator*=(const double num) {
  this->mul_number(num);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  this->mul_matrix(other);
  return *this;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix temp(*this);
  return temp *= other;
}

Matrix operator*(const Matrix& lhs, const double rhs) {
  return mulNumber(lhs, rhs);
}

Matrix operator*(const double lhs, const Matrix& rhs) {
  return mulNumber(rhs, lhs);
}

double& Matrix::operator()(int row, int col) {
  if (row > rows_ || col > cols_) throw "wrong size";
  return matrix_[row][col];
}
}  // namespace s21