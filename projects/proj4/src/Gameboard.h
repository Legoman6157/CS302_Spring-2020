#include <iostream>	//std::cin
#include <map>			//std::map
#include <sstream>	//std::stringstream
#include <vector>		//std::vector
#include <stack>		//std::stack

#include "matrix.h"	//Gameboard

enum direction {N, E, W, S, Z};

struct pixel {
	int x, y;

	pixel() {};
	pixel(int n_x, int n_y): x(n_x), y(n_y) {};
	bool operator==(pixel &p) {
		return (x == p.x) && (y == p.y);
	}
};//struct pixel

class Gameboard {
	private:
		int N_rows, N_cols;
		std::map<char, int> piece_costs;
		Matrix<char> board;
		Matrix<bool> visited;
		direction get_direction(pixel loc);

	public:
		pixel source,
				sink;

		int total_cost;

		Gameboard(): total_cost(0) {};
		~Gameboard() {};

		char* operator[](int x) { return board[x]; }

		void read_board();
		std::vector<pixel> find_dijkstra_path();

		const int get_N_rows() const { return N_rows; };
		const int get_N_cols() const { return N_cols; };
};//class Gameboard
