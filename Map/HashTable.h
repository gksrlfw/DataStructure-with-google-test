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
	using List=list<T>;
private:
	int capacity;
	int size = 0;
	bool capacityFlag = false;
	List* list = nullptr;
	vector<T> traverseVector;
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

	// 사이즈를 늘릴때마다 rehash를 해준다.
	void increaseCapacity() {
		int previousSize = size;
		clear();
		capacity = 2 * capacity + 1;
		List* temp = new List[capacity];
		rehashAll(temp);
		list = temp;
		size = previousSize;
	}

	int hash(const T& key) const noexcept {
		auto hashvalue = std::hash<T>{}(key);
		return hashvalue % capacity;
		//return hashInteger(hashvalue);
	}
	/*
	// folding
	int hashInteger(unsigned long val) const noexcept {
		int length = sizeof(val);
		unsigned char* p = reinterpret_cast<unsigned char*>(&val);
		int result{ 0 };
		for (int i = 0; i < length / 2; i++) {
			result ^= (p[i] ^ p[length - 1 - i]);
		}
		return result % capacity;
	}
	*/
}; 
#endif /* HASHMAP_H_ */
