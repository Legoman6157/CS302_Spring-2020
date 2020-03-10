#include "Gameboard.h"

//Gameboard
void Gameboard::read_board() {
	int N_pieces;

	std::stringstream ss;
	char char_buff;

	char piece_buff;
	int cost_buff;

	//Get how many pieces there are
	std::cin >> N_pieces;

	//Get list of pieces and their respective costs
	for (int i = 0; i < N_pieces; i++) {
		std::cin >> piece_buff >> cost_buff;
		piece_costs.insert(std::pair<char, int>(piece_buff, cost_buff));
	}//for (i < N_pieces)

	//Get board size and set matrix to that size
	std::cin >> N_rows >> N_cols;
	board.resize(N_rows, N_cols);

	//Get actual board data
	for (int i = 0; i < N_rows; i++) {
		for (int j = 0; j < N_cols; j++) {
			std::cin >> char_buff;
			board[i][j] = char_buff;
		}// for (j < N_cols)
	}//for (i < N_rows)

	//Get source and sink
	std::cin >> source.x >> source.y;
	std::cin >> sink.x >> sink.y;

}//Gameboard::read_board()

int Gameboard::get_cost(char piece) {
	return piece_costs[piece];
}//Gameboard::get_cost(char piece)
