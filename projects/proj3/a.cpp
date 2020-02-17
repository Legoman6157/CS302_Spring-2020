#include <iostream>

int main() {
	int arr[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9
	};
	int N = sizeof(arr)/sizeof(int);

	for (int i = 0; i < N; i++)
		std::cout << arr[i] << std::endl;
}
