#include "pch.h"
#include "gtest/gtest.h"
#include <string>

TEST(HashTable_Chaining_Dynamic, addTest)
{
	HashTable hTable;
	hTable.add("apple");
	hTable.add("peach");
	hTable.add("orange");
	hTable.add("mango");
	hTable.add("grape");
	hTable.add("strawberry");
	hTable.add("banana");
	hTable.add("melon");
	hTable.add("kiwi");
	hTable.add("tomato");
	hTable.debugPrint();
	ASSERT_EQ(hTable.getSize(), 10);
	ASSERT_TRUE(hTable.contains("strawberry"));
	ASSERT_TRUE(hTable.contains("grape"));
	hTable.add("apple");
	ASSERT_EQ(hTable.getSize(), 10);
}

TEST(HashTable_Chaining_Dynamic, removeTest)
{
	HashTable hTable;
	hTable.add("apple");
	hTable.add("peach");
	hTable.add("orange");
	hTable.add("mango");
	hTable.add("grape");
	hTable.add("strawberry");
	hTable.add("banana");
	hTable.add("melon");
	hTable.add("kiwi");
	hTable.add("tomato");
	ASSERT_EQ(hTable.getSize(), 10);
	hTable.debugPrint();
	hTable.remove("melon");
	hTable.remove("strawberry");
	hTable.remove("grape");
	hTable.debugPrint();
	ASSERT_EQ(hTable.getSize(), 7);
	ASSERT_FALSE(hTable.contains("strawberry"));
	ASSERT_FALSE(hTable.contains("grape"));
	ASSERT_FALSE(hTable.contains("melon"));
	ASSERT_TRUE(hTable.contains("mango"));
}
/*
TEST(HashTable_Chaining_Dynamic, iteratorTest)
{
	HashTable hTable;
	std::set<std::string> fruits;
	hTable.add("apple");
	fruits.insert("apple");
	hTable.add("peach");
	fruits.insert("peach");
	hTable.add("grape");
	fruits.insert("grape");
	hTable.add("orange");
	fruits.insert("orange");
	hTable.add("mango");
	fruits.insert("mango");
	hTable.add("coconut");
	fruits.insert("coconut");
	hTable.add("strawberry");
	fruits.insert("strawberry");

	for (std::string fruit : hTable) {
		ASSERT_EQ(1, fruits.count(fruit));
	}
}
*/