#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <stack>
#include <vector>

#include "sb-read.cpp"
#include "disjoint_by_rank.cpp"

using namespace std;

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

struct dset {
	char piece;
	std::vector<pixel> pixels;
	int score;
};//dset

std::vector<dset> sb_analyze(int argc, char* argv[], Superball *s) {

	DisjointSetByRankWPC ds(s->r*s->c);

	std::vector<pixel> goal_pieces = read_data(argc, argv, s);

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

		if (curr_pixel_loc == ds.Find(curr_pixel_loc) && temp_dset.pixels.size() >= 5) {
			temp_dset.score = s->colors[temp_dset.piece] * temp_dset.pixels.size();
			dsets.push_back(temp_dset);
		}

	}//for (i < goal_pieces.size())


	return dsets;
}//find_dsets(read_data rd)
