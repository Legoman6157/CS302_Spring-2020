#include "Gameboard.h"

void Gameboard::read_board() {
	int N_pieces;

	char piece_buff;
	int cost_buff;

	std::cin >> N_pieces;

	for (int i = 0; i < N_pieces; i++) {
		std::cin >> piece_buff >> cost_buff;
		piece_costs.insert(std::pair<char, int>(piece_buff, cost_buff));
	}

	for (auto it : piece_costs)
		std::cout << it.first << ' ' << it.second << std::endl;
}//read_board
