

#ifndef UNSORTEDARRAYLIST_H_
#define UNSORTEDARRAYLIST_H_
#include <stdexcept>
#include <iterator>
#include <initializer_list>
#include <iostream>

class UnsortedArrayList {
	class ListIterator : public std::iterator<std::input_iterator_tag, int> {
		int* p;
	public:
		explicit ListIterator(int* p)
			: p(p) {}
		ListIterator& operator++() noexcept { ++p; return *this; }
		ListIterator operator++(int) noexcept { ListIterator retval = *this; ++p; return retval; }
		bool operator==(ListIterator other) const noexcept { return p == other.p; }
		bool operator!=(ListIterator other) const noexcept { return p != other.p; }
		int operator*() const noexcept { return *p; }
	};
private:
	unsigned int capacity = 5;
	int* list = nullptr;
	unsigned int size = 0;
	bool needMoreSpace() {
		return size == capacity;
	}
	void increaseCapacity() {
		capacity *= 2;
		int* temp = new int[capacity];
		std::copy(list, list + size, temp);
		if (list) delete[] list;
		list = temp;
	}
	int search(int key, int startIndex = 0) const noexcept {
		for (int i = startIndex; i < size; i++)
			if (list[i] == key) return i;
		return -1;
	}

public:
	UnsortedArrayList(unsigned int capacity = 5)
		: capacity(capacity), list(new int[capacity]) {}
	UnsortedArrayList(std::initializer_list<int> initList)
		: UnsortedArrayList(initList.size()) {
		for (auto n : initList) pushBack(n);
	}
	UnsortedArrayList(const UnsortedArrayList& other)
		: UnsortedArrayList(other.capacity) {
		size = other.size;
		std::copy(other.list, other.list + size, list);
	}
	UnsortedArrayList(UnsortedArrayList&& other)
		: capacity(other.capacity), size(other.size) {
		list = other.list;
		other.list = nullptr;
	}

	virtual ~UnsortedArrayList() {
		if (list) delete[] list;
	}
	bool isEmpty() const noexcept {
		return size == 0;
	}
	bool isFull() const noexcept {
		return false;
	}
	void clear() noexcept {
		size = 0;
	}
	unsigned int getSize() const noexcept {
		return size;
	}
	unsigned int getCapaciy() const noexcept {
		return capacity;
	}

	const UnsortedArrayList& operator=(const UnsortedArrayList& other) {
		capacity = other.capacity;
		size = other.size;
		if (list) delete[] list;
		list = new int[capacity];
		std::copy(other.list, other.list + size, list);
		//std::cout << "copy assignment>> this:" << this << ", other: " << &other << "\n";
		return *this;
	}
	const UnsortedArrayList& operator=(UnsortedArrayList&& other) {
		capacity = other.capacity;
		size = other.size;
		if (list) delete[] list;
		list = other.list;
		other.list = nullptr;
		//std::cout << "move assignment>> this:" << this << ", other: " << &other << "\n";
		return *this;
	}
	int operator[](int index) const {
		if (index >= 0 && index < size) return list[index];
		else throw std::out_of_range("");
	}
	int& operator[](int index) {
		if (index >= 0 && index < size) return list[index];
		else throw std::out_of_range("");
	}

	//===========================================================================================================
	void pushBack(int key) {
		if (needMoreSpace()) increaseCapacity();
		list[size] = key;
		++size;
	}

	void pushFront(int key) {
		if (needMoreSpace()) increaseCapacity();
		list[size] = list[0];
		list[0] = key;
		++size;
	}

	int popFront() {
		if (isEmpty()) throw std::runtime_error("pushFront: state is empty");
		int temp = list[0];
		--size;
		list[0] = list[size];
		return temp;
	}

	int popBack() {
		if (isEmpty()) throw std::runtime_error("pushBack: state is empty");
		--size;
		return list[size];
	}

	int peekFront() const {
		if (isEmpty()) throw std::runtime_error("ERROR: peekFront, State: empty");
		return list[0];
	}
	int peekBack() const {
		if (isEmpty()) throw std::runtime_error("ERROR: peekBack, State: empty");
		return list[size - 1];
	}

	bool find(int key) const noexcept {
		if (isEmpty()) return false;
		//		for(int i=0; i<size; i++){
		//			if(list[i]==key) return true;
		//		}
		//		return false;
		return search(key) != -1;
	}

	void removeFirst(int key) noexcept {
		//		for(int i=0; i<size; i++) {
		//			if(list[i] == key){
		//				--size;
		//				list[i] = list[size];
		//				break;
		//			}
		//		}
		int index = search(key);
		if (index != -1) {
			--size;
			list[index] = list[size];
		}
	}

	void removeAll(int key) noexcept {
		//		for(int i=0; i<size; i++){
		//			if(list[i] == key){
		//				--size;
		//				list[i] = list[size];
		//
		//			}
		//		}
		while (1) {
			int index = search(key);
			if (index == -1) break;
			--size;
			list[index] = list[size];
		}
	}
	ListIterator begin() { return ListIterator(list); }
	ListIterator end() { return ListIterator(list + size); }
};
#endif /* UNSORTEDARRAYLIST_H_ */
