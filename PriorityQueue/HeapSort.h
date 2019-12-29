#include <iostream>
#include <algorithm>
void makeHeap(int* list, int size);
void reheapDown(int* list, int size, int index);
void moveMax(int* heap, int size);
void reorder(int* list, int size);

// �ܰ� 1. ���� �迭�� ������ Ư���� ������ ���ġ: ���(n/2 * log n)
// �ܰ� 2. ���� ū ���� �� �ڷ� �̵��� �� �� ���� �����ϰ� ������ �ٽ� ���� (n * log n)
void heapSort(int* list, int size) {
	makeHeap(list, size);
	reorder(list, size);
}

void makeHeap(int* list, int size) {
	int startLoc{ (size - 2) / 2 };	// ���� ������ �θ� ��ġ (index-1)/2, ������ �ܸ��� ��ġ�� size-1
	for (int i = startLoc; i >= 0; i--) {
		reheapDown(list, size, i);
	}
}

void moveMax(int* heap, int size) {
	std::swap(heap[0], heap[size - 1]);
	reheapDown(heap, size - 1, 0);
}

void reheapDown(int* heap, int size, int index) {
	int currIndex = index;
	while (currIndex < size) {
		int leftChild{ 2 * currIndex + 1 };
		int rightChild{ leftChild + 1 };
		if (leftChild >= size) return;
		int maxChild{ leftChild };
		if (rightChild < size && heap[leftChild] < heap[rightChild])
			maxChild = rightChild;
		if (heap[maxChild] < heap[currIndex]) return;
		else std::swap(heap[maxChild], heap[currIndex]);
		currIndex = maxChild;
	}

}

void reorder(int* heap, int size) {
	int currSize = size;
	for (int i = 0; i < size - 1; i++) {
		moveMax(heap, currSize);
		--currSize;
	}
}

