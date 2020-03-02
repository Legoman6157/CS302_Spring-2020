#include <iostream>
#include <map>
#include <vector>

int main(int argc, char* argv[]) {
	std::vector<std::string> vec_vec;

	int N_rows;
	std::string line_buffer;

/*
	while (std::cin >> N_rows)
		for (int i = 0; i < N_rows; i++) {
			std::getline(std::cin, line_buffer);
			vec_vec.push_back(line_buffer);
		}
*/
	while (std::getline(std::cin, line_buffer))
		vec_vec.push_back(line_buffer);

	for (int i = 0; i < vec_vec.size(); i++)
		std::cout << vec_vec[i] << std::endl;
}//main
