// Chaing

#ifndef HASHMAP_H_
#define HASHMAP_H_
#include <cstddef>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <list>
#include <set>
#include <vector>
#include <iterator>
#include <string>
#include <functional>
using namespace std;

template <typename K, typename V>
struct Entry {
	K key;
	V value;
	Entry(K key, V value)
		: key(key), value(value) {}
};

template <typename K, typename V>
class HashMap {
	using List=list<Entry<K, V>>;
private:
	int capacity;
	int size = 0;
	bool capacityFlag = false;			// 3개 이상 연결되어있을 시 true로 바뀌며 rehash 해준다.
	List* table = nullptr;
	constexpr static int p = 97453981;
public:
	HashMap()
		:capacity(7), table(new List[capacity]()) {}
	void clear() {
		delete[] table;
		table = nullptr;
		size = 0;
		capacityFlag = false;
	}
	virtual ~HashMap() {
		clear();
	}
	HashMap(const HashMap& other) :
		capacity{ other.capacity }, size{ other.size },
		capacityFlag{ other.capacityFlag },
		table{ new List[capacity]{} }{
		for (int i = 0; i < capacity; i++) {
			table[i].insert(table[i].begin(),
				other.table[i].cbegin(), other.table[i].cend());
		}
	}
	HashMap(HashMap&& other) :
		capacity{ other.capacity }, size{ other.size },
		capacityFlag{ other.capacityFlag },
		table{ other.table }{
		other.table = nullptr;
	}
	const HashMap& operator=(const HashMap& other) {
		capacity = other.capacity;
		size = other.size;
		capacityFlag = other.capacityFlag;
		clear();
		table = new List[capacity];
		for (int i = 0; i < capacity; i++) {
			table[i].insert(table[i].begin(),
				other.table[i].cbegin(), other.table[i].cend());
		}
		return *this;
	}
	HashMap& operator=(HashMap&& other) {
		capacity = other.capacity;
		size = other.size;
		capacityFlag = other.capacityFlag;
		table = other.table;
		other.table = nullptr;
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

	void put(const K& key, const V& value) {
		if (needMoreSpace()) increaseCapacity();
		int index = hash(key);
		if (isEmpty() || !containsKey(key)) {
			table[index].emplace_front(key, value);
			if (table[index].size() >= 3) capacityFlag = true;
			++size;
		}
		else {
			// 중복허용 안함 > 값을 갱신한다.
			auto cur = getListPosition(table[index], key);
			cur->value = value;
		}
		// for (auto node : table[index]) cout << index<<" "<<node.key << " " <<node.value << endl;
		// cout << endl;
	}

	bool containsKey(const K& key) const noexcept {
		if (isEmpty()) return false;
		int index = hash(key);
		if (table[index].empty()) return false;
		for (auto node : table[index])
			if (node.key == key) return true;
		return false;
	}

	V get(const K& key) const {
		if (isEmpty()) throw std::runtime_error("HashMap: get. empty");
		int index = hash(key);
		for (auto node : table[index])
			if (node.key == key) return node.value;
		throw std::runtime_error("HashMap: get, key does not exists");
	}

	void remove(const K& key) noexcept {
		if (isEmpty()) return;
		int index = hash(key);
		if (table[index].empty()) return;
		auto cur = getListPosition(table[index], key);
		if (cur != table[index].end()) {
			table[index].erase(cur);
			--size;
		}
	}

	vector<Entry<K, V>> getEntrySet() {
		vector<Entry<K, V>> list;
		for (int i = 0; i < capacity; i++) {
			if (table[i].size() != 0)
				for (auto node : table[i]) list.emplace_back(node.key, node.value);
		}
		return list;
	}

	set<K> getKeySet() const noexcept {
		set<K> set;
		for (int i = 0; i < capacity; i++) {
			if (table[i].size() != 0)
				for (auto node : table[i]) set.insert(node.key);
		}
		return set;
	}

	set<V> getValueSet() const noexcept {
		set<V> set;
		for (int i = 0; i < capacity; i++) {
			if (table[i].size() != 0)
				for (auto node : table[i]) set.insert(node.value);
		}
		return set;
	}


private:
	// 값이 있는 위치 반환
	auto getListPosition(List& L, const K& key) {
		auto cur = L.begin();
		while (cur != L.end()) {
			if (cur->key == key) return cur;
			++cur;
		}
		return cur;
	}

	bool needMoreSpace() const noexcept {
		return capacityFlag || ((double)size / capacity > 0.7);
	}

	void increaseCapacity() noexcept {
		vector<Entry<K, V>> list = getEntrySet();
		clear();
		capacity = capacity * 2 + 1;
		List* temp = new List[capacity]();
		for (auto node : list) {
			int index = hash(node.key);
			temp[index].emplace_front(node.key, node.value);
		}
		table = temp;
		capacityFlag = false;
		size = list.size();
	}

	int hash(const K& key) const noexcept {
		// size_t 크기의 값을 리턴하고 이 값은 hash value이다.
		// () 안에 들어오는 값들에 대해서 서로 다른 값이면 hashvalue가 같을 확률은 매우 작다.
		auto hashvalue = std::hash<K>()(key);
		return hashvalue % capacity;
		//return hashInteger(hashvalue);
	}
	// folding


	/*
	int hashInteger(unsigned long val) const noexcept {
		int length = sizeof(val);
		unsigned char* p = reinterpret_cast<unsigned char*>(&val);
		int result{ 0 };
		for (int i = 0; i < length / 2; i++) {
			result ^= (p[i] ^ p[length - 1 - i]);
		}
		return result % capacity;
	}*/
};
#endif /* HASHMAP_H_ */
