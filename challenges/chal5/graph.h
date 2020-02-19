#include <map>
#include <vector>

class Graph {
	private:
		std::map< char, std::vector<char> > edges;
		inline bool node_exists(char c) { return edges.find(c) != edges.end(); }
		dfs

	public:
		std::vector<char>& operator[](char c) { return edges[c]; }

		void tell_graph();

		std::map< char, std::vector<char> > get_edges() const { return edges; }

};//Graph
