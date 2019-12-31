#include "pch.h"
#include "gtest/gtest.h"
#include <string>
#include <random>
std::random_device rd;
std::mt19937_64 mtRand(rd());

int getRandomInt(int n) {
	std::uniform_int_distribution<std::int64_t> dist(1, n);
	return dist(mtRand);
}


TEST(BitVectorTest, setTest)
{
	BitVector vector;
	ASSERT_EQ(vector.size, 64);
	ASSERT_EQ(vector.length, 8);
	vector.set(11);
	ASSERT_TRUE(vector.get(11));
	ASSERT_FALSE(vector.get(12));
	vector.set(63);
	ASSERT_TRUE(vector.get(63));
	ASSERT_FALSE(vector.get(62));
	for (int i = 0; i < 5; i++) {
		int x = getRandomInt(64);
		if (!vector.get(x)) {
			vector.set(x);
			ASSERT_TRUE(vector.get(x));
		}
	}
}

TEST(BitVectorTest, unSetTest)
{
	BitVector vector;
	ASSERT_EQ(vector.length, 8);
	vector.set(27);
	ASSERT_TRUE(vector.get(27));
	vector.unSet(27);
	ASSERT_FALSE(vector.get(27));
	for (int i = 0; i < 5; i++) {
		int x = getRandomInt(64);
		if (!vector.get(x)) {
			vector.set(x);
			ASSERT_TRUE(vector.get(x));
			vector.unSet(x);
			ASSERT_FALSE(vector.get(x));
		}
	}
}

TEST(BitVectorTest, flipTest)
{
	BitVector vector;
	for (int i = 0; i < 10; i++) {
		int x = getRandomInt(64);
		if (vector.get(x)) {
			vector.flip(x);
			ASSERT_FALSE(vector.get(x));
		}
		else {
			vector.flip(x);
			ASSERT_TRUE(vector.get(x));
		}
	}
}
