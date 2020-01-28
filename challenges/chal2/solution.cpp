#include <algorithm>	//std::sort
#include <cmath>		//std::abs
#include <iostream>	//std::cin, std::cout, std::flush, std::endl
#include <vector>		//std::vector

struct small_thing {
	std::pair<int, int> indices;
	small_thing(std::pair<int, int> n_indices) {
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


	std::vector<small_thing> smallest_pairs;
	std::vector< std::vector<small_thing> > smallest_pairs_vec;

	{
		int temp_diff;
		int smallest;
		std::vector< std::vector<small_thing> >::iterator small_vec_it;

		for (std::vector< std::vector<int> >::iterator it = vec_arr.begin(); it != vec_arr.end(); it++) {
			smallest = (*it)[1] - (*it)[0];
			smallest_pairs.push_back(small_thing(std::pair<int, int>((*it)[0], (*it)[1])));

			for (int i = 1; (i+1) < it->size(); i++) {

				temp_diff = std::abs( (*it)[i+1] - (*it)[i] );

				if (temp_diff < smallest) {
					smallest = temp_diff;
					smallest_pairs.clear();
					smallest_pairs.push_back(small_thing(std::pair<int, int>((*it)[i], (*it)[i+1])));
				} else if (temp_diff == smallest)
					smallest_pairs.push_back(small_thing(std::pair<int, int>((*it)[i], (*it)[i+1])));

			}//for going through an array of numbers
			smallest_pairs_vec.push_back(smallest_pairs);
			smallest_pairs.clear();
		}//for going through all of the arrays
	}//temp_diff container

	N = vec_arr.size();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < smallest_pairs_vec[i].size(); j++) {
			int first = smallest_pairs_vec[i][j].indices.first,
				 second = smallest_pairs_vec[i][j].indices.second;

			std::cout << first << ' ' << second << std::endl;
		}
	}

}//main
