# MyMatrix

## Description

Project implements C++ Matrix class and some operations on them.


## Constructors

Constuctor | Description
--- | ---
Matrix() | Constructs matrix with 1X1 dimensions with zero element
Matrix(int rows,int cols) | Constructs matrix with rowsXcols dimensions, with every elements equal to zero
Matrix(const Matrix&) | Copy constructor
Matrix(const Matrix&&) | Move constructor


## Methods

Return Value | Method | Description | Exceptions
--- | --- | --- | ---
bool | eq_matrix(const Matrix&) | Checks matrixes for equality | noexcept
void | sum_matrix(const Matrix&) | Sums matrix to current one | Different dimensions
void | sub_matrix(const Matrix&) | Subtracts matrix from current one | Different dimensions
void | mul_number(const double num) | Multiplies current matrix to a number | noexcept
void | mul_matrix(const Matrix&) | Multiplies current matrix to matrix | First matrix cols!=rows of second matrix
Matrix | transpose() | Returns transposed matrix | noexcept
Matrix | calc_complements() | Returns the algebraic addition matrix | Matrix isn't square
double | determinant() | Calculates determinant | Matrix isn't square
Matrix | inverse_matrix() | Returns the inverse matrix | Determinant equals 0
int | rows() | Returns rows of matrix | noexcept
int | cols() | Returns cols of matrix | noexcept
void | set_cols(int) | Changes cols of matrix, if new value is greater, new elements are equal to zero | Argument less than 1
void | set_rows(int) | Changes rows of matrix, if new value is greater, new elements are equal to zero | Argument less than 1


## Overloaded Operators

Operator | Description | Exceptions
--- | --- | ---
\+ | Sums two matrixes and returns result | Different dimensions
\- | Subtracts two matrixes and returns result | Different dimensions
\* | Multiplies matrix to matrix/number and returns result | First matrix cols!=rows of second matrix
== | Checks for matrixes equality | noexcept
= | Matrix assignment | noexcept
+= | Addition assignment | Different dimensions
-= | Subtraction assignment | Different dimensions
*= | Multiplication by matrix/number assignment | First matrix cols!=rows of second matrix
(int i, int j) | Mutator/Accessor by indexes | Index is outside of matrix


## Compiling

Project compiles using Makefile. To compile project to static library:
```sh
make
```


