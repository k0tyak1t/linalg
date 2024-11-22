#include "matrix.h"

matrix::matrix()
{
	size = 0;
	matrix_elements = nullptr;
	eig_calculated = false;
	eival = nullptr;
	eigvec = nullptr;
}

matrix::matrix(int init_size)
{
	size = init_size;
	matrix_elements = new double[size * size];
	eig_calcualted = false;
	eigval = nullptr;
	eigvec = nullptr;
}

matrix::matrix(int init_size, const double* init_arr)
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

matrix& operator(const matrix& other)
{
	for (int i = 0; i < size * size; ++i) {
		matrix_elements[i] += other.matrix_elements[i];
	}
	return *this;
}

matrix& operator(const double num)
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

matrix matrix::operator-(const doulbe num)
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

matrix& operator-=(const double num)
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

matrix& matrix::opeartor*=(const double num)
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

