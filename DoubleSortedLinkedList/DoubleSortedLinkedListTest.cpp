#include "pch.h"
#include <string>
#include "gtest/gtest.h"

TEST(DoubleSortedLinkedList_WithDuplicate_Int_Tail, listEmptyInitializationTest)
{
	DoubleSortedLinkedList list{};
	ASSERT_EQ(list.getSize(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(DoubleSortedLinkedList_WithDuplicate_Int_Tail, PushAndPopFrontTest)
{
	DoubleSortedLinkedList list;
	list.add(3);
	list.add(5);
	list.add(11);
	list.add(7);
	list.add(9);
	ASSERT_EQ(list.getSize(), 5);
	std::string output = "";
	while (!list.isEmpty())
		output += std::to_string(list.popFront()) + ",";
	ASSERT_EQ(output, "3,5,7,9,11,");

	list.add(3);
	list.add(5);
	list.add(11);
	list.add(7);
	list.add(9);
	ASSERT_EQ(list.getSize(), 5);
	output = "";
	while (!list.isEmpty())
		output += std::to_string(list.popBack()) + ",";
	ASSERT_EQ(output, "11,9,7,5,3,");
}

TEST(DoubleSortedLinkedList_WithDuplicate_Int_Tail, listInitializationTest)
{
	// requires pushBack, popFront
	DoubleSortedLinkedList list1{ 3,5,7 };
	std::string output = "";
	while (!list1.isEmpty())
		output += std::to_string(list1.popFront()) + ",";
	ASSERT_EQ(output, "3,5,7,");

	DoubleSortedLinkedList list2{ 1,2,3,4,5,6,7,8,9,10 };
	output = "";
	while (!list2.isEmpty())
		output += std::to_string(list2.popFront()) + ",";
	ASSERT_EQ(output, "1,2,3,4,5,6,7,8,9,10,");

	DoubleSortedLinkedList list3{ 4,4,4,4,4 };
	output = "";
	while (!list3.isEmpty())
		output += std::to_string(list3.popFront()) + ",";
	ASSERT_EQ(output, "4,4,4,4,4,");
}

TEST(DoubleSortedLinkedList_WithDuplicate_Int_Tail, findTest) {
	DoubleSortedLinkedList list{ 3,3,5,7,9 };
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(DoubleSortedLinkedList_WithDuplicate_Int_Tail, removeFirstTest) {
	DoubleSortedLinkedList list;
	list.add(3);
	list.add(5);
	list.add(7);
	list.removeFirst(3);
	ASSERT_EQ(list.getSize(), 2);
	list.removeFirst(7);
	ASSERT_EQ(list.getSize(), 1);
	ASSERT_EQ(5, list.popFront());
	ASSERT_TRUE(list.isEmpty());
}

TEST(DoubleSortedLinkedList_WithDuplicate_Int_Tail, removeAllTest) {
	DoubleSortedLinkedList list1;
	list1.add(3);
	list1.add(5);
	list1.add(7);
	list1.add(3);
	list1.removeAll(3);
	ASSERT_EQ(list1.getSize(), 2);
	list1.removeFirst(7);
	ASSERT_EQ(list1.getSize(), 1);
	ASSERT_EQ(5, list1.popFront());
	ASSERT_TRUE(list1.isEmpty());

	DoubleSortedLinkedList list2{ 5,5,5,5,5 };
	list2.removeAll(5);
	ASSERT_EQ(list2.getSize(), 0);
	ASSERT_TRUE(list2.isEmpty());

	DoubleSortedLinkedList list3{ 3,3,3,5,5,5,5,5,7,7 };
	list3.removeAll(5);
	ASSERT_EQ(list3.getSize(), 5);
	list3.removeAll(7);
	ASSERT_EQ(list3.getSize(), 3);
	list3.removeAll(3);
	ASSERT_TRUE(list3.isEmpty());
}

TEST(DoubleSortedLinkedList_WithDuplicate_Int_Tail, iteratorTest) {
	DoubleSortedLinkedList list;
	list.add(3);
	list.add(5);
	list.add(7);
	list.add(3);
	std::string output = "";
	for (auto i : list)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "3,3,5,7,");
}

TEST(DoubleSortedLinkedList_WithDuplicate_Int_Tail, IndexOperator) {
	DoubleSortedLinkedList list;
	list.add(3);
	list.add(5);
	ASSERT_EQ(list[1], 5);
	list.add(7);
	std::string output = "";
	for (auto i : list)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "3,5,7,");
}


DoubleSortedLinkedList foo() {
	DoubleSortedLinkedList list{ 1,2,3,4,5 };
	return list;
}

TEST(DoubleSortedLinkedList_WithDuplicate_Int_Tail, Big5)
{
	DoubleSortedLinkedList list1{ 1,2,3,4,5 };
	DoubleSortedLinkedList list2{ 6,7,8,9,10 };
	DoubleSortedLinkedList list3;
	DoubleSortedLinkedList list4(list2);
	list3 = list1;
	for (int i = 0; i < list1.getSize(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	for (int i = 0; i < list2.getSize(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list2 = foo();
	for (int i = 0; i < list1.getSize(); i++)
		ASSERT_EQ(list1[i], list2[i]);
}
