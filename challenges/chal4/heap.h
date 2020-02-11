/* heap.h
 * Joshua Byers
 */

#include <iostream>
#include <vector>

template<typename T>
class Heap {
	protected:
		std::vector<T> heap;
		void swap(T &a, T &b) {
			T temp = a;
			a = b;
			b = temp;
		}//swap

	public:
		int size() const { return heap.size(); }
		virtual void push(T val)=0;
		virtual T pop()=0;
};//Heap


template<typename T>
class MinHeap: public Heap<T> {
	protected:
		std::vector<T> heap;
		void heapify_up(int loc);
		void heapify_down(int loc);
	public:
		void push(T val);
		T pop();
};//MinHeap


template<typename T>
class MaxHeap: public Heap<T> {
	protected:
		std::vector<T> heap;
		void heapify_up(int loc);
		void heapify_down(int loc);
	public:
		void push(T val);
		T pop();
		void heapify(int loc);
};


template<typename T>
void MinHeap<T>::push(T val) {
	heap.push_back(val);
	heapify_up(heap.size()-1);
}

template<typename T>
T MinHeap<T>::pop() {
	for (int i = 0; i < heap.size(); i++)
		std::cout << heap[i] << std::endl;
}

template<typename T>
void MinHeap<T>::heapify_up(int loc) {

	if (loc == 0)
		return;

	int parent = (loc-1)/2;
	
	if (heap[parent] > heap[loc]) {
		MinHeap::Heap::swap(heap[parent], heap[loc]);
		heapify_up(parent);
	}
}//MinHeap::heapify_up

template<typename T>
void MinHeap<T>::heapify_down(int loc) {
	
	int left_loc = loc * 2 + 1,
		 right_loc = loc * 2 + 2;

	int N = heap.size();

	bool left_exists = left_loc < N,
		  right_exists = right_loc < N;

	if (!left_exists && !right_exists)
		return;
	
	int left_val = heap[left_loc],
		 right_val = heap[right_loc];

	if (left_exists && right_exists) {

		if (left_val < right_val) {
			swap(heap[loc], heap[left_loc]);
			heapify_down(left_loc);
		} else if (right_val < left_val){
			swap(heap[loc], heap[right_loc]);
			heapify_down(right_loc);
		}

	} else if (left_exists && (left_val < heap[loc])) {

		swap(heap[loc], heap[left_loc]);
		heapify_down(heap[left_loc]);

	} else if (right_exists && (right_val < heap[loc])) {

		swap(heap[loc], heap[right_loc]);
		heapify_down(heap[right_loc]);

	}
}//MinHeap::heapify_down


template<typename T>
void MaxHeap<T>::push(T val) {
	heap.push_back(val);
	heapify_up(heap.size()-1);
}

template<typename T>
T MaxHeap<T>::pop() {
	for (int i = 0; i < heap.size(); i++)
		std::cout << heap[i] << std::endl;
}

template<typename T>
void MaxHeap<T>::heapify_up(int loc) {

	if (loc == 0)
		return;

	int parent = (loc-1)/2;
	
	if (heap[parent] < heap[loc]) {
		MaxHeap::Heap::swap(heap[parent], heap[loc]);
		heapify_up(parent);
	}
}//MaxHeap::heapify_up

template<typename T>
void MaxHeap<T>::heapify_down(int loc) {
	
	int left_loc = loc * 2 + 1,
		 right_loc = loc * 2 + 2;

	int N = heap.size();

	bool left_exists = left_loc < N,
		  right_exists = right_loc < N;

	if (!left_exists && !right_exists)
		return;
	
	int left_val = heap[left_loc],
		 right_val = heap[right_loc];

	if (left_exists && right_exists) {

		if (left_val > right_val) {
			swap(heap[loc], heap[left_loc]);
			heapify_down(left_loc);
		} else if (right_val > left_val){
			swap(heap[loc], heap[right_loc]);
			heapify_down(right_loc);
		}

	} else if (left_exists && (left_val > heap[loc])) {

		swap(heap[loc], heap[left_loc]);
		heapify_down(heap[left_loc]);

	} else if (right_exists && (right_val > heap[loc])) {

		swap(heap[loc], heap[right_loc]);
		heapify_down(heap[right_loc]);

	}
}//MaxHeap::heapify_down
