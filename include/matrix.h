#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <vector>

class matrix
{
public:
	matrix(); // default constructor
	matrix(int); // size initializer
	matrix(int, double*); // initialize with array
	matrix(const matrix&); // initialize with other matrix
	~matrix(); // destructor
	double* operator[](int); // row setter
	const double* operator[](int) const; // row getter
	matrix& operator=(const matrix&); // assignement
	matrix operator+(const matrix&); // sum of matrices
	matrix operator+(const double); // add const * identity
	matrix& operator+=(const matrix&); // add matrix and assign
	matrix& operator+=(const double);
	matrix operator-();
	matrix operator-(const matrix&); // substract
	matrix operator-(const double);
	matrix& opeartor-=(const matrix&); // substract and assign
	matrix& operator-=(const double);
	matrix operator*(const double); // multiply by number
	matrix operator*(const matrix&); // matrix product
	matrix& operator*=(const matrix&); // obvious
	matrix& operator*=(const double); // obviout too
	matrix operator/(const double); 
	matrix& operator/=(const double);
	matrix T(); // transpose
	matrix inv(); // returns matrix^(-1)
	double det(); // determinant of matrix
	void calc_eigsys(); // calculate eigensystem (eigenvectors and eigenvalues) of matrix
	double* get_eigvec();
	double* get_eigval();
	void print();
private:
	int size;
	double* matrix_elements;
	bool eig_calculated;
	double* eigval; // [1, size]
	double* eigvec; // [size, size]
};
