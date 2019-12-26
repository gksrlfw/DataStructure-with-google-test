
#include "pch.h"
#include <string>
#include "gtest/gtest.h"

TEST(SingleSortedLinkedList_WithDuplicate_Int_Tail, listEmptyInitializationTest)
{
	SingleSortedLinkedList list{};
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(SingleSortedLinkedList_WithDuplicate_Int_Tail, AddandPopFrontTest)
{
	SingleSortedLinkedList list;
	list.add(3);
	list.add(5);
	list.add(7);
	list.add(3);
	list.add(7);
	ASSERT_EQ(list.getSize(), 5);
	std::string output = "";
	while (!list.isEmpty())
		output += std::to_string(list.popFront()) + ",";
	ASSERT_EQ(output, "3,3,5,7,7,");
}

TEST(SingleSortedLinkedList_WithDuplicate_Int_Tail, AddandPopBackTest)
{
	SingleSortedLinkedList list;
	list.add(3);
	list.add(5);
	list.add(7);
	list.add(3);
	ASSERT_EQ(list.getSize(), 4);
	std::string output = "";
	while (!list.isEmpty())
		output += std::to_string(list.popBack()) + ",";
	ASSERT_EQ(output, "7,5,3,3,");
}

TEST(SingleSortedLinkedList_WithDuplicate_Int_Tail, listInitializationTest)
{
	SingleSortedLinkedList list1{ 3,5,7 };
	std::string output = "";
	while (!list1.isEmpty())
		output += std::to_string(list1.popFront()) + ",";
	ASSERT_EQ(output, "3,5,7,");

	SingleSortedLinkedList list2{ 1,2,6,7,3,8,9,10,4,5, };
	output = "";
	while (!list2.isEmpty())
		output += std::to_string(list2.popFront()) + ",";
	ASSERT_EQ(output, "1,2,3,4,5,6,7,8,9,10,");
}

TEST(SingleSortedLinkedList_WithDuplicate_Int_Tail, findTest) {
	SingleSortedLinkedList list{ 3,3,5,7,9 };
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(SingleSortedLinkedList_WithDuplicate_Int_Tail, removeFirstTest) {
	SingleSortedLinkedList list;
	list.add(3);
	list.add(5);
	list.add(7);
	list.removeFirst(3);
	ASSERT_EQ(list.getSize(), 2);
	list.removeFirst(7);
	ASSERT_EQ(list.getSize(), 1);
	list.removeFirst(5);
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
}

TEST(SingleSortedLinkedList_WithDuplicate_Int_Tail, removeAllTest) {
	SingleSortedLinkedList list;
	list.add(3);
	list.add(5);
	list.add(7);
	list.add(3);
	list.removeAll(3);
	ASSERT_EQ(list.getSize(), 2);
	list.removeFirst(7);
	ASSERT_EQ(list.getSize(), 1);
	ASSERT_EQ(5, list.popFront());
	ASSERT_TRUE(list.isEmpty());

	SingleSortedLinkedList list1{ 3,3,3,3 };
	list1.removeAll(3);
	ASSERT_EQ(list1.getSize(), 0);
	ASSERT_TRUE(list1.isEmpty());
}

TEST(SingleSortedLinkedList_WithDuplicate_Int_Tail, iteratorTest) {
	SingleSortedLinkedList list;
	list.add(3);
	list.add(5);
	list.add(7);
	std::string output = "";
	for (auto i : list)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "3,5,7,");
}

TEST(SingleSortedLinkedList_WithDuplicate_Int_Tail, IndexOperator) {
	SingleSortedLinkedList list;
	list.add(5);
	list.add(3);
	ASSERT_EQ(list[0], 3);
	ASSERT_EQ(list[1], 5);
	list.add(7);
	ASSERT_EQ(list[2], 7);
	std::string output = "";
	for (auto i : list)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "3,5,7,");
}


SingleSortedLinkedList foo() {
	SingleSortedLinkedList list{ 1,2,3,4,5 };
	return list;
}

TEST(SingleSortedLinkedList_WithDuplicate_Int_Tail, Big5)
{
	SingleSortedLinkedList list1{ 1,2,3,4,5 };
	SingleSortedLinkedList list2{ 6,7,8,9,10 };
	SingleSortedLinkedList list3;
	SingleSortedLinkedList list4(list2);
	list3 = list1;
	for (int i = 0; i < list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	for (int i = 0; i < list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list2 = foo();
	for (int i = 0; i < list1.getSize(); i++)
		ASSERT_EQ(list1[i], list2[i]);
}
