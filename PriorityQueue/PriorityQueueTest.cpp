#include "pch.h"
#include "HeapSort.h"
#include "gtest/gtest.h"
#include <string>

TEST(PriorityQueue, enqueue_dequeue_Test)
{
	PriorityQueue queue1;
	queue1.enqueue(3);
	queue1.enqueue(5);
	queue1.enqueue(7);
	queue1.enqueue(9);
	queue1.enqueue(11);
	ASSERT_EQ(5, queue1.getSize());
	std::string output = "";
	while (!queue1.isEmpty())
		output += std::to_string(queue1.dequeue()) + ",";
	ASSERT_EQ(output, "11,9,7,5,3,");

	PriorityQueue queue2;
	queue2.enqueue(3);
	queue2.enqueue(11);
	queue2.enqueue(5);
	queue2.enqueue(7);
	queue2.enqueue(13);
	ASSERT_EQ(5, queue2.getSize());
	output = "";
	while (!queue2.isEmpty())
		output += std::to_string(queue2.dequeue()) + ",";
	ASSERT_EQ(output, "13,11,7,5,3,");
}

TEST(PriorityQueue, InitializerTest)
{
	PriorityQueue queue1{ 3,5,7,9,11 };
	ASSERT_EQ(5, queue1.getSize());
	std::string output = "";
	while (!queue1.isEmpty())
		output += std::to_string(queue1.dequeue()) + ",";
	ASSERT_EQ(output, "11,9,7,5,3,");

	PriorityQueue queue2{ 11,2,8,5,9 };
	ASSERT_EQ(5, queue2.getSize());
	output = "";
	while (!queue2.isEmpty())
		output += std::to_string(queue2.dequeue()) + ",";
	ASSERT_EQ(output, "11,9,8,5,2,");
}

TEST(HeapSort, Test) {
	
	int list[9]{ 4,7,0,3,9,17,19,6,2 };
	heapSort(list, 9);
	std::string output = "";
	for (auto n : list)
		output += std::to_string(n) + ",";
	//ASSERT_EQ(output,"19,9,17,6,7,4,0,3,2,");
	ASSERT_EQ(output, "0,2,3,4,6,7,9,17,19,");
}