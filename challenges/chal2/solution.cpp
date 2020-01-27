#include <algorithm>	//std::sort
#include <cmath>		//std::abs
#include <iostream>	//std::cin, std::cout, std::flush, std::endl
#include <vector>		//std::vector

struct small_thing {
	std::vector< std::vector<int> >::iterator it;
	std::pair<int, int> indices;
	small_thing(std::vector< std::vector<int> >::iterator n_it, std::pair<int, int> n_indices) {
		it = n_it;
		indices = n_indices;
	}//small_thing constructor
};//small_thing

int main(int argc, char* argv[]) {
	std::vector<int> arr;
	std::vector< std::vector<int> > vec_arr;
	int N;
	int buffer;

	while (std::cin >> N) {
		for (int i = 0; i < N && std::cin >> buffer; i++)
			arr.push_back(buffer);
		vec_arr.push_back(arr);
		arr.clear();
	}//While still more stuff to get

	//Had to consult the StackOverflow Council to remember how std::sort worked
	for (std::vector< std::vector<int> >::iterator it = vec_arr.begin(); it != vec_arr.end(); it++)
		std::sort(it->begin(), it->end());


	int smallest_diff = 2147483647;
	std::vector<small_thing> smallest_pairs;
	std::vector< std::vector<small_thing> > smallest_pairs_vec;

	{
		int temp_diff;
		std::vector< std::vector<small_thing> >::iterator small_vec_it;

		for (std::vector< std::vector<int> >::iterator it = vec_arr.begin(); it != vec_arr.end(); it++) {
			for (int i = 0; (i+1) < it->size(); i++) {
				temp_diff = std::abs( (*it)[i+1] - (*it)[i] );
				if (temp_diff < smallest_diff) {
					smallest_diff = temp_diff;
					smallest_pairs.clear();
					smallest_pairs.push_back(small_thing(it, std::pair<int, int>(i, i+1)));
				} else if (temp_diff == smallest_diff)
					smallest_pairs.push_back(small_thing(it, std::pair<int, int>(i, i+1)));
			}//for going through an array of numbers
			smallest_pairs_vec.push_vec
		}//for going through all of the arrays
	}//temp_diff container

}//main
