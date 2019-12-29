#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <initializer_list>
#include <cmath>
using namespace std;

class BinaryHeap {
	class HeapIterator
		: public iterator<input_iterator_tag, int> {
		int* p;
	public:
		explicit HeapIterator(int* p)
			:p(p) {}
		const HeapIterator& operator++() { ++p; return *this; }
		HeapIterator operator++(int) { HeapIterator retval = *this; ++p; return retval; }
		bool operator==(const HeapIterator& other) const { return p == other.p; }
		bool operator!=(const HeapIterator& other) const { return !(*this == other); }
		int operator*() const { return *p; }
	};

	int capacity;
	int* heap;
	int size = 0;
	bool needMoreSpace() const {
		return size == capacity;
	}
	void increaseCapacity() {
		capacity *= 2;
		int* temp = new int[capacity];
		copy(heap, heap + size, temp);
		delete[] heap;
		heap = temp;
	}
public:
	BinaryHeap()
		:capacity(15), heap(new int[capacity]) {}
	BinaryHeap(initializer_list<int> initList)
		:BinaryHeap() {
		for (auto n : initList) add(n);
	}
	virtual ~BinaryHeap() {
		delete[] heap;
	}
	bool isEmpty() const noexcept {
		return size == 0;
	}
	bool isFull() const noexcept {
		return false;
	}
	int getSize() const noexcept {
		return size;
	}
	void clear() noexcept {
		size = 0;
	}
	int* getHeap() {
		return heap;
	}
	void add(int key) noexcept {
		if (needMoreSpace())  increaseCapacity();
		heap[size] = key;
		reheapUp(size);
		++size;
	}

	int getMax() const noexcept {
		if (isEmpty()) throw std::runtime_error("extract Max: heap is empty");
		return heap[0];
	}

	int extractMax() {
		if (isEmpty()) throw std::runtime_error("extract Max: heap is empty");
		int temp = heap[0];
		swap(heap[0], heap[size - 1]);
		--size;
		reheapDown(0);
		return temp;
	}

	void changePriority(int index, int key) {
		if (isEmpty()) throw std::runtime_error("changePriority: heap is empty");
		if (index < 0 || index >= size) throw std::range_error("changePriority: illegal index");
		int prevKey = heap[index];
		heap[index] = key;
		if (prevKey > key) reheapDown(index);
		else reheapUp(index);
	}

	void remove(int index) {
		if (index == size - 1) --size;
		else {
			--size;
			changePriority(index, heap[size]);
		}
	}

	/*
	완전이진트리는 배열로 표현가능
	parent(i) = (i-1)/2
	left(i) = 2i+1
	right(i) = 2i+2
	
	*/
	void reheapUp(int index) {
		int curIndex = index;
		while (curIndex > 0) {
			int parentIndex = (curIndex - 1) / 2;
			if (heap[parentIndex] > heap[curIndex]) return;
			else swap(heap[parentIndex], heap[curIndex]);
			curIndex = parentIndex;
		}
	}

	void reheapDown(int index) {
		int curIndex = index;
		while (curIndex < size) {
			int leftChild = 2 * curIndex + 1;
			int rightChild = leftChild + 1;
			// 단말노드 > 그냥 리턴
			if (leftChild >= size) return;
			// 왼쪽 자식만 있는경우 > 그냥 왼쪽자식을 넣는다.
			int maxChild = leftChild;
			// 둘다 있는경우 > 두 노드 중 큰 노드와 바꾼다.
			if (rightChild < size && heap[leftChild] < heap[rightChild])
				maxChild = rightChild;
			if (heap[maxChild] < heap[curIndex]) return;
			else swap(heap[maxChild], heap[curIndex]);
			curIndex = maxChild;
		}
	}
	/*
	void reheapDown(int* heap, int size, int index) {
		int curIndex = index;
		while (curIndex < size) {
			int leftChild = 2 * curIndex + 1;
			int rightChild = 2 * curIndex + 2;
			if (leftChild >= size) return;
			int maxChild = leftChild;
			if (rightChild < size && heap[leftChild] < heap[rightChild])
				maxChild = rightChild;
			if (heap[maxChild] < heap[curIndex]) return;
			else swap(_Is_heap_until_unchecked)
		}
	}*/

	
};
#endif /* BINARYHEAP_H_ */
