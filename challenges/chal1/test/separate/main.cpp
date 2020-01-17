#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
	int N = 0;
	int shift;
	char dir;
	char c;
	std::vector<char> vec;
	while (std::cin >> N) {
		std::cin >> shift;
		std::cin >> dir;
		for (int i = 0; i < N; i++) {
			std::cin >> c;
			vec.push_back(c);
		}//for

		std::cout << "Size=" << N
			<< "\nshift=" << shift
			<< "\ndirection=" << dir
			<< std::endl;
		for (int i = 0; i < vec.size(); i++)
			std::cout << vec[i];
	}//while
	return 0;
}//main
