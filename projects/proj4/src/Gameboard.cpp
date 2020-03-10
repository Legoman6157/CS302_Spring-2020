#include "Gameboard.h"

void Gameboard::read_board() {
	int N_pieces;

	std::stringstream ss;
	std::string line_buff;
	char char_buff;

	char piece_buff;
	int cost_buff;

	std::cin >> N_pieces;

	for (int i = 0; i < N_pieces; i++) {
		std::cin >> piece_buff >> cost_buff;
		piece_costs.insert(std::pair<char, int>(piece_buff, cost_buff));
	}

	std::cin >> N_rows >> N_cols;
	board.resize(N_rows, N_cols);

	for (int i = 0; i < N_rows; i++) {
		for (int j = 0; j < N_cols; j++) {
			std::cin >> char_buff;
			board[i][j] = char_buff;
		}// for (j < N_cols)
	}//for (i < N_rows)

	std::cout << "Printing board:" << std::endl;
	for (int i = 0; i < N_rows; i++) {
		for (int j = 0; j < N_cols; j++)
			std::cout << board[i][j];
		std::cout << std::endl;
	}
}//read_board
