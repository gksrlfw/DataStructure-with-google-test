#include "pch.h"
#include "gtest/gtest.h"
#include <string>
#include <set>

TEST(HashTable_LinearProbing, addTest)
{
	HashTable hTable;
	hTable.add("peach");
	hTable.add("grape");
	hTable.add("orange");
	hTable.add("mango");
	hTable.add("strawberry");
	hTable.add("banana");
	ASSERT_TRUE(hTable.contains("banana"));
	ASSERT_TRUE(hTable.contains("orange"));
	hTable.add("apple");
	ASSERT_EQ(hTable.getSize(), 7);
	//hTable.debugPrint();
}

TEST(HashTable_LinearProbing, removeTest)
{
	HashTable hTable;
	hTable.add("peach"); 	// 0
	hTable.add("grape"); 	// 13
	hTable.add("orange");	// 9
	hTable.add("mango");	// 13
	hTable.add("strawberry");	// 1
	hTable.add("banana");	// 3
	hTable.add("apple");	// 1
	hTable.add("melon");	// 0
	hTable.add("avocado");	// 11
	hTable.add("tomato");	// 11
	hTable.add("grapefruit"); // 12
	hTable.remove("strawberry");
	ASSERT_FALSE(hTable.contains("strawberry"));
	ASSERT_TRUE(hTable.contains("melon"));
	ASSERT_TRUE(hTable.contains("grapefruit"));
	ASSERT_FALSE(hTable.contains("blackberry"));
	hTable.remove("mango");
	ASSERT_TRUE(hTable.contains("grape"));
}

TEST(HashTable_LinearProbing, iteratorTest)
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

	for (auto fruit : hTable) {
		ASSERT_EQ(1, fruits.count(fruit));
	}
}
