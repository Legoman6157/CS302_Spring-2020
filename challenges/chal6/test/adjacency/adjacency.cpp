#include <iostream>
#include <sstream>
#include <string>

#include "matrix.h"

int main() {
	Matrix m;

	std::stringstream ss;
	std::string line_buffer;
	int num_buff;

	int N_elements;

	while (std::cin >> N_elements) {

		m.resize(N_elements, N_elements);

		for (int i = 0; i < N_elements; i++) {
			std::getline(std::cin, line_buffer);
			ss.str(line_buffer);
			for (int j = 0; j < N_elements; j++) {
				ss >> num_buff;
				m[i][j] = num_buff;
			}//for j < N_elements
		}
	}//while (std::cin >> N_elements)
}//main
