#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <queue>
#include <vector>

#include "sb-read.cpp"
#include "disjoint_by_rank.cpp"

using namespace std;

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

struct dset {
	int size;
	int score;
	std::vector<pixel> pixels;
};//dset

std::vector<dset> find_dsets(Superball *s, DisjointSetByRankWPC ds, std::vector<pixel> goal_pieces) {
	std::vector<dset> dsets;

	std::queue<pixel> bfs_q;
	pixel curr_pixel,
			temp_pixel;

	dset temp_dset;

	int curr_pixel_loc,
		 north_loc,
		 east_loc,
		 west_loc,
		 south_loc;

	for (int i = 0; i < goal_pieces.size(); i++) {
		bfs_q.push(pixel(goal_pieces[i].x, goal_pieces[i].y));

		while (!bfs_q.empty()) {
			curr_pixel = bfs_q.back();
			bfs_q.pop();

			
			curr_pixel_loc = curr_pixel.x * s->c + curr_pixel.y;
			north_loc = curr_pixel.x+1 * s->c + curr_pixel.y;
			east_loc = curr_pixel.x * s->c + curr_pixel.y+1;
			west_loc = curr_pixel.x * s->c + curr_pixel.y-1;
			south_loc = curr_pixel.x-1 * s->c + curr_pixel.y;

			//N
			if ( (curr_pixel.x > 0)
					&& (ds.Find(north_loc) != ds.Find(curr_pixel_loc))
					&& (s->board[north_loc] == s->board[curr_pixel_loc]) ) {
std::cout << "N" << std::endl;
				ds.Union(north_loc, curr_pixel_loc);

				temp_pixel.x = north_loc/s->c;
				temp_pixel.y = north_loc%s->c;

				bfs_q.push(pixel(temp_pixel));
				temp_dset.pixels.push_back(temp_pixel);
			}

			//E
			if ( (curr_pixel.x > 0)
					&& (ds.Find(east_loc) != ds.Find(curr_pixel_loc))
					&& (s->board[east_loc] == s->board[curr_pixel_loc]) ) {

std::cout << "E" << std::endl;
				ds.Union(east_loc, curr_pixel_loc);

				temp_pixel.x = north_loc/s->c;
				temp_pixel.y = north_loc%s->c;

				bfs_q.push(pixel(temp_pixel));
				temp_dset.pixels.push_back(temp_pixel);
			}

			//W
			if ( (curr_pixel.x > 0)
					&& (ds.Find(west_loc) != ds.Find(curr_pixel_loc))
					&& (s->board[west_loc] == s->board[curr_pixel_loc]) ) {

std::cout << "W" << std::endl;
				ds.Union(west_loc, curr_pixel_loc);

				temp_pixel.x = north_loc/s->c;
				temp_pixel.y = north_loc%s->c;

				bfs_q.push(pixel(temp_pixel));
				temp_dset.pixels.push_back(temp_pixel);
			}

			//S
			if ( (curr_pixel.x > 0)
					&& (ds.Find(south_loc) != ds.Find(curr_pixel_loc))
					&& (s->board[south_loc] == s->board[curr_pixel_loc]) ) {

std::cout << "S" << std::endl;
				ds.Union(south_loc, curr_pixel_loc);

				temp_pixel.x = north_loc/s->c;
				temp_pixel.y = north_loc%s->c;

				bfs_q.push(pixel(temp_pixel));
				temp_dset.pixels.push_back(temp_pixel);
			}
		}//while (!bfs_q.empty())

		dsets.push_back(temp_dset);

		temp_dset.size = 0;
		temp_dset.pixels.clear();

	}//for (i < goal_pieces.size())

	return dsets;
}//find_dsets(read_data rd)

void sb_analyze();

int main(int argc, char **argv)
{
	Superball *s;
 
	s = new Superball(argc, argv);

	DisjointSetByRankWPC ds(s->r*s->c);

	std::vector<pixel> goal_pieces = read_data(argc, argv, s);

	for (auto it : goal_pieces)
		std::cout
		<< '('
		<< it.x
		<< ','
		<< it.y
		<< ')'
		<< ": "
		<< s->board[it.x * s->c + it.y]
		<< std::endl;
	
	std::vector<dset> dsets = find_dsets(s, ds, goal_pieces);

	for (auto it_dsets : dsets) {
		std::cout << it_dsets.size << std::endl;
		for (auto it_dsets_pixels : it_dsets.pixels)
			std::cout
				<< '('
				<< it_dsets_pixels.x
				<< ','
				<< it_dsets_pixels.y
				<< ')'
				<< std::endl;
	}
}
