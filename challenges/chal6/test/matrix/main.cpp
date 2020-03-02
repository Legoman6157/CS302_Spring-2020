#include <iostream>

#include "matrix.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " [rows] [col.'s]" << std::endl;
		return 1;
	}

	int r = *(argv[1])-'0', c = *(argv[2])-'0';

	Matrix<int> matrix(r, c);

	for (int i = 0; i < matrix.N_rows; i++)
		for (int j = 0; j < matrix.N_cols; j++)
			matrix[i][j] = i*matrix.N_cols+j;


	for (int i = 0; i < matrix.N_rows; i++)
		for (int j = 0; j < matrix.N_cols; j++)
			std::cout << matrix[i][j] << std::endl;
}//main
