#include <iostream>
#include <climits>

int main(int argc, char* argv[]) {
	std::string buff;
	std::cout << "Hello,World!";
	std::cin.clear();
	std::cin.ignore(INT_MAX);
	std::cin >> buff;
	std::cout << buff << std::endl;

	return 0;
}//main
