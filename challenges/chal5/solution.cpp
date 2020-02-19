#include <iostream>

#include "graph.h"

int main() {
	int N;
	char from_buff,
		  to_buff;
	Graph graph;

	while (std::cin >> N) {
		for (int i = 0; i < N; i++) {
			std::cin >> from_buff >> to_buff;
			graph[from_buff].push_back(to_buff);
		}//for i < N
	}//while (std::cin >> N)

	for (auto edges_it : graph.get_edges()) {
		std::cout << edges_it.second.size() << std::endl;
		for (auto vec_it : edges_it.second)
			std::cout << edges_it.first << vec_it << std::endl;
	}
}
