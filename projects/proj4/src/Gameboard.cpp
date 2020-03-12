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

	std::cin >> N_rows >> N_cols;

	board.resize(N_rows, N_cols);
	visited.resize(N_rows, N_cols);

	//Read in board to internal matrix (board)
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

direction Gameboard::get_direction(pixel loc) {

	bool N_valid = loc.x > 0,
		  E_valid = loc.y < N_cols - 1,
		  W_valid = loc.y > 0,
		  S_valid = loc.x < N_rows - 1;

	int current_smallest = 0;
		  
	direction next_direction = Z;

	std::cout << "\t\tPrinting moves: " << std::endl;
	std::cout << "\t\tN: " << N_valid << std::endl;
	std::cout << "\t\tE: " << E_valid << std::endl;
	std::cout << "\t\tW: " << W_valid << std::endl;
	std::cout << "\t\tS: " << S_valid << std::endl;

	pixel N_pixel(loc.x-1, loc.y),
			E_pixel(loc.x, loc.y+1),
			W_pixel(loc.x, loc.y-1),
			S_pixel(loc.x+1, loc.y);

	if (N_valid && (!visited[N_pixel.x][N_pixel.y])) {
		visited[N_pixel.y][N_pixel.y] = true;
		current_smallest = piece_costs[ board[N_pixel.x][N_pixel.y] ];
		next_direction = N;
	}

	if (E_valid
		 &&
		 ((!visited[E_pixel.x][E_pixel.y])
			&&
			((piece_costs[ board[E_pixel.x][E_pixel.y] ] < current_smallest)
			  ||
			  (next_direction == Z)
			)
		)) {
		visited[E_pixel.x][E_pixel.y] = true;
		current_smallest = piece_costs[ board[E_pixel.x][E_pixel.y] ];
		next_direction = E;
	}

	if (W_valid
		&& (
			(!visited[W_pixel.x][W_pixel.y])
			&& ( 
				(piece_costs[ board[W_pixel.x][W_pixel.y] ] < current_smallest)
				||
				(next_direction == Z)
			)
		) 
		) {
		visited[W_pixel.x][W_pixel.y] = true;
		current_smallest = piece_costs[ board[W_pixel.x][W_pixel.y] ];
		next_direction = W;
	}

	if (S_valid
		&& (
			(!visited[S_pixel.x][S_pixel.y])
			&& ( 
				(piece_costs[ board[S_pixel.x][S_pixel.y] ] < current_smallest)
				||
				(next_direction == Z)
			)
		) 
		) {
		visited[S_pixel.x][S_pixel.y] = true;
		current_smallest = piece_costs[ board[S_pixel.x][S_pixel.y] ];
		next_direction = S;
	}

	std::cout << current_smallest << std::endl;
	if (next_direction == N) std::cout << 'N' << std::endl;
	else if (next_direction == E) std::cout << 'E' << std::endl;
	else if (next_direction == W) std::cout << 'W' << std::endl;
	else if (next_direction == S) std::cout << 'S' << std::endl;
	else if (next_direction == Z) std::cout << 'Z' << std::endl;

	return next_direction;
}//get_direction(Gameboard& gb, pixel loc)

std::vector<pixel> Gameboard::find_dijkstra_path() {
	std::vector<pixel> d_path;

	pixel curr_pixel = source;
	d_path.push_back(curr_pixel);

	char curr_piece;	

	while ((!d_path.empty()) && (curr_pixel != sink)) {
		curr_piece = board[curr_pixel.x][curr_pixel.y];

		std::cout << "Current pixel: " << curr_pixel.x << ' ' << curr_pixel.y << std::endl;
		std::cout << "\tCurrent cost and path: " << curr_pixel.x << ' ' << curr_pixel.y << std::endl;
		std::cout << '\t' << total_cost << std::endl;
		for (auto it : d_path)
			std::cout << '\t' << it.x << ' ' << it.y << std::endl;

		switch (get_direction(curr_pixel)) {
			case N:
				curr_pixel.x -= 1;
				d_path.push_back(curr_pixel);
				total_cost = piece_costs[curr_piece];
				break;
			case E:
				curr_pixel.y += 1;
				d_path.push_back(curr_pixel);
				total_cost = piece_costs[curr_piece];
				break;
			case W:
				curr_pixel.y -= 1;
				d_path.push_back(curr_pixel);
				total_cost = piece_costs[curr_piece];
				break;
			case S:
				curr_pixel.x += 1;
				d_path.push_back(curr_pixel);
				total_cost = piece_costs[curr_piece];
				break;

			case Z:
			default:
				total_cost -= piece_costs[curr_piece];
				d_path.pop_back();
				curr_pixel = d_path.back();
		}
		std::cout << "\tCurrent state of loop condition: " << ((!d_path.empty()) && (curr_pixel != sink)) << '\n' << std::endl;
		std::cout << "\t\tnot empty: " << (!d_path.empty()) << std::endl;
		std::cout << "\t\tnot at sink: " << (curr_pixel != sink) << std::endl;
		std::cout << "\t\t\tcurrent pixel: " << curr_pixel.x << ' ' << curr_pixel.y << std::endl;
		std::cout << "\t\t\tsink: " << sink.x << ' ' << sink.y << std::endl;
	}//while not empty and not sink

	std::cout << total_cost << std::endl;
	for (auto it : d_path)
		std::cout << it.x << ' ' << it.y << std::endl;

	return d_path;
}
