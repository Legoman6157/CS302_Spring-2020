#include "Gameboard.cpp"

enum direction {N, E, W, S, Z};

direction get_direction(Gameboard& gb, pixel loc) {
	bool N_valid = loc.x > 0,
		  E_valid = loc.y < gb.get_N_cols() - 1,
		  W_valid = loc.y > 0,
		  S_valid = loc.x < gb.get_N_rows() - 1;

	int smallest_cost = 0;
		  
	direction next_direction = Z;

	std::cout << "N: " << N_valid << std::endl;
	std::cout << "E: " << E_valid << std::endl;
	std::cout << "W: " << W_valid << std::endl;
	std::cout << "S: " << S_valid << std::endl;
}//get_direction(Gameboard& gb, pixel loc)

int main() {
	Gameboard gb;
	gb.read_board();

	int r = gb.get_N_rows();
	int c = gb.get_N_cols();

	pixel curr_pixel = gb.source;
}
