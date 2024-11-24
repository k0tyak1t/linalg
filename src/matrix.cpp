#include "matrix.h"
#include <cstring>

matrix::matrix()
{
	size = 0;
	matrix_elements = nullptr;
	eig_calculated = false;
	eigval = nullptr;
	eigvec = nullptr;
}

matrix::matrix(int init_size)
{
	size = init_size;
	matrix_elements = new double[size * size];
	eig_calculated = false;
	eigval = nullptr;
	eigvec = nullptr;
}

matrix::matrix(int init_size, double* init_arr)
{
	size = init_size;
	matrix_elements = new double[size * size];
	memcpy(matrix_elements, init_arr, size * size * sizeof(double));
	eig_calculated = false;
	eigval = nullptr;
	eigvec = nullptr;
}

matrix::matrix(const matrix& init_matrix)
{
	size = init_matrix.size;
	matrix_elements = new double[size * size];
	for (int i = 0; i < size * size; ++i) {
		matrix_elements[i] = init_matrix.matrix_elements[i];
	}
	eig_calculated = false;
	eigval = nullptr;
	eigvec = nullptr;
}

matrix::~matrix()
{
	if (size) {
		delete[] matrix_elements;
	}
	
	if (eig_calculated) {
		delete[] eigval;
		delete[] eigvec;
	}
}

double* matrix::operator[](int row)
{
	return &matrix_elements[row * size];
}

const double* matrix::operator[](int row) const
{
	return &matrix_elements[row * size];
}

matrix& matrix::operator=(const matrix& other)
{
	if (this == &other) {
		return *this;
	}

	size = other.size;
	delete[] matrix_elements;
	matrix_elements = new double[size * size];
	for (int i = 0; i < size * size; ++i) {
		matrix_elements[i] = other.matrix_elements[i];
	}
	return *this;
}

matrix& matrix::operator=(const double* arr)
{
  for (int i = 0; i < size * size; ++i) {
    matrix_elements[i] = arr[i];
  }

  return *this;
}

matrix matrix::operator+(const matrix& other)
{
	matrix result(size);
	for (int i = 0; i < size * size; ++i) {
		result.matrix_elements[i] = matrix_elements[i] + other.matrix_elements[i];
	}
	return result;
}

matrix matrix::operator+(const double num)
{
	for (int i = 0; i < size; ++i) {
		(*this)[i][i] *= num;
	}
	return *this;
}

matrix& matrix::operator+=(const matrix& other)
{
	for (int i = 0; i < size * size; ++i) {
		matrix_elements[i] += other.matrix_elements[i];
	}
	return *this;
}

matrix& matrix::operator+=(const double num)
{
	for (int i = 0; i < size; ++i) {
		(*this)[i][i] += num;
	}
	return *this;
}

matrix matrix::operator-()
{
	matrix result(size);

	for (int i = 0; i < size * size; ++i) {
		result.matrix_elements[i] = -matrix_elements[i];
	}
	return result;
}

matrix matrix::operator-(const matrix& other)
{
	matrix result(size);

	for (int i = 0; i < size * size; ++i) {
		result.matrix_elements[i] = matrix_elements[i] - other.matrix_elements[i];
	}
	return result;
}

matrix matrix::operator-(const double num)
{
	matrix result(size);

	for (int i = 0; i < size; ++i) {
		(*this)[i][i] += num;
	}
	return *this;
}

matrix& matrix::operator-=(const matrix& other)
{
	for (int i = 0; i < size * size; ++i) {
		matrix_elements[i] -= other.matrix_elements[i];
	}
	return *this;
}

matrix& matrix::operator-=(const double num)
{
	for (int i = 0; i < size; ++i) {
		(*this)[i][i] -= num;
	}
	return *this;
}

matrix matrix::operator*(const double num)
{
	matrix result(size);
	for (int i = 0; i < size * size; ++i) {
		result.matrix_elements[i] *= num;
	}
	return result;
}

matrix matrix::operator*(const matrix& other)
{
	matrix result(size);

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			result[i][j] = 0;
			for (int k = 0; k < size; ++k) {
				result[i][j] += (*this)[i][k] * other[k][j];
			}
		}
	}
	return result;
}

matrix& matrix::operator*=(const matrix& other)
{
	matrix result(size);
	result = (*this) * other;
	(*this) = result;
	return *this;
}

matrix& matrix::operator*=(const double num)
{
	for (int i = 0; i < size * size; ++i) {
		matrix_elements[i] *= num;
	}
	return *this;
}

matrix matrix::operator/(const double num)
{
	matrix result(size);
	for (int i = 0; i < size * size; ++i) {
		result.matrix_elements[i] = matrix_elements[i] / num;
	}
	return result;
}

matrix& matrix::operator/=(const double num)
{
	for (int i = 0; i < size * size; ++i) {
		matrix_elements[i] /= num;
	}
	return *this;
}

matrix matrix::T()
{
	matrix result(size);
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			result[i][j] = (*this)[j][i];
		}
	}
	return result;
}

matrix matrix::minor(int i, int j)
{
	matrix result(size - 1);
	int linear_idx = 0;
	for (int k = 0; k < size; ++k) {
		for (int l = 0; l < size; ++l) {
			if (k != i && l != j) {
				result.matrix_elements[linear_idx] = (*this)[k][l];
				linear_idx += 1;
			}
		}
	}
	return result;
}

double matrix::det()
{
	if (size == 0) {return 0; }
	if (size == 1) {return matrix_elements[0]; }

	if (size == 2) {
		return (*this)[0][0] * (*this)[1][1] -
			   (*this)[0][1] * (*this)[1][0];
	}

	double res = 0;

	for (int i = 0; i < size; ++i) {
		if (i%2==0) {
			res += (*this)[0][i] * (*this).minor(0, i).det();}
		else {
			res -= (*this)[0][i] * (*this).minor(0, i).det();
			}
	}

	return res;
}

void matrix::print()
{
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			std::cout << (*this)[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

