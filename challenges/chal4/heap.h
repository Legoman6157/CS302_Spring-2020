/* heap.h
 * Joshua Byers
 */

#include <vector>

template<typename T>
class Heap {
	protected:
		std::vector<T> heap;

	public:
		int size() const { return heap.size(); }
		virtual void push(T val)=0;
		virtual T pop()=0;
		virtual void heapify(int i)=0;
};//Heap


template<typename T>
class MinHeap: public Heap<T> {

	void push(T val) {
		
	}//Minheap.push(T val)
};//MinHeap

template<typename T>
class MaxHeap: public Heap<T> {};
