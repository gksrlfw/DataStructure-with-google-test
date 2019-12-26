
#ifndef SORTEDARRAYLIST_H_
#define SORTEDARRAYLIST_H_
#include <stdexcept>
#include <iterator>
#include <initializer_list>
#include <iostream>

class SortedArrayList {
	class ListIterator : public std::iterator<std::input_iterator_tag, int> {
		int* p;
	public:
		explicit ListIterator(int* p) : p{ p } {}
		ListIterator& operator++() noexcept { ++p; return *this; }
		ListIterator operator++(int) noexcept { ListIterator retval = *this; ++p; return retval; }
		bool operator==(ListIterator other) const noexcept { return p == other.p; }
		bool operator!=(ListIterator other) const noexcept { return p != other.p; }
		int operator*() const noexcept { return *p; }
	};
private:

	const static unsigned int MAX{ 10 };
	int list[MAX];
	long size{ 0 };
	int search(int key, int startIndex = 0) const noexcept {
		long low{ 0 };
		long high{ size - 1 };
		while (low <= high) {
			//long mid{(low+high)/2};
			long mid{ low + (high - low) / 2 };
			if (list[mid] == key) return mid;
			else if (list[mid] < key) low = mid + 1;
			else high = mid - 1;
		}
		return low;
		/*
		for(int i=startIndex; i<size; i++){
			if(list[i]>=key) return i;
		}
		return size;
		*/
	}
public:
	SortedArrayList() = default;
	SortedArrayList(std::initializer_list<int> initList) {
		try {
			for (auto n : initList) add(n);
		}
		catch (std::runtime_error& e) {}
	}
	virtual ~SortedArrayList() = default;
	bool isEmpty() const noexcept {
		return size == 0;
	}
	bool isFull() const noexcept {
		return size == MAX;
	}
	void clear() noexcept {
		size = 0;
	}
	unsigned int getSize() const noexcept {
		return size;
	}

	int operator[](int index) const {
		if (index >= 0 && index < size) return list[index];
		else throw std::out_of_range("");
	}
	/*
	int& operator[](int index){
		if(index>=0&&index<size) return list[index];
		else throw std::out_of_range("");
	}
	*/

	void add(int key) {
		if (isFull()) throw std::runtime_error("add: state is full");
		if (isEmpty() || list[size - 1] <= key) list[size] = key;
		else {
			int index{ search(key) };
			for (int i = size - 1; i >= index; i--) {
				list[i + 1] = list[i];
			}
			list[index] = key;
		}
		++size;
	}

	int popBack() {
		if (isEmpty()) throw std::runtime_error("pushBack: state is empty");
		--size;
		return list[size];
	}
	int popFront() {
		if (isEmpty()) throw std::runtime_error("popFront: state is empty");
		int tmp = list[0];
		for (int i = 1; i < size; i++) {
			list[i - 1] = list[i];
		}
		--size;
		return tmp;
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
		int index{ search(key) };
		return index < size && list[index] == key;
	}
	void removeFirst(int key) noexcept {
		int index{ search(key) };
		if (list[index] == key) {
			for (int i = index; i < size - 1; i++)
				list[i] = list[i + 1];
			--size;
		}
	}
	void removeAll(int key) noexcept {
		int index{ search(key) };
		if (list[index] == key) {
			int low = index - 1;
			int high = index + 1;
			while (low >= 0 && list[low] == key) --low;
			while (high < size && list[high] == key) ++high;
			++low;
			--high;
			int count = high - low + 1;
			for (int i = high + 1; i < size; i++) {
				list[low] = list[i];
				++low;
			}
			size -= count;
		}
	}
	ListIterator begin() { return ListIterator(list); }
	ListIterator end() { return ListIterator(list + size); }
};

#endif /* SORTEDARRAYLIST_H_ */
