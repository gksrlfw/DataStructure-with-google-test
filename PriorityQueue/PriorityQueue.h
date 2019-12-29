#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_
#include "BinaryHeap.h"

class PriorityQueue {
	BinaryHeap heap;
public:
	PriorityQueue() = default;
	PriorityQueue(std::initializer_list<int> initList) : heap{ initList } {}
	virtual ~PriorityQueue() = default;
	bool isEmpty() const noexcept {
		return heap.isEmpty();
	}
	bool isFull() const noexcept {
		return heap.isFull();
	}
	int getSize() const noexcept {
		return heap.getSize();
	}
	void clear() noexcept {
		heap.clear();
	}
	int* getHeap() {
		return heap.getHeap();
	}
	void enqueue(int key) noexcept {
		heap.add(key);
	}
	int dequeue() {
		return heap.extractMax();
	}
	int peek() const {
		return heap.getMax();
	}
};
#endif /* PRIORITYQUEUE_H_ */
