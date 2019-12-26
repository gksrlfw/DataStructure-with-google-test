
#include "pch.h"
#include <string>
#include <iostream>
#include "gtest/gtest.h"

TEST(DoubleUnsortedLinkedList_WithDuplicate_Int_NoTail, listEmptyInitializationTest)
{
	DoubleUnsortedLinkedList list{};
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_Int_NoTail, PushAndPopFrontTest)
{
	DoubleUnsortedLinkedList list;
	list.pushFront(3);
	list.pushFront(5);
	list.pushFront(7);
	list.pushFront(3);
	list.pushFront(7);
	ASSERT_EQ(list.getSize(), 5);
	std::string output = "";
	while (!list.isEmpty())
		output += std::to_string(list.popFront()) + ",";
	ASSERT_EQ(output, "7,3,7,5,3,");
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_Int_NoTail, PushAndPopBackTest)
{
	DoubleUnsortedLinkedList list;
	list.pushBack(3);
	list.pushBack(5);
	list.pushBack(7);
	list.pushBack(3);
	ASSERT_EQ(list.getSize(), 4);
	std::string output = "";
	while (!list.isEmpty())
		output += std::to_string(list.popBack()) + ",";
	ASSERT_EQ(output, "3,7,5,3,");
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_Int_NoTail, listInitializationTest)
{
	// requires pushBack, popFront
	DoubleUnsortedLinkedList list1{ 3,5,7 };
	std::string output = "";
	while (!list1.isEmpty())
		output += std::to_string(list1.popFront()) + ",";
	ASSERT_EQ(output, "3,5,7,");

	DoubleUnsortedLinkedList list2{ 1,2,3,4,5,6,7,8,9,10, };
	output = "";
	while (!list2.isEmpty())
		output += std::to_string(list2.popFront()) + ",";
	ASSERT_EQ(output, "1,2,3,4,5,6,7,8,9,10,");
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_Int_NoTail, findTest) {
	DoubleUnsortedLinkedList list{ 3,3,5,7,9 };
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_Int_NoTail, removeFirstTest) {
	DoubleUnsortedLinkedList list;
	list.pushFront(3);
	list.pushFront(5);
	list.pushFront(7);
	list.removeFirst(3);
	ASSERT_EQ(list.getSize(), 2);
	list.removeFirst(7);
	ASSERT_EQ(list.getSize(), 1);
	ASSERT_EQ(5, list.popFront());
	ASSERT_TRUE(list.isEmpty());
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_Int_NoTail, removeAllTest) {
	DoubleUnsortedLinkedList list1;
	list1.pushFront(3);
	list1.pushFront(5);
	list1.pushFront(7);
	list1.pushFront(3);
	list1.removeAll(3);
	ASSERT_EQ(list1.getSize(), 2);
	list1.removeFirst(7);
	ASSERT_EQ(list1.getSize(), 1);
	ASSERT_EQ(5, list1.popFront());
	ASSERT_TRUE(list1.isEmpty());

	DoubleUnsortedLinkedList list2{ 5,5,5,5,5 };
	list2.removeAll(5);
	ASSERT_EQ(list2.getSize(), 0);
	ASSERT_TRUE(list2.isEmpty());

	DoubleUnsortedLinkedList list3{ 3,5,5,5,7,7,5,5,3,3 };
	list3.removeAll(5);
	ASSERT_EQ(list3.getSize(), 5);
	list3.removeAll(7);
	ASSERT_EQ(list3.getSize(), 3);
	list3.removeAll(3);
	ASSERT_TRUE(list3.isEmpty());

}

TEST(DoubleUnsortedLinkedList_WithDuplicate_Int_NoTail, iteratorTest) {
	DoubleUnsortedLinkedList list;
	list.pushFront(3);
	list.pushFront(5);
	list.pushFront(7);
	std::string output = "";
	for (auto i : list)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "7,5,3,");
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_Int_NoTail, IndexOperator) {
	DoubleUnsortedLinkedList list;
	list.pushFront(3);
	list.pushFront(5);
	ASSERT_EQ(list[1], 3);
	list.pushFront(7);
	list[0] = 4;
	std::string output = "";
	for (auto i : list)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "4,5,3,");
}


DoubleUnsortedLinkedList foo() {
	DoubleUnsortedLinkedList list{ 1,2,3,4,5 };
	return list;
}

TEST(DoubleUnsortedLinkedList_WithDuplicate_Int_NoTail, Big5)
{
	DoubleUnsortedLinkedList list1{ 1,2,3,4,5 };
	DoubleUnsortedLinkedList list2{ 6,7,8,9,10 };
	DoubleUnsortedLinkedList list3;
	DoubleUnsortedLinkedList list4(list2);
	list3 = list1;
	for (int i = 0; i < list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	for (int i = 0; i < list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list2 = foo();
	for (int i = 0; i < list1.getSize(); i++)
		ASSERT_EQ(list1[i], list2[i]);
}
