#include "link_list.h"

template <typename T>
void LinkedList<T>::push_front(T n_data) {
	Node* temp = new Node(n_data);
	temp->next = head;
	if (head)
		head->last = temp;
	head = temp;
	if (tail == NULL)
		tail = temp;
}

template <typename T>
void LinkedList<T>::push_back(T n_data) {
	Node* temp = new Node(n_data);
	temp->last = tail;
	if (tail)
		temp->next = temp;
	tail = temp;
	if (head == NULL)
		head = temp;
}
