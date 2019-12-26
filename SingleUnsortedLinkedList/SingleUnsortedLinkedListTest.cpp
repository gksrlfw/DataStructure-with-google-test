
#include "pch.h"
#include <string>
#include "gtest/gtest.h"

TEST(SingleUnsortedLinkedList_WithDuplicate_Int_WithTail, listEmptyInitializationTest)
{
	SingleUnsortedLinkedList list{};
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Int_WithTail, PushAndPopFrontTest)
{
	SingleUnsortedLinkedList list;
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

TEST(SingleUnsortedLinkedList_WithDuplicate_Int_WithTail, PushAndPopBackTest)
{
	SingleUnsortedLinkedList list;
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

TEST(SingleUnsortedLinkedList_WithDuplicate_Int_WithTail, listInitializationTest)
{
	// requires pushBack, popFront
	SingleUnsortedLinkedList list1{ 3,5,7 };
	std::string output = "";
	while (!list1.isEmpty())
		output += std::to_string(list1.popFront()) + ",";
	ASSERT_EQ(output, "3,5,7,");

	SingleUnsortedLinkedList list2{ 1,2,3,4,5,6,7,8,9,10, };
	output = "";
	while (!list2.isEmpty())
		output += std::to_string(list2.popFront()) + ",";
	ASSERT_EQ(output, "1,2,3,4,5,6,7,8,9,10,");
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Int_WithTail, findTest) {
	SingleUnsortedLinkedList list{ 3,3,5,7,9 };
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}


TEST(SingleUnsortedLinkedList_WithDuplicate_Int_WithTail, removeFirstTest) {
	SingleUnsortedLinkedList list;
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

TEST(SingleUnsortedLinkedList_WithDuplicate_Int_WithTail, removeAllTest) {
	SingleUnsortedLinkedList list;
	list.pushFront(3);
	list.pushFront(5);
	list.pushFront(7);
	list.pushFront(3);
	list.removeAll(3);
	ASSERT_EQ(list.getSize(), 2);
	list.removeFirst(7);
	ASSERT_EQ(list.getSize(), 1);
	ASSERT_EQ(5, list.popFront());
	ASSERT_TRUE(list.isEmpty());
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Int_WithTail, iteratorTest) {
	SingleUnsortedLinkedList list;
	list.pushFront(3);
	list.pushFront(5);
	list.pushFront(7);
	std::string output = "";
	for (auto i : list)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "7,5,3,");
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Int_WithTail, IndexOperator) {
	SingleUnsortedLinkedList list;
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


SingleUnsortedLinkedList foo() {
	SingleUnsortedLinkedList list{ 1,2,3,4,5 };
	return list;
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Int_WithTail, Big5)
{
	SingleUnsortedLinkedList list1{ 1,2,3,4,5 };
	SingleUnsortedLinkedList list2{ 6,7,8,9,10 };
	SingleUnsortedLinkedList list3;
	SingleUnsortedLinkedList list4(list2);
	list3 = list1;
	for (int i = 0; i < list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	for (int i = 0; i < list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list2 = foo();
	for (int i = 0; i < list1.getSize(); i++)
		ASSERT_EQ(list1[i], list2[i]);
	list4.pushBack(11);
	ASSERT_EQ(list4.peekBack(), 11);
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Int_WithTail, reverse)
{
	SingleUnsortedLinkedList list{ 1,2,3,4,5 };
	list.reverse();
	std::string output = "";
	for (auto i : list)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "5,4,3,2,1,");
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Int_WithTail, middle)
{
	SingleUnsortedLinkedList list1{ 1,2,3,4,5 };
	SingleUnsortedLinkedList list2{ 1,2,3,4,5,6 };
	ASSERT_EQ(list1.middle(), 3);
	ASSERT_EQ(list2.middle(), 4);
}

TEST(SingleUnsortedLinkedList_WithDuplicate_Int_WithTail, getNthFromBack)
{
	SingleUnsortedLinkedList list{ 1,2,3,4,5, };
	ASSERT_EQ(list.getNthFromBack(0), 5);
	ASSERT_EQ(list.getNthFromBack(1), 4);
	ASSERT_EQ(list.getNthFromBack(2), 3);
	ASSERT_EQ(list.getNthFromBack(3), 2);
	ASSERT_EQ(list.getNthFromBack(4), 1);
}

