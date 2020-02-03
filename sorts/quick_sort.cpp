#include <deque>
#include <iostream>
#include <vector>

template<typename T>
void swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}//swap

int main() {
/*
*/

	int buff;
	std::vector<int> vec;
	while (std::cin >> buff) {
		vec.push_back(buff);
	}

	int N = vec.size();

	std::cout << vec[0] << ' ' << vec[N/2] << ' ' << vec[N-1] << std::endl;

	if (vec[0] > vec[N/2])
		swap(vec[0], vec[N/2]);

	if (vec[N/2] > vec[N-1])
		swap(vec[N/2], vec[N-1]);

	if (vec[0] > vec[N/2])
		swap(vec[0], vec[N/2]);

	std::cout << vec[0] << ' ' << vec[N/2] << ' ' << vec[N-1] << std::endl;

	
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << ' ' << std::flush;
	std::cout << std::endl;

	return 0;
}//main
