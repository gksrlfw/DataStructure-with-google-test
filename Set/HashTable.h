#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <cstddef>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <list>
#include <vector>
#include <iterator>
#include <string>
#include <functional>
using namespace std;

template <typename T>
class HashTable {
	using List = list<T>;
private:
	int capacity;
	int size = 0;
	bool capacityFlag = false;
	List* list = nullptr;
	vector<T> traverseVector;
	constexpr static int p = 987891723;
public:
	HashTable() : capacity(7), list{ new List[capacity] }{}
	void clear() {
		delete[] list;
		list = nullptr;
		size = 0;
		capacityFlag = false;
	}
	virtual ~HashTable() {
		clear();
	}
	HashTable(const HashTable& other) :
		capacity{ other.capacity }, size{ other.size },
		capacityFlag{ other.capacityFlag }, list{ new List[capacity] }{
		for (int i = 0; i < capacity; i++) {
			list[i].insert(list[i].begin(),
				other.list[i].cbegin(), other.list[i].cend());
		}
	}
	HashTable(HashTable&& other) :
		capacity{ other.capacity }, size{ other.size },
		capacityFlag{ other.capacityFlag }, list{ other.list }{
		other.list = nullptr;
	}
	const HashTable& operator=(const HashTable& other) noexcept {
		capacity = other.capacity;
		size = other.size;
		capacityFlag = other.capacityFlag;
		clear();
		list = new List[capacity];
		for (int i = 0; i < capacity; i++) {
			list[i].insert(list[i].begin(),
				other.list[i].cbegin(), other.list[i].cend());
		}
		return *this;
	}
	HashTable& operator=(HashTable&& other) noexcept {
		capacity = other.capacity;
		size = other.size;
		capacityFlag = other.capacityFlag;
		list = other.list;
		other.list = nullptr;
		return *this;
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

	void add(const T& key) noexcept {
		if (needMoreSpace()) increaseCapacity();
		int index = hash(key);
		if (size == 0 || !contains(key)) {
			list[index].push_front(key);
			traverseVector.push_back(key);
			if (list[index].size() >= 3) capacityFlag = true;
			++size;
		}
	}

	bool contains(const T& key) const noexcept {
		if (isEmpty()) return false;
		int index = hash(key);
		for (auto s : list[index])
			if (s == key) return true;
		return false;
	}

	void remove(const T& key) noexcept {
		if (isEmpty()) return;
		int index = hash(key);
		if (contains(key)) {
			list[index].remove(key);
			traverseVector.erase(find(traverseVector.begin(), traverseVector.end(), key));
			--size;
		}
	}
	auto begin() const { return traverseVector.cbegin(); }
	auto end() const { return traverseVector.cend(); }

private:
	bool needMoreSpace() const {
		return capacityFlag || ((double)size / capacity > 0.7);
	}

	void rehashAll(List* temp) {
		for (auto s : traverseVector) {
			int index = hash(s);
			temp[index].push_front(s);
		}
	}

	void increaseCapacity() {
		int previousSize = size;
		clear();
		capacity = capacity * 2 + 1;
		List* temp = new List[capacity];
		rehashAll(temp);
		list = temp;
		size = previousSize;
	}

	int hash(const T& key) const noexcept {
		auto hashvalue = std::hash<T>{}(key);
		return hashvalue % capacity;
	}
};
#endif /* HASHTABLE_H_ */
