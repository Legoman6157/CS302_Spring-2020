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

template <typename T>
void LinkedList<T>::reserve(int size) {
	for (int i = 0; i < size; i++)
		push_back(T());
}//reserve

template <typename T>
void LinkedList<T>::clear() {
	Node* temp;
	while (head != NULL) {
		temp = head;
		head = head->next;
		delete temp;
	}
	tail = NULL;
}//clear()
