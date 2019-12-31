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
	ASSERT_EQ(vector.getSize(), 64);
	vector.set(11);
	ASSERT_TRUE(vector[11]);
	vector.set(63);
	ASSERT_TRUE(vector[63]);
	for (int i = 0; i < 5; i++) {
		int x = getRandomInt(64);
		if (!vector[x]) {
			vector.set(x);
			ASSERT_TRUE(vector[x]);
		}
	}
}

TEST(BitVectorTest, unSetTest)
{
	BitVector vector;
	vector.set(27);
	ASSERT_TRUE(vector[27]);
	vector.unSet(27);
	ASSERT_FALSE(vector[27]);
	for (int i = 0; i < 5; i++) {
		int x = getRandomInt(64);
		if (!vector[x]) {
			vector.set(x);
			ASSERT_TRUE(vector[x]);
			vector.unSet(x);
			ASSERT_FALSE(vector[x]);
		}
	}
}

TEST(BitVectorTest, flipTest)
{
	BitVector vector;
	for (int i = 0; i < 10; i++) {
		int x = getRandomInt(64);
		if (vector[x]) {
			vector.flip(x);
			ASSERT_FALSE(vector[x]);
		}
		else {
			vector.flip(x);
			ASSERT_TRUE(vector[x]);
		}
	}
}

TEST(BitVectorTest, unionTest)
{
	BitVector vector1{ 16 };
	BitVector vector2{ 16 };
	vector1.set(1);
	vector1.set(3);
	vector1.set(5);
	vector2.set(1);
	vector2.set(6);
	vector2.set(7);
	BitVector vector3{ 16 };
	vector3 = vector3.unionSet(vector1, vector2);
	ASSERT_TRUE(vector3[1]);
	ASSERT_TRUE(vector3[3]);
	ASSERT_TRUE(vector3[5]);
	ASSERT_TRUE(vector3[6]);
	ASSERT_TRUE(vector3[7]);
	ASSERT_FALSE(vector3[0]);
	ASSERT_FALSE(vector3[8]);
}

TEST(BitVectorTest, differenceTest)
{
	BitVector vector1{ 16 };
	BitVector vector2{ 16 };
	vector1.set(1);
	vector1.set(3);
	vector1.set(5);
	vector2.set(1);
	vector2.set(6);
	vector2.set(7);
	BitVector vector3{ 16 };
	vector3 = vector3.differenceSet(vector1, vector2);
	ASSERT_FALSE(vector3[1]);
	ASSERT_TRUE(vector3[3]);
	ASSERT_TRUE(vector3[5]);
	ASSERT_FALSE(vector3[6]);
	ASSERT_FALSE(vector3[7]);
	ASSERT_FALSE(vector3[0]);
	ASSERT_FALSE(vector3[8]);
}

TEST(BitVectorTest, intersectionTest)
{
	BitVector vector1{ 16 };
	BitVector vector2{ 16 };
	vector1.set(1);
	vector1.set(3);
	vector1.set(5);
	vector2.set(1);
	vector2.set(5);
	vector2.set(7);
	BitVector vector3{ 16 };
	vector3 = vector3.intersectionSet(vector1, vector2);
	ASSERT_TRUE(vector3[1]);
	ASSERT_FALSE(vector3[3]);
	ASSERT_TRUE(vector3[5]);
	ASSERT_FALSE(vector3[6]);
	ASSERT_FALSE(vector3[7]);
	ASSERT_FALSE(vector3[0]);
	ASSERT_FALSE(vector3[8]);
}
