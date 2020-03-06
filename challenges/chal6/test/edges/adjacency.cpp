
#include <iostream>
#include <sstream>
#include <string>

#include "matrix.h"

int main() {
	Matrix<int> *m;

	std::stringstream ss;
	std::string line_buffer;
	int num_buff;

	int N_elements;

	while (std::cin >> N_elements) {
		std::cout << N_elements << std::endl;
		m = new Matrix<int>(N_elements, N_elements);

		std::cin.ignore();


		for (int i = 0; i < N_elements; i++) {
			std::getline(std::cin, line_buffer);

			ss.clear();
			ss.str(line_buffer);
			for (int j = 0; j < N_elements; j++) {
				ss >> num_buff;
				(*m)[i][j] = num_buff;
			}//for j < N_elements
		}

		for (int i = 0; i < m->N_rows; i++)
			for (int j = 0; j < m->N_cols; j++)
				if ((*m)[i][j] != -1)
					std::cout << (char)('A'+i) << ',' << (char)('A'+j) << ": " << (*m)[i][j] << std::endl;

		delete m;
	}//while (std::cin >> N_elements)
}//main
