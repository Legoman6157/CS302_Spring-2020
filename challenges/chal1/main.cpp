/*	main.cpp, Joshua Byers
 *	
 *	This program is meant to take in the length of the array, the number of places to
 *		shift the array, the shift direction, and the array itself.
 *
 *	It then shifts the array based on those given criteria.
 *
 */

#include <iostream>
#include <vector>



int main(int argc, char* argv[]) {

	int N = 0;
	int shift;
	char dir;
	int buff;
	std::vector<int> vec;

	//As long as more data can be read in,
		//Read in array size (N)
	while (std::cin >> N) {
		//Read in number of shifts (shift)
		std::cin >> shift;
		//Read in shift direction (dir)
		std::cin >> dir;
		//Read in the array itself on the next line
		for (int i = 0; i < N; i++) {
			std::cin >> buff;
			vec.push_back(buff);
		}//for

		//Ignore everything else on the line
		std::cin.ignore(1000, '\n');

		//Make sure shift is within array size 
		shift %= N;

		//Conceptually, the idea is that if you want to go 2 places right on an array of
		//	size 5, (5-2)=3, making 3 left switches have the same effect. This program will
		//	always switch "left", just change how many times.

		//If direction (dir) is right ('R'),
		if (dir == 'R')
			//Just change how far the switching goes.
			shift = N - shift;

		//This scope is just meant to contain some temporary variables used for location,
		//	number of switches, and a temporary variable for the actual switching.
		{
			//Array location
			int loc = 0;
			//Times array elements have been swapped 
			int num_swaps = 0;
			int temp = vec[(loc + shift) % N];

			//While number of swaps is less than 1 less than the number of elements in the
			//	array, (Swapping the same of elements would just give back the same array)
			while (num_swaps < N-1) {
				//Swap elements @ vec[loc] and vec[loc+shift]
				temp = vec[(loc+shift)%N];
				vec[(loc+shift)%N] = vec[(loc)];
				vec[(loc)] = temp;
				
				//Move to next element position
				loc = (loc+shift)%N;

				//Another swap has been made.
				num_swaps++;

			}//while number of swaps < N-1
		}//Container for loc, times_shifted, and temp.

		//Print out array
		for (int i = 0; i < N; i++)
			std::cout << vec[i] << ' ' << std::flush;
		std::cout << std::endl;

		//Clear out array for next iteration.
		vec.clear();
	}//while

	return 0;
}//main
