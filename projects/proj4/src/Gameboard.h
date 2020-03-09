#include <iostream>	//std::cin
#include <map>			//std::map
#include <sstream>	//std::stringstream
#include <vector>		//std::vector

#include "matrix.h"	//Gameboard

struct pixel {
	int x, y;

	pixel() {};
	pixel(int n_x, int n_y): x(n_x), y(n_y) {};
};//struct pixel

class Gameboard {
	private:
		int N_rows, N_cols;
		std::map<char, int> piece_costs;
		Matrix<char> board;
		pixel source,
				sink;
	public:
		void read_board();
		std::vector<pixel> get_shortest_path();
		char* operator[](int x) { return board[x]; }
};//class Gameboard
