#include <fstream>
#include <iostream>

int main() {
	std::ifstream i_f("temp.txt");
	int buff;
	i_f >> buff;
	std::cout << buff << std::endl;
}//main
