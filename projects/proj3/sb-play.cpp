#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

#include "disjoint.h"

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

struct pixel {
	int x,
		 y;

	pixel() {};
	pixel(int n_x, int n_y): x(n_x), y(n_y) {};
};

struct dset {
	std::vector<pixel> pixels;
	char piece;
	int score;
};//dset

class Superball {
	public:
		Superball(int argc, char **argv);
		int r;
		int c;
		int mss;
		int empty;
		vector <int> board;
		vector <int> goals;
		vector <int> colors;
};

void usage(const char *s) 
{
	fprintf(stderr, "usage: sb-read rows cols min-score-size colors\n");
	if (s != NULL) fprintf(stderr, "%s\n", s);
	exit(1);
}

Superball::Superball(int argc, char **argv)
{
	int i, j;
	string s;

	if (argc != 5) usage(NULL);

	if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
	if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
	if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");

	colors.resize(256, 0);

	for (i = 0; i < strlen(argv[4]); i++) {

		if (colors[argv[4][i]] != 0) usage("Duplicate color");
		colors[argv[4][i]] = 2+i;
		colors[toupper(argv[4][i])] = 2+i;
	}

	board.resize(r*c);
	goals.resize(r*c, 0);

	empty = 0;

	for (i = 0; i < r; i++) {
		if (!(cin >> s)) {
			fprintf(stderr, "Bad board: not enough rows on standard input\n");
			exit(1);
		}
		if (s.size() != c) {
			fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
			exit(1);
		}
		for (j = 0; j < c; j++) {
			if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0) {
				fprintf(stderr, "Bad board row %d - bad character %c.\n", i, s[j]);
				exit(1);
			}
			board[i*c+j] = s[j];
			if (board[i*c+j] == '.') empty++;
			if (board[i*c+j] == '*') empty++;
			if (isupper(board[i*c+j]) || board[i*c+j] == '*') {
				goals[i*c+j] = 1;
				board[i*c+j] = tolower(board[i*c+j]);
			}
		}
	}
}

std::vector<pixel> sb_read(int argc, char **argv, Superball *s)
{
	std::vector<pixel> pieces;

	int i, j;

	//Number of goal pieces and total score of all goal pieces
	int ngoal, tgoal;
 
	tgoal = 0;
	ngoal = 0;

	//For all pixels in board,
	for (i = 0; i < s->r*s->c; i++) {
		//If it's a goal piece and it's not an empty space,
		if (s->goals[i] && s->board[i] != '*') {

			//Push it to the vector containing goal pieces.
			pieces.push_back(pixel(i/s->c, i%s->c));

			//Add score of piece to total score sum
			tgoal += s->colors[s->board[i]];

			//Incerement number of goal pieces
			ngoal++;

		}//if (s->goals[i] && s->board[i] != '*')
	}//for (i < s->r*s->c)

	return pieces;
}

std::vector<dset> sb_analyze(int argc, char* argv[], Superball *s) {
	DisjointSetByRankWPC ds(s->r*s->c);

	std::vector<pixel> goal_pieces = sb_read(argc, argv, s);

	//Vector of disjoint sets to return
	std::vector<dset> dsets;

	//Stack for dfs traversal of the board
	std::stack<pixel> dfs_stack;

	//Pixel for traversal and 
	pixel curr_pixel,
			temp_pixel;

	//Buffer dset for putting into dsets vector
	dset temp_dset;

	int curr_pixel_loc,
		 north_loc,
		 east_loc,
		 west_loc,
		 south_loc;

	for (int i = 0; i < goal_pieces.size(); i++) {
		dfs_stack.push(goal_pieces[i]);

		temp_dset.pixels.clear();
		temp_dset.pixels.push_back(goal_pieces[i]);

		temp_dset.piece = s->board[(goal_pieces[i].x) * s->c + (goal_pieces[i].y)];

		while (!dfs_stack.empty()) {
			curr_pixel = dfs_stack.top();
			dfs_stack.pop();

			//Set location of current pixel and possible "movements" for traversal
			curr_pixel_loc = (curr_pixel.x) * s->c + (curr_pixel.y);
			north_loc = (curr_pixel.x-1) * s->c + (curr_pixel.y);
			east_loc = (curr_pixel.x) * s->c + (curr_pixel.y+1);
			west_loc = (curr_pixel.x) * s->c + (curr_pixel.y-1);
			south_loc = (curr_pixel.x+1) * s->c + (curr_pixel.y);

			//(N) Check North
			if ( (curr_pixel.x > 0)
					&& (ds.Find(north_loc) != ds.Find(curr_pixel_loc))
					&& (s->board[north_loc] == s->board[curr_pixel_loc]) ) {

				ds.Union(ds.Find(north_loc), ds.Find(curr_pixel_loc));

				temp_pixel.x = north_loc/s->c;
				temp_pixel.y = north_loc%s->c;

				dfs_stack.push(pixel(temp_pixel));
				temp_dset.pixels.push_back(temp_pixel);
			}

			//(E) Check East
			if ( (curr_pixel.y < s->c-1)
					&& (ds.Find(east_loc) != ds.Find(curr_pixel_loc))
					&& (s->board[east_loc] == s->board[curr_pixel_loc]) ) {

				ds.Union(ds.Find(east_loc), ds.Find(curr_pixel_loc));

				temp_pixel.x = east_loc/s->c;
				temp_pixel.y = east_loc%s->c;

				dfs_stack.push(pixel(temp_pixel));
				temp_dset.pixels.push_back(temp_pixel);
			}

			//(W) Check Weast
			if ( (curr_pixel.y > 0)
					&& (ds.Find(west_loc) != ds.Find(curr_pixel_loc))
					&& (s->board[west_loc] == s->board[curr_pixel_loc]) ) {

				ds.Union(ds.Find(west_loc), ds.Find(curr_pixel_loc));

				temp_pixel.x = west_loc/s->c;
				temp_pixel.y = west_loc%s->c;

				dfs_stack.push(pixel(temp_pixel));
				temp_dset.pixels.push_back(temp_pixel);
			}

			//(S) Check South
			if ( (curr_pixel.x < s->r-1)
					&& (ds.Find(south_loc) != ds.Find(curr_pixel_loc))
					&& (s->board[south_loc] == s->board[curr_pixel_loc]) ) {

				ds.Union(ds.Find(south_loc), ds.Find(curr_pixel_loc));

				temp_pixel.x = south_loc/s->c;
				temp_pixel.y = south_loc%s->c;

				dfs_stack.push(pixel(temp_pixel));
				temp_dset.pixels.push_back(temp_pixel);
			}
		}//while (!dfs_stack.empty())

		curr_pixel_loc = (temp_dset.pixels[0].x) * s->c + (temp_dset.pixels[0].y);

		if (curr_pixel_loc == ds.Find(curr_pixel_loc) ) {
			temp_dset.score = s->colors[temp_dset.piece] * temp_dset.pixels.size();
			dsets.push_back(temp_dset);
		}

	}//for (i < goal_pieces.size())


	return dsets;
}//find_dsets(read_data rd)


bool operator<(dset a, dset b) {
	return a.pixels.size() < b.pixels.size();
}


std::vector<pixel> get_adjacent_pieces(dset main, Superball *s) {
	bool visited[s->r*s->c] = {false};

	std::vector<pixel> adjacents;

	pixel curr_pixel,
			temp_pixel;
	
	int curr_pixel_loc,
		 north_loc,
		 east_loc,
		 west_loc,
		 south_loc;


	while (!main.pixels.empty()) {
		curr_pixel = main.pixels.back();
		main.pixels.pop_back();

		//Set location of current pixel and possible "movements" for traversal
		curr_pixel_loc = (curr_pixel.x) * s->c + (curr_pixel.y);
		north_loc = (curr_pixel.x-1) * s->c + (curr_pixel.y);
		east_loc = (curr_pixel.x) * s->c + (curr_pixel.y+1);
		west_loc = (curr_pixel.x) * s->c + (curr_pixel.y-1);
		south_loc = (curr_pixel.x+1) * s->c + (curr_pixel.y);

		//(N) Check North
		if ( (curr_pixel.x > 0)
				&& (s->board[north_loc] != main.piece)
				&& (s->board[north_loc] != '.')
				&& (s->board[north_loc] != '*')
				&& (!(visited[north_loc])) ) {
			visited[north_loc] = true;
			adjacents.push_back(pixel(north_loc/s->c, north_loc%s->c)); 
		}

		//(E) Check East
		if ( (curr_pixel.y < s->c-1)
				&& (s->board[east_loc] != main.piece)
				&& (s->board[east_loc] != '.')
				&& (s->board[east_loc] != '*')
				&& (!(visited[east_loc])) ) {
			visited[east_loc] = true;
			adjacents.push_back(pixel(east_loc/s->c, east_loc%s->c));
		}

		//(W) Check West
		if ( (curr_pixel.y > 0)
				&& (s->board[west_loc] != main.piece)
				&& (s->board[west_loc] != '.')
				&& (s->board[west_loc] != '*')
				&& (!(visited[west_loc])) ) {
			visited[west_loc] = true;
			adjacents.push_back(pixel(west_loc/s->c, west_loc%s->c));
		}

		//(S) Check South
		if ( (curr_pixel.x < s->r-1)
				&& (s->board[south_loc] != main.piece)
				&& (s->board[south_loc] != '.')
				&& (s->board[south_loc] != '*')
				&& (!(visited[south_loc])) ) {
			visited[south_loc] = true;
			adjacents.push_back(pixel(south_loc/s->c, south_loc%s->c));
		}
	}//while (!main.pixels.empty())

	return adjacents;
}//get_adjacent_pieces(dset main, Superball *s)

dset get_biggest_dset(std::vector<dset> dsets) {
	dset biggest = dsets[0];
	for (auto it : dsets)
		if (biggest.pixels.size() < it.pixels.size())
			biggest = it;
	return biggest;
}

dset get_best_dset(std::vector<dset> dsets, Superball *s) {

	std::sort(dsets.begin(), dsets.end());

	dset temp = dsets[dsets.size()-1];

	if (get_adjacent_pieces(temp, s).size() == 0)
		for (int i = dsets.size()-2; i > 0; i--)
			if (get_adjacent_pieces(dsets[i], s).size() > 0) {
				temp = dsets[i];
				break;
			}

	return temp;

}

pixel get_swap_piece(dset main, Superball *s) {

	bool dset_piece[s->r*s->c] = {0};

	for (auto it : main.pixels)
		dset_piece[it.x * s->c + it.y] = true;

	for (int i = 0; i < s->r*s->c; i++) {
		if (!dset_piece[i]
			 && s->board[i] == main.piece)
			return pixel(i/s->c, i%s->c);
	}
	
	return pixel(-1, 0);
}

pixel get_random_piece(pixel match, Superball *s) {
	for (int i = 0; i < s->r*s->c; i++)
		if ( (s->board[i] != '.')
			  && (s->board[i] != '*')
			  && (i != match.x * s->c + match.y) )
			return pixel(i/s->c, i%s->c);
}

void swap(pixel a, pixel b) {
	std::printf("SWAP %d %d %d %d\n", a.x, a.y, b.x, b.y);
}//swap(pixel a, pixel b)

void score(pixel a) {
	std::printf("SCORE %d %d\n", a.x, a.y);
}//score(pixel a)


void swap_random_pieces(Superball *s) {

	pixel a(-1, 0), b;

	for (int i = 0; i < s->r*s->c; i++)
		if ((s->board[i] != '.') && (s->board[i] != '*')
			 && (i/s->c != a.x) && (i%s->c != a.y))
			if (a.x == -1) {
				a.x = i/s->c;
				a.y = i%s->c;
			} else {
				b.x = i/s->c;
				b.y = i%s->c;
			}
	swap(a, b);
}

int main(int argc, char **argv)
{
	Superball *s;

	s = new Superball(argc, argv);

	//This gets all disjoint sets with a goal piece, which is at 0 of their pixels.
	std::vector<dset> dsets = sb_analyze(argc, argv, s);

	if (dsets.size() == 0) {
		swap_random_pieces(s);
	} else {

		if (s->empty < 20) {
			score(get_biggest_dset(dsets).pixels[0]);
		} else {
			dset best_dset = get_best_dset(dsets, s);
			std::vector<pixel> adjacent_pieces = get_adjacent_pieces(best_dset, s);

			if (adjacent_pieces.size() == 0) {
				swap_random_pieces(s);
			} else {

				pixel adjacent_piece = adjacent_pieces[0],
						swap_piece = get_swap_piece(best_dset, s);
				
				if (swap_piece.x == -1) {
					swap_piece = get_random_piece(adjacent_piece, s);
				}

				swap(adjacent_piece, swap_piece);

			}// if (get_adjacent_pieces(best_dset, s).size() == 0) / else
		}//if (s->empty < 20)

	}//if (dsets.size() == 0) / else

	delete s;

	return 0;
}//main
