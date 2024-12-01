#include "matrix.h"
#include <iostream>

void test_minor(int size, matrix& A)
{
	std::cout << "MINOR TEST:\n";
	matrix result(size-1);
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			std::cout << "i: " << i << " j: " << j << '\n';
			result = A.minor(i, j);
			result.print();
			std::cout << '\n';
		}
	}

}

void det_test(matrix& A)
{
	std::cout << "DETERMINANT TEST:\n";
	A.print();
	std::cout << "\ndet = " << A.det(); 
}

int main()
{
	double a[] = {1, 2, 3,
                4, 5, 6,
                7, 8, 9};

	matrix A(3, a);
	A.print();
	std::cout << std::endl;
	test_minor(3, A);
  double b[] = {1, 0, 0,
                0, 2, 0,
                0, 0, 3};
  A = b;
	det_test(A);
	return 0;
}
