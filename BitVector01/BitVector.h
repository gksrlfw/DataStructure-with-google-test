// Bitvecor�� �̿��ϸ� ���� �������� ������ ���翩�� Ȯ���� �� �ִ�.
#ifndef BITVECTOR_H_
#define BITVECTOR_H_
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <cstdint>

using Byte = uint8_t;	
using Long = uint64_t;

class BitVector {
public:
	const Long size;
	const Long length;
	// bitMask[i]�� 1 ����Ʈ�� i��° ��Ʈ�� 1�� ����Ʈ ��
	// 100000~ , 0100~, 001000~ �̷������̴�.
	const Byte bitMasks[8] = {
		(Byte)128, (Byte)64, (Byte)32, (Byte)16, (Byte)8, (Byte)4, (Byte)2, (Byte)1,
	};
private:
	/*
	 *  ��Ʈ ����: 0000 0000 0000 0000
	 *  ����    : 0123 4567 89
	 *  ��) ���� 10: 0000 1010
	 *  byteIndex: 10/8 = 0x1010>>3 = 0x0001 = 1			����Ʈ�� ������ 8 > >> 3�� �ϸ�� 
	 *  bitIndex:  10%8 = 0x1010 & 0x0111 = 0x0010 = 2		��Ʈ �ε����� ��� 8 > & 0x0111 �ϸ�� 
	 *  bitMask = bitMast[2] = 32 = 0010 0000
	 */

	 // vector[0]:0~7, vector[1]:8~15 > vector
	 // 0000 0000 0000
	Byte* vector = nullptr;
public:
	explicit BitVector(unsigned int size = 64) :
		size{ size }, length{ size / 8 }, vector{ new Byte[length]{} }{}
	virtual ~BitVector() {
		delete[] vector;
	}
	BitVector(const BitVector& other) :
		size{ other.size }, length{ size / 8 }, vector{ new Byte[length]{} }{
		std::copy(other.vector, other.vector + size, vector);
	}
	BitVector(BitVector&& tmp) :
		size{ tmp.size }, length{ size / 8 }, vector{ tmp.vector }{
		tmp.vector = nullptr;
	}
	const BitVector& operator=(const BitVector& other) {
		if (size != other.size) throw std::runtime_error("");
		std::copy(other.vector, other.vector + size, vector);
		return *this;
	}
	const BitVector& operator=(BitVector&& tmp) {
		if (size != tmp.size) throw std::runtime_error("");
		vector = tmp.vector;
		tmp.vector = nullptr;
		return *this;
	}

	// Ư�� ��Ʈ�� 1�� ���� : OR
	// vector[index >> 3]�� bitMasks[index & 0x07]�� ����
	void set(Long index) {
		Long byteIndex = getByteNumber(index);
		// vector[byteIndex] = bitMasks[index & 0x07];
		Byte bitmask = 0x80 >> (index & 0x07);
		vector[byteIndex] |= bitmask;
	}

	// Ư�� ��Ʈ�� 0���� ���� : AND
	void unSet(Long index) {
		Long byteIndex = getByteNumber(index);
		// Byte unMask = bitMasks[index & 0x07] ^ (Byte)0xFF;
		Byte unMask = 0x80 >> (index & 0x07) ^ (Byte)0xFF;
		vector[byteIndex] &= unMask;
	}

	// Ư�� ��Ʈ�� ������ : XOR
	void flip(Long index) {
		Long byteIndex = getByteNumber(index);
		// vector[byteIndex] ^= bitMasks[index & 0x07];
		Byte bitmask = 0x80 >> (index & 0x07);
		vector[byteIndex]^=bitmask;
	}

	bool get(Long index) const {
		Long byteIndex = getByteNumber(index);
		// Byte computedMask = vector[byteIndex] & bitMasks[index & 0x07]; �� ���� �����ϸ� 1, �ٸ��� 0
		Byte bitmask = 0x80 >> (index & 0x07);
		Byte computedMask = vector[byteIndex] & bitmask;
		// return computedMask != (Byte)0;	// 0�� �ƴϸ� true
		return computedMask == bitmask;
		// return computedMask == vector[byteIndex];	�̰� �� �ȵ���???
	}
	Long getByteNumber(Long index)const {
		if (index >= size) throw std::range_error("���� ���� �ʰ�");
		index = index >> 3;
		return index;
	}
};
#endif /* BITVECTOR_H_ */
