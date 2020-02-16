#include <iostream>
#include <vector>

int main() {
	std::vector<int> vec;
	int buff;

	while (std::cin >> buff)
		vec.push_back(buff);
	
	for (auto it : vec)
		std::cout << '-' << it << std::endl;
}
