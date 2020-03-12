#include "Gameboard.cpp"

int main() {
	Gameboard gb;
	gb.read_board();

	gb.find_dijkstra_path();
}
