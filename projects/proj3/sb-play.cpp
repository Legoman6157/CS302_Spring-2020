#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
using namespace std;

//#include "sb-analyze.cpp"

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))


int main(int argc, char **argv)
{
//	Superball *s;

//	s = new Superball(argc, argv);

//	std::vector<dset> dsets = sb_analyze(argc, argv, s);

//	pixel a(-1,0),
//			b(0,0);

/*	for (int i = 0; i < s->r*s->c; i++) {
		std::cout << "Looking for pieces..." << std::endl;
		if (s->board[i] != '.' && s->board[i] != '*')
			if (a.x == -1) {
				a.x = i/s->c;
				a.y = i%s->c;
			} else {
				b.x = i/s->c;
				b.y = i%s->c;
				break;
			}
	}//for*/

	std::printf("SWAP 0 0 0 1\n");//, a.x, a.y, b.x, b.y);
	
	return 0;
}//main
