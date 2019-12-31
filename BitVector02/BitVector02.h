#ifndef BITVECTOR_H_
#define BITVECTOR_H_
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdint>

using Long = uint64_t;

class BitVector {
	std::vector<bool> vector;
	Long size;
public:
	explicit BitVector(Long size = 64) : size{ size } {
		vector.resize(size, false);
	}
	bool operator[](Long index) const {
		if (index < size) return vector[index];
		else throw std::range_error("ERROR: [] const");
	}
	virtual ~BitVector() = default;
	int getSize() const {
		return size;
	}

	void set(Long index) {	vector[index] = true; }
	void unSet(Long index) { vector[index] = false; }
	void flip(Long index) { vector[index] = !vector[index]; }

	BitVector unionSet(const BitVector& a, const BitVector& b) {
		if (a.size != b.size) throw std::runtime_error("");
		BitVector temp(a.size);
		for (int i = 0; i < temp.vector.size(); i++)
			temp.vector[i] = a.vector[i] || b.vector[i];
		return temp;
	}
	BitVector differenceSet(const BitVector& a, const BitVector& b) {
		if (a.size != b.size) throw std::runtime_error("");
		BitVector temp(a.size);
		for (int i = 0; i < temp.vector.size(); i++)
			temp.vector[i] = (a.vector[i] && !b.vector[i]);
		return temp;
	}
	BitVector intersectionSet(const BitVector& a, const BitVector& b) {
		if (a.size != b.size) throw std::runtime_error("");
		BitVector temp(a.size);
		for (int i = 0; i < temp.vector.size(); i++)
			temp.vector[i] = a.vector[i] && b.vector[i];
		return temp;
	}
};

#endif BITVECTOR_H_;

