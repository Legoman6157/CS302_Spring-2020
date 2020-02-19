#include <map>
#include <vector>
#include <queue>

class Graph {
	private:
		std::map< char, std::vector<char> > edges;
		inline bool node_exists(char c) { return edges.find(c) != edges.end(); }

	public:
		std::vector<char>& operator[](char c) { return edges[c]; }
		std::map< char, std::vector<char> > get_edges() const { return edges; }

		void insert(char from, char to);
		bool path_exists(char s, char t);
		void tell_graph();
		void clear();
};//Graph
