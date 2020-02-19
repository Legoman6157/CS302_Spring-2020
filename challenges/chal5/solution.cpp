#include "graph.cpp"

#include <iostream>


int main() {
	int N_edges,
		 N_paths,
		 graph_num = 1;

	char from_buff,
		  to_buff;

	Graph graph;

	std::vector< std::pair<char, char> > paths;

	while (std::cin >> N_edges) {

		//Just for making diff stay quiet
		if (graph_num > 1)
			std::cout << std::endl;

		//Get all edges
		for (int i = 0; i < N_edges; i++) {
			std::cin >> from_buff >> to_buff;
			graph.insert(from_buff, to_buff);
		}//for i < N

		//Get all paths
		std::cin >> N_paths;
		for (int i = 0; i < N_paths; i++) {
			std::cin >> from_buff >> to_buff;
			paths.push_back(std::pair<char, char>(from_buff, to_buff));
		}

		//Search for paths based on given edges
		for (auto paths_it : paths) {

				bool path_exist = graph.path_exists(paths_it.first, paths_it.second);
				std::cout << "In Graph " << graph_num << " there is " << std::flush;

				if (path_exist)
					std::cout << "a" << std::flush;
				else
					std::cout << "no" << std::flush;

				std::cout << " path from "
							 << paths_it.first
							 << " to "
							 << paths_it.second
							 << std::endl;
		}

		//Clear all and preapre for next set of edges and paths.
		graph.clear();
		paths.clear();

		//Go to next graph
		graph_num++;
	}//while (std::cin >> N)

	for (auto edges_it : graph.get_edges()) {
		std::cout << edges_it.second.size() << std::endl;
		for (auto vec_it : edges_it.second)
			std::cout << edges_it.first << vec_it << std::endl;
	}
}
