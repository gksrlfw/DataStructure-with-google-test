#include "pch.h"
#include "gtest/gtest.h"
#include <string>


TEST(UnsortedDynamicArrayListWithDuplicate, listEmptyInitializationTest)
{
	UnsortedArrayList list{};
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(UnsortedDynamicArrayListWithDuplicate, PushAndPopBackTest)
{
	UnsortedArrayList list;
	list.pushBack(3);
	list.pushBack(5);
	list.pushBack(7);
	list.pushBack(3);
	list.pushBack(4);
	list.pushBack(2);
	list.pushBack(1);
	ASSERT_EQ(list.getSize(), 7);
	std::string output = "";
	while (!list.isEmpty())
		output += std::to_string(list.popBack()) + ",";
	ASSERT_EQ(output, "1,2,4,3,7,5,3,");
}

TEST(UnsortedDynamicArrayListWithDuplicate, PushAndPopFrontTest)
{
	UnsortedArrayList list;
	list.pushFront(3);
	list.pushFront(5);
	list.pushFront(7);
	list.pushFront(3);
	list.pushFront(7);
	list.pushFront(2);
	list.pushFront(4);
	ASSERT_EQ(list.getSize(), 7);
	std::string output = "";
	while (!list.isEmpty())
		output += std::to_string(list.popFront()) + ",";
	ASSERT_EQ(output, "4,2,7,3,7,5,3,");
}

TEST(UnsortedDynamicArrayListWithDuplicate, listInitializationTest)
{
	// requires pushBack, popFront
	UnsortedArrayList list1{ 3,5,7 };
	std::string output = "";
	while (!list1.isEmpty())
		output += std::to_string(list1.popFront()) + ",";
	ASSERT_EQ(output, "3,7,5,");

	UnsortedArrayList list2{ 1,2,3,4,5,6,7,8,9,10,11 };
	output = "";
	while (!list2.isEmpty())
		output += std::to_string(list2.popFront()) + ",";
	ASSERT_EQ(output, "1,11,10,9,8,7,6,5,4,3,2,");
}

TEST(UnsortedDynamicArrayListWithDuplicate, findTest) {
	UnsortedArrayList list{ 3,3,5,7,9 };
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(UnsortedDynamicArrayListWithDuplicate, removeFirstTest) {
	UnsortedArrayList list;
	list.pushBack(3);
	list.pushBack(5);
	list.pushBack(7);
	list.removeFirst(3);
	ASSERT_EQ(list.getSize(), 2);
	list.removeFirst(7);
	ASSERT_EQ(list.getSize(), 1);
	ASSERT_EQ(5, list.popFront());
	ASSERT_TRUE(list.isEmpty());
}

TEST(UnsortedDynamicArrayListWithDuplicate, removeAllTest) {
	UnsortedArrayList list{ 1,3,1,1,3,4,5,4,4,6 };
	list.removeAll(3);
	ASSERT_EQ(list.getSize(), 8);
	list.removeAll(1);
	ASSERT_EQ(list.getSize(), 5);
	list.removeFirst(5);
	ASSERT_EQ(list.getSize(), 4);
	list.removeAll(4);
	ASSERT_EQ(list.getSize(), 1);
	ASSERT_EQ(6, list.popFront());
	ASSERT_TRUE(list.isEmpty());
}

TEST(UnsortedDynamicArrayListWithDuplicate, iteratorTest) {
	UnsortedArrayList list;
	list.pushBack(3);
	list.pushBack(5);
	list.pushBack(7);
	std::string output = "";
	for (auto i : list)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "3,5,7,");
}

TEST(UnsortedDynamicArrayListWithDuplicate, IndexOperator) {
	UnsortedArrayList list;
	list.pushBack(3);
	list.pushBack(5);
	ASSERT_EQ(list[1], 5);
	list.pushBack(7);
	list[0] = 4;
	std::string output = "";
	for (auto i : list)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "4,5,7,");
}

TEST(UnsortedDynamicArrayListWithDuplicate, clearTest) {
	UnsortedArrayList list{ 1,3,1,1,3,4,5,4,4,6 };
	list.clear();
	list.pushBack(4);
	ASSERT_EQ(list.getSize(), 1);
	ASSERT_EQ(4, list.popFront());
	ASSERT_TRUE(list.isEmpty());
}


UnsortedArrayList foo() {
	UnsortedArrayList list{ 1,2,3,4,5 };
	return list;
}

TEST(UnsortedDynamicArrayListWithDuplicate, Big5)
{
	UnsortedArrayList list1{ 1,2,3,4,5 };
	UnsortedArrayList list2{ 6,7,8,9,10 };
	UnsortedArrayList list3;
	UnsortedArrayList list4(list2);
	list3 = list1;
	for (int i = 0; i < list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	for (int i = 0; i < list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list2 = foo();
	for (int i = 0; i < list1.getSize(); i++)
		ASSERT_EQ(list1[i], list2[i]);
}
