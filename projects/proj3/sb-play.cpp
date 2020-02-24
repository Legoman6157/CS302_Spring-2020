#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
using namespace std;

#include "sb-analyze.cpp"

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

int main(int argc, char **argv)
{
	Superball *s;

	s = new Superball(argc, argv);

	std::vector<dset> dsets = sb_analyze(argc, argv, s);

	for (int i = 0; i < dsets.size(); i++) {
		std::printf("Size: %3d  Character: %2c  Scoring cell: (%d,%d)\n",
			dsets[i].pixels.size(),
			dsets[i].piece,
			dsets[i].pixels[0].x,
			dsets[i].pixels[0].y
		);
	}//for (i < dsets.size())
	return 0;
}//main
