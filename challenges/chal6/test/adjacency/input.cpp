#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main(int argc, char* argv[]) {
	std::vector<int> vec_vec;

	int N_rows,
		 buffer;
	std::string line_buffer;
	std::stringstream ss;


	while (std::cin >> N_rows) {
		std::cout << "New set of rows of size " << N_rows << std::endl;
		std::cin.ignore();
		for (int i = 0; i < N_rows; i++) {
			std::cout << "Getting row " << i << std::endl;

			//Store new line in line_buffer
			std::getline(std::cin, line_buffer);

			std::cout << "\tNew row: " << line_buffer << std::endl;

			ss.clear();
			ss.str(line_buffer);

			while (ss >> buffer) {
				vec_vec.push_back(buffer);
			}
		}
	}

	for (int i = 0; i < vec_vec.size(); i++)
		std::cout << vec_vec[i] << std::endl;
}//main
