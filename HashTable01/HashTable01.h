// 선형조사, delete flag 사용
// delete flag : 버킷 삭제시 표시한다. 어느 정도 선형탐색이 되는 것을 방지할 수 있다. (추가, 삭제를 많이하는 경우에는 효율이 없을수도 있다.)
#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

class HashTable {
	struct Bucket {
		string key;
		bool deleteFlag = false;
		bool empty = true;
	};

	class TableIterator
		: public iterator<input_iterator_tag, string> {
		Bucket* p;
		Bucket* end;
	public:
		explicit TableIterator(Bucket* p, int capacity)
			: p(p), end(p + capacity) {}
		const TableIterator& operator++() noexcept {
			++p;
			while (p->empty && p != end) ++p;
			return *this;
		}

		TableIterator operator++(int) noexcept {
			TableIterator temp(*this);
			while (p->empty && p != end) ++p;
			return temp;
		}
		bool operator==(const TableIterator& other) const noexcept {
			return p == other.p;
		}
		bool operator!=(const TableIterator& other) const noexcept {
			return !(p == other.p);
		}
		const string& operator*() const noexcept {
			return p->key;
		}
	};
private:
	int capacity;
	int size = 0;
	Bucket* list;
	constexpr static unsigned long p = 4210098769;
public:
	HashTable(int capacity = 7)
		:capacity(capacity), list(new Bucket[capacity]) {}
	HashTable(const HashTable& other)
		: HashTable(other.capacity) {
		size = other.size;
		copy(other.list, other.list + other.capacity, list);
	}
	HashTable(HashTable&& other)
		:capacity(other.capacity), size(other.size) {
		list = other.list;
		other.list = nullptr;
	}
	virtual ~HashTable() {
		if (list) delete[] list;
	}
	const HashTable& operator=(const HashTable& other) {
		if (list) delete[] list;
		capacity = other.capacity;
		size = other.size;
		list = new Bucket[capacity];
		std::copy(other.list, other.list + other.capacity, list);
		return *this;
	}
	const HashTable& operator=(HashTable&& other) {
		if (list) delete[] list;
		capacity = other.capacity;
		size = other.size;
		list = other.list;
		other.list = nullptr;
		return *this;
	}
	void clear() {
		for (int i = 0; i < capacity; i++) {
			list[i].deleteFlag = false;
			list[i].empty = true;
		}
		size = 0;
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

	void add(string key) {
		if (needMoreSpace()) increaseCapacity();
		int index = hash(key);
		for (int i = 0; i < capacity; i++) {
			if (list[index].empty) {
				list[index].key = key;
				list[index].deleteFlag = false;
				list[index].empty = false;
				++size;
				return;
			}
			else if (!list[index].empty && list[index].key == key) return;
			index = (index + 1) % capacity;
		}
	}

	bool contains(string key) const noexcept {
		if (isEmpty()) return false;
		int index = hash(key);
		for (int i = 0; i < capacity; i++) {
			if (!list[index].empty && list[index].key == key)
				return true;
			else if (list[index].empty && !list[index].deleteFlag) return false;
			index = (index + 1) % capacity;
		}
		return false;
	}

	void remove(string key) noexcept {
		if (isEmpty()) return;
		int index = hash(key);
		for (int i = 0; i < capacity; i++) {
			if (!list[index].empty && list[index].key == key) {
				list[index].deleteFlag = true;
				list[index].empty = true;
				--size;
				return;
			}
			index = (index + 1) % capacity;
		}
	}
	TableIterator begin() { return TableIterator(list, capacity); }
	TableIterator end() { return TableIterator(list + capacity, capacity); }
private:
	bool needMoreSpace() {
		return (double)size / capacity > 0.7;
	}
	void increaseCapacity() {
		vector<string> keyset;
		for (int i = 0; i < capacity; i++)
			if (!list[i].empty) keyset.push_back(list[i].key);
		delete[] list;
		capacity = capacity * 2 + 1;
		list = new Bucket[capacity];
		size = 0;
		for (auto key : keyset) add(key);
	}

	int hash(string key) const noexcept {
		unsigned long value = 0;
		constexpr unsigned long x = 62057;
		const size_t length = key.length();
		for (int i = length - 1; i >= 0; i--)
			value = (value * x + (unsigned int)key[i]) % p;
		// return hashInteger((int)value);
		return value % capacity;
	}
	/* 굳이 필요없음
	int hashInteger(int x) const noexcept {
		constexpr unsigned long a = 42283;
		constexpr unsigned long b = 44267;
		unsigned long value = (a * x + b) % p;
		return value % capacity;
	}*/
};
#endif /* HASHTABLE_H_ */
