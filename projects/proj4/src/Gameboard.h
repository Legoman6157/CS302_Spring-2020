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
		char* operator[](int x) { return board[x]; }

		void read_board();
		int get_cost(char piece);

		const int get_N_rows() const { return N_rows; };
		const int get_N_cols() const { return N_cols; };
};//class Gameboard
