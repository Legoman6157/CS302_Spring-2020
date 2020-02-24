#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
using namespace std;

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

struct pixel {
	int x;
	int y;

	pixel() {};
	pixel(int n_x, int n_y): x(n_x), y(n_y) {};
};//pixel

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

std::vector<pixel> read_data(int argc, char **argv, Superball *s)
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

	//Print out data
	printf("Empty cells:			%2d\n", s->empty);
	printf("Non-Empty cells:		%2d\n", s->r*s->c - s->empty);
	printf("Number of pieces in goal cells:	%2d\n", ngoal);
	printf("Sum of their values:		%2d\n", tgoal);

	return pieces;
}

