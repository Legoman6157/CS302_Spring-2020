#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <stack>
#include <vector>

#include "disjoint.h"

using namespace std;

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

struct pixel {
	int x,
		 y;
	
	pixel() {};
	pixel(int n_x, int n_y): x(n_x), y(n_y) {};
};//pixel

struct dset {
	char piece;
	std::vector<pixel> pixels;
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

std::vector<pixel> sb_read(Superball *s)
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
		if ((s->board[i] != '.') && (s->board[i] != '*')) {

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

std::vector<dset> sb_analyze(Superball *s) {
	DisjointSetByRankWPC ds(s->r*s->c);

	//List of all goal pieces
	std::vector<pixel> goal_pieces = sb_read(s);

	//Vector of disjoint sets to return
	std::vector<dset> dsets;

	//Stack for dfs traversal of the board
	std::stack<pixel> dfs_stack;

	//Pixel for traversal and 
	pixel curr_pixel,
			temp_pixel;

	//Buffer dset for putting into dsets vector
	dset temp_dset;

	//Variables for the current cell and its neighbors
	int curr_pixel_loc,
		 north_loc,
		 east_loc,
		 west_loc,
		 south_loc;

	//For all goal pieces,
	for (int i = 0; i < goal_pieces.size(); i++) {
		dfs_stack.push(goal_pieces[i]);

		//Free the temporary disjoint set's array of pixels and push the front pixel
		//	of the list of goal pieces
		temp_dset.pixels.clear();
		temp_dset.pixels.push_back(goal_pieces[i]);

		//Setting the disjoint set's piece (colour)
		temp_dset.piece = s->board[(goal_pieces[i].x) * s->c + (goal_pieces[i].y)];

		//While there's still pixels on the stack,
		while (!dfs_stack.empty()) {
			curr_pixel = dfs_stack.top();
			dfs_stack.pop();

			//Set location of current pixel it neighbors
			//Set location of current pixel and possible "movements" for traversal
			curr_pixel_loc = (curr_pixel.x) * s->c + (curr_pixel.y);
			north_loc = (curr_pixel.x-1) * s->c + (curr_pixel.y);
			east_loc = (curr_pixel.x) * s->c + (curr_pixel.y+1);
			west_loc = (curr_pixel.x) * s->c + (curr_pixel.y-1);
			south_loc = (curr_pixel.x+1) * s->c + (curr_pixel.y);

			//(N) Check North
			//If the current pixel is below the top row,
			//	and the north and current pixels have different parents
			//	and the north and current piece match,
			if ( (curr_pixel.x > 0)
					&& (ds.Find(north_loc) != ds.Find(curr_pixel_loc))
					&& (s->board[north_loc] == s->board[curr_pixel_loc]) ) {

				//Match them
				ds.Union(ds.Find(north_loc), ds.Find(curr_pixel_loc));

				//Set the temporary pixel's x and y to north's
				temp_pixel.x = north_loc/s->c;
				temp_pixel.y = north_loc%s->c;

				dfs_stack.push(temp_pixel);
				dfs_stack.push(pixel(temp_pixel));
				temp_dset.pixels.push_back(temp_pixel);
			}

			//(E) Check East
			//If the current pixel is below the top row,
			//	and the east and current pixels have different parents
			//	and the east and current piece match,
			if ( (curr_pixel.y < s->c-1)
					&& (ds.Find(east_loc) != ds.Find(curr_pixel_loc))
					&& (s->board[east_loc] == s->board[curr_pixel_loc]) ) {

				//Match them
				ds.Union(ds.Find(east_loc), ds.Find(curr_pixel_loc));

				//Set the temporary pixel's x and y to east's
				temp_pixel.x = east_loc/s->c;
				temp_pixel.y = east_loc%s->c;

				dfs_stack.push(temp_pixel);
				dfs_stack.push(pixel(temp_pixel));
				temp_dset.pixels.push_back(temp_pixel);
			}

			//(W) Check West
			//If the current pixel is below the top row,
			//	and the west and current pixels have different parents
			//	and the west and current piece match,
			if ( (curr_pixel.y > 0)
					&& (ds.Find(west_loc) != ds.Find(curr_pixel_loc))
					&& (s->board[west_loc] == s->board[curr_pixel_loc]) ) {

				//Match them
				ds.Union(ds.Find(west_loc), ds.Find(curr_pixel_loc));

				//Set the temporary pixel's x and y to west's
				temp_pixel.x = west_loc/s->c;
				temp_pixel.y = west_loc%s->c;

				dfs_stack.push(temp_pixel);
				dfs_stack.push(pixel(temp_pixel));
				temp_dset.pixels.push_back(temp_pixel);
			}

			//(S) Check South
			//If the current pixel is below the top row,
			//	and the south and current pixels have different parents
			//	and the south and current piece match,
			if ( (curr_pixel.x < s->r-1)
					&& (ds.Find(south_loc) != ds.Find(curr_pixel_loc))
					&& (s->board[south_loc] == s->board[curr_pixel_loc]) ) {

				//Match them
				ds.Union(ds.Find(south_loc), ds.Find(curr_pixel_loc));

				//Set the temporary pixel's x and y to south's
				temp_pixel.x = south_loc/s->c;
				temp_pixel.y = south_loc%s->c;

				dfs_stack.push(temp_pixel);
				dfs_stack.push(pixel(temp_pixel));
				temp_dset.pixels.push_back(temp_pixel);
			}

		}//while (!dfs_stack.empty())

		curr_pixel_loc = (temp_dset.pixels[0].x) * s->c + (temp_dset.pixels[0].y);

		//This little section is to make sure I don't push a size 1 dset with a goal piece that's
		//	in another dset.
		int temp_pixel_loc = (temp_dset.pixels[0].x) * s->c + (temp_dset.pixels[0].y);
		if (curr_pixel_loc == ds.Find(curr_pixel_loc) && temp_dset.pixels.size() >= 2) {
			temp_dset.score = s->colors[temp_dset.piece] * temp_dset.pixels.size();
			dsets.push_back(temp_dset);
		}

	}//for (i < goal_pieces.size())


	return dsets;
}//find_dsets(read_data rd)


int main(int argc, char* argv[]) {

	Superball *s;

	s = new Superball(argc, argv);

	std::vector<dset> goal_pieces = sb_analyze(s);	

	std::printf("Scoring sets:\n");
	for (int i = 0; i < goal_pieces.size(); i++) {
		std::printf("  Size: %2d  Char: %2c  Scoring Cell: %d,%d\n",
			goal_pieces[i].pixels.size(),
			goal_pieces[i].piece,
			goal_pieces[i].pixels[0].x,
			goal_pieces[i].pixels[0].y
		);
	}//for (i < goal_pieces.size())

	return 0;
}
