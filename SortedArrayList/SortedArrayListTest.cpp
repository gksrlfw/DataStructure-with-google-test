

#include "pch.h"
#include "gtest/gtest.h"
#include <string>


TEST(SortedArrayListWithDuplicate, listEmptyInitializationTest)
{
	SortedArrayList list{};
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(SortedArrayListWithDuplicate, addWithPopBackTest)
{
	SortedArrayList list;
	list.add(5);
	list.add(3);
	list.add(10);
	list.add(8);
	list.add(4);
	ASSERT_EQ(list.getSize(), 5);
	std::string output = "";
	while (!list.isEmpty())
		output += std::to_string(list.popBack()) + ",";
	ASSERT_EQ(output, "10,8,5,4,3,");
}

TEST(SortedArrayListWithDuplicate, addWithPopFrontTest)
{
	SortedArrayList list;
	list.add(5);
	list.add(3);
	list.add(10);
	list.add(8);
	list.add(4);
	ASSERT_EQ(list.getSize(), 5);
	std::string output = "";
	while (!list.isEmpty())
		output += std::to_string(list.popFront()) + ",";
	ASSERT_EQ(output, "3,4,5,8,10,");
}

TEST(SortedArrayListWithDuplicate, listInitializationTest)
{
	// requires pushBack, popFront
	SortedArrayList list1{ 3,5,7 };
	std::string output = "";
	while (!list1.isEmpty())
		output += std::to_string(list1.popFront()) + ",";
	ASSERT_EQ(output, "3,5,7,");

	SortedArrayList list2{ 1,2,3,4,5,6,7,8,9,10,11 };
	output = "";
	while (!list2.isEmpty())
		output += std::to_string(list2.popBack()) + ",";
	ASSERT_EQ(output, "10,9,8,7,6,5,4,3,2,1,");
}

TEST(SortedArrayListWithDuplicate, findTest) {
	SortedArrayList list{ 3,3,5,7,9 };
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(SortedArrayListWithDuplicate, removeFirstTest) {
	SortedArrayList list;
	list.add(7);
	list.add(5);
	list.add(3);
	list.removeFirst(3);
	ASSERT_EQ(list.getSize(), 2);
	list.removeFirst(7);
	ASSERT_EQ(list.getSize(), 1);
	ASSERT_EQ(5, list.popFront());
	ASSERT_TRUE(list.isEmpty());
}

TEST(SortedArrayListWithDuplicate, removeAllTest) {
	SortedArrayList list{ 1,3,1,3,4,5,4,4,6,6 };
	// 1,1,3,3,4,4,4,5,6,6
	list.removeAll(3); // 1,1,4,4,4,5,6,6
	ASSERT_EQ(list.getSize(), 8);
	list.removeAll(1); // 4,4,4,5,6,6
	ASSERT_EQ(list.getSize(), 6);
	list.removeFirst(5); // 4,4,4,6,6
	ASSERT_EQ(list.getSize(), 5);
	list.removeAll(6); // 4,4,4
	ASSERT_EQ(list.getSize(), 3);
	list.removeAll(4); //
	ASSERT_TRUE(list.isEmpty());
}

TEST(SortedArrayListWithDuplicate, iteratorTest) {
	SortedArrayList list;
	list.add(3);
	list.add(10);
	list.add(7);
	std::string output = "";
	for (auto i : list)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "3,7,10,");
}

TEST(SortedArrayListWithDuplicate, IndexOperator) {
	SortedArrayList list;
	list.add(7);
	list.add(3);
	ASSERT_EQ(list[1], 7);
	list.add(5);
	std::string output = "";
	for (auto i : list)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "3,5,7,");
}

TEST(SortedArrayListWithDuplicate, clearTest) {
	SortedArrayList list{ 1,3,1,1,3,4,5,4,4,6 };
	list.clear();
	list.add(4);
	ASSERT_EQ(list.getSize(), 1);
	ASSERT_EQ(4, list.popFront());
	ASSERT_TRUE(list.isEmpty());
}

SortedArrayList foo() {
	SortedArrayList list{ 1,2,3,4,5 };
	return list;
}

TEST(SortedArrayListWithDuplicate, Big5)
{
	SortedArrayList list1{ 1,2,3,4,5 };
	SortedArrayList list2{ 6,7,8,9,10 };
	SortedArrayList list3;
	SortedArrayList list4(list2);
	list3 = list1;
	for (int i = 0; i < list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	for (int i = 0; i < list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list2 = foo();
	for (int i = 0; i < list1.getSize(); i++)
		ASSERT_EQ(list1[i], list2[i]);
}
