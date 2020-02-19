#include <iostream>
#include <vector>

int main() {
	int N_edges,
		 N_paths;

	char from_buff,
		  to_buff;
	
	std::vector< std::pair<char, char> > edges,
												  paths;
	
	while (std::cin >> N_edges) {
		for (int i = 0; i < N_edges; i++) {
			std::cin >> from_buff >> to_buff;
			edges.push_back(std::pair<char, char>(from_buff, to_buff));
		}

		std::cin >> N_paths;
		for (int i = 0 ; i < N_paths; i++) {
			std::cin >> from_buff >> to_buff;
			paths.push_back(std::pair<char, char>(from_buff, to_buff));
		}

		std::cout << "Edges:" << std::endl;
		for (auto it : edges)
			std::cout << it.first << ' ' << it.second << std::endl;

		std::cout << "Paths:" << std::endl;
		for (auto it : paths)
			std::cout << it.first << ' ' << it.second << std::endl;

		edges.clear();
		paths.clear();
	}//while std::cin >> N_edges
}
