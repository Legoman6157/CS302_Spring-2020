#include <cstdlib>
#include <iostream>
#include <queue>

class node {
	public:
		char val;

		node(char n_val) {
			val = n_val;
			parent = NULL;
			left = NULL;
			right = NULL;
		}

		~node() {
			if (left)
				delete left;
			if (right)
				delete right;
		}

		node *parent;
		node* left;
		node* right;

		void add(char n_val) {
			if (n_val < val) {
				if (left)
					left->add(n_val);
				else {
					left = new node(n_val);
					left->parent = this;
				}
			} else {
				if (right)
					right->add(n_val);
				else {
					right = new node(n_val);
					left->parent = this;
				}
			}//if n_val < val
		}//add
};//node

void dfs_print(node *head) {
	if (head->left)
		dfs_print(head->left);

	if (head->right)
		dfs_print(head->right);

	std::cout << head->val << std::endl;
}

void bfs_print(node *head) {
	std::queue<node *> node_queue;

	node_queue.push(head);

	node *current_node;

	while (!node_queue.empty()) {
		current_node = node_queue.front();
		std::cout << current_node->val << std::endl;
		node_queue.pop();

		if (current_node->left)
			node_queue.push(current_node->left);
			
		if (current_node->right)
			node_queue.push(current_node->right);
	}
}//bfs_print

int main (int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Please enter 1 or more arguments." << std::endl;
		return 0;
	}

	node *head = new node(*argv[1]);

	for (int i = 2; i < argc; i++)
		head->add(*argv[i]);

	std::cout << "Depth-first search print:" << std::endl;
	dfs_print(head);

	std::cout << std::endl;


	std::cout << "Breadth-first search print:" << std::endl;
	bfs_print(head);

	delete head;

	return 0;
}
