#include <cstddef>

template <typename T>
class LinkedList {
	public:
			struct Node {
			T data;
			Node* next;
			Node* last;

			Node(T n_data) {
				data = n_data;
				next = NULL;
				last = NULL;
			}//Constructor
		};//Node

		Node* head;
		Node* tail;

		LinkedList(): head(NULL), tail(NULL) {};
		~LinkedList() {
			while (head != NULL) {
				Node* temp = head;
				head = head->next;
				delete temp;
				if (head != NULL)
					head->last = NULL;
			}//while head != NULL
		}//Destructor

		void push_front(T n_data);
		void push_back(T n_data);
		void reserve(int size);
		void clear();
};//LinkedList
