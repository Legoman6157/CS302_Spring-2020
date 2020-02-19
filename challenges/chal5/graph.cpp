#include "graph.h"

bool Graph::path_exists(char s, char t) {
	std::queue<char> node_queue;
	bool node_visited[edges.size()] = {false};
	node_queue.push(s);

	char curr_node;

	while (!node_queue.empty()) {
		curr_node = node_queue.front();
		node_queue.pop();
		node_visited[curr_node-'A'] = 1;

		if (curr_node == t)
			return true;

		for (auto it : edges[curr_node]) {
			if (!node_visited[(int)((it)-'A')])
				node_queue.push(it);
		}
	}//while (!node_queue.empty())

	return false;
}//Graph::path_exists(char, char)

void Graph::insert(char from, char to) {
	edges[from].push_back(to);

	if (edges.find(to) == edges.end())
		edges.insert(std::pair< char, std::vector<char> >(to, std::vector<char>()));
}//Graph::insert()

/*Graph::clear()
 *Clear the graph
 *
 *Clear the edge map and its adjacency lists
*/
void Graph::clear() {
	for (auto it : edges)
		it.second.clear();

	edges.clear();
}//Graph::clear()
