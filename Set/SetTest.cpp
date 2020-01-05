#include "pch.h"
#include "gtest/gtest.h"
#include <string>
#include <set>

TEST(Set_HashTable_Chaining, addTest)
{
	Set<std::string> set;
	set.add("apple");	// 5
	set.add("peach");	// 3
	set.add("orange");	// 3
	set.add("mango");	// 5
	set.add("grape");	// 2
	set.add("strawberry");	// 10
	set.add("banana");	// 7
	set.add("melon");	// 14
	set.add("kiwi");		// 1
	set.add("tomato");	// 12
	set.add("blackberry"); // 3
	ASSERT_EQ(set.getSize(), 11);
	ASSERT_TRUE(set.contains("banana"));
	ASSERT_TRUE(set.contains("orange"));
	ASSERT_TRUE(set.contains("peach"));
	set.add("apple");
	ASSERT_EQ(set.getSize(), 11);
}

TEST(Set_HashTable_Chaining, removeTest)
{
	Set<std::string> set;
	set.add("apple");	// 5
	set.add("peach");	// 3
	set.add("orange");	// 3
	set.add("mango");	// 5
	set.add("grape");	// 2
	set.add("strawberry");	// 10
	set.add("banana");	// 7
	set.add("melon");	// 14
	set.add("kiwi");		// 1
	set.add("tomato");	// 12
	set.add("blackberry"); // 3
	ASSERT_EQ(set.getSize(), 11);
	set.remove("orange");
	set.remove("banana");
	set.remove("apple");
	ASSERT_FALSE(set.contains("banana"));
	ASSERT_FALSE(set.contains("orange"));
	ASSERT_FALSE(set.contains("apple"));
	ASSERT_TRUE(set.contains("mango"));
	set.add("peach");
	ASSERT_EQ(set.getSize(), 8);
}

TEST(Set_HashTable_Chaining, iteratorTest)
{
	Set<std::string> set;
	std::set<std::string> fruits;
	set.add("apple");
	fruits.insert("apple");
	set.add("peach");
	fruits.insert("peach");
	set.add("grape");
	fruits.insert("grape");
	set.add("orange");
	fruits.insert("orange");
	set.add("mango");
	fruits.insert("mango");
	set.add("coconut");
	fruits.insert("coconut");
	set.add("strawberry");
	fruits.insert("strawberry");
	set.remove("grape");

	for (std::string fruit : set) {
		//std::cout << fruit << "\n";
		ASSERT_EQ(1, fruits.count(fruit));
	}
}


TEST(Set_HashTable_Chaining, unionTest)
{
	Set<std::string> set1, set2;
	std::set<std::string> fruits;
	set1.add("apple");
	fruits.insert("apple");
	set1.add("peach");
	fruits.insert("peach");
	set1.add("grape");
	fruits.insert("grape");
	set2.add("orange");
	fruits.insert("orange");
	set2.add("mango");
	fruits.insert("mango");
	set2.add("coconut");
	fruits.insert("coconut");
	set2.add("strawberry");
	fruits.insert("strawberry");

	Set<std::string> set(set1 + set2);

	for (std::string fruit : set) {
		ASSERT_EQ(1, fruits.count(fruit));
	}
}

TEST(Set_HashTable_Chaining, DifferenceTest)
{
	Set<std::string> set1, set2;
	std::set<std::string> fruits;
	set1.add("apple");
	fruits.insert("apple");
	set1.add("peach");
	set1.add("mango");
	fruits.insert("mango");
	set1.add("grape");
	fruits.insert("grape");
	set2.add("peach");
	set2.add("grape");
	set2.add("strawberry");

	Set<std::string> set(set1 - set2);

	for (std::string fruit : set) {
		ASSERT_EQ(1, fruits.count(fruit));
	}
}

TEST(Set_HashTable_Chaining, IntersectionTest)
{
	Set<std::string> set1, set2;
	std::set<std::string> fruits;
	set1.add("apple");
	fruits.insert("apple");
	set1.add("peach");
	set1.add("mango");
	set2.add("apple");
	set2.add("grape");
	set2.add("strawberry");

	Set<std::string> set(intersection(set1, set2));

	for (std::string fruit : set) {
		ASSERT_EQ(1, fruits.count(fruit));
	}
}
