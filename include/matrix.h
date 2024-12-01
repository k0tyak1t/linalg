#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

class matrix
{
public:
	matrix(); // default constructor
	matrix(int); // constructor with specified size
	matrix(int, double*); // constructor with specified elements
	matrix(const matrix&); // constructor with source matrix
	~matrix(); // destructor
	double* operator[](int); // row setter
	const double* operator[](int) const; // row getter
	matrix& operator=(const matrix&); // assignement
  matrix& operator=(const double*); // reassign elements
	matrix operator+(const matrix&); // sum of matrices
	matrix operator+(const double); // + const * identity
	matrix& operator+=(const matrix&); // add matrix and assign
	matrix& operator+=(const double);
	matrix operator-();
	matrix operator-(const matrix&); // substract matrices
	matrix operator-(const double); // - const * identity
	matrix& operator-=(const matrix&); // substract and assign
	matrix& operator-=(const double); // substract scalar and assign
	matrix operator*(const double); // multiply by number
	matrix operator*(const matrix&); // matrix product
	matrix& operator*=(const matrix&); // obvious
	matrix& operator*=(const double); // obviout too
	matrix operator/(const double); // divide by scalar
	matrix& operator/=(const double); // dibide by scallar and assign
	matrix T(); // transpose
	matrix inv(); // returns matrix^(-1)
	matrix minor(int, int); // get minor matrix of element i, j
	double det(); // determinant of matrix
	void calc_eigsys(); // calculate eigensystem (eigenvectors and eigenvalues) of matrix
	double* get_eigvec(); // get eigenvectors
	double* get_eigval(); // get eigenvalues
	void print(); // print matrix to stdout
private:
	int size;
	double* matrix_elements;
	bool eig_calculated;
	double* eigval;
	double* eigvec;
};

#endif
