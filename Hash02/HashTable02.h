// Chaing

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
using  namespace std;

using List = std::list<std::string>;

class HashTable {
	int capacity;
	int size = 0;
	bool capacityFlag = false;
	List* list = nullptr;
	vector<string> traverseVector;
	constexpr static int p = 974283241;
public:
	HashTable()
		:capacity(7), list(new List[capacity]) {}
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

	void add(string key) noexcept {
		if (needMoreSpace()) increaseCapacity();
		int index = hash(key);
		if (size == 0 || !contains(key)) {
			list[index].push_front(key);
			traverseVector.push_back(key);
			if (list[index].size() >= 3) capacityFlag = true;
			++size;
		}
	}

	bool contains(string key) const noexcept {
		if (isEmpty()) return false;
		int index = hash(key);
		for (auto s : list[index])
			if (s == key) return true;
		return false;
	}

	void remove(string key)	noexcept {
		if (isEmpty()) return;
		int index = hash(key);
		if (contains(key)) {
			list[index].remove(key);
			traverseVector.erase(find(traverseVector.begin(), traverseVector.end(), key));
			--size;
		}
	}
	
	void debugPrint() {
		for (int i = 0; i < capacity; i++) {
			std::cout << i << ": ";
			if (list[i].empty()) std::cout << "empty\n";
			else {
				for (auto key : list[i]) {
					std::cout << key << "(" << hash(key) << "), ";
				}
				std::cout << "\n";
			}
		}
	}

	//ConstVectorIterator begin() const { return traverseVector.cbegin(); }
	//ConstVectorIterator end() const { return traverseVector.cend(); }
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

	int hash(string key) const noexcept {
		unsigned long value = 0;
		const size_t length = key.length();
		for (int i = length - 1; i >= 0; i--)
			// 문자 하나에 31씩 곱하여 더해준다.
			value = (value * 31 + (unsigned int)key[i]) % p;
		return value % capacity;
	}
};
#endif /* HASHTABLE_H_ */
