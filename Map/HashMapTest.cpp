#include "pch.h"
#include "gtest/gtest.h"
#include <string>

TEST(HashMap, duplTest)
{
	HashMap<std::string, int> hMap;
	hMap.put("a", 3);
	hMap.put("apple", 3);
	hMap.put("mango", 3);
	hMap.put("b", 3);
	hMap.put("c", 3);
	hMap.put("d", 3);
	hMap.put("e", 3);
	hMap.put("f", 3);
	hMap.put("g", 3);
	hMap.put("h", 3);
	hMap.put("i", 3);
	hMap.put("j", 3);
	
	ASSERT_EQ(hMap.getSize(), 12);
}

TEST(HashMap, addTest)
{
	HashMap<std::string, int> hMap;
	hMap.put("apple", 3);
	hMap.put("peach", 5);
	hMap.put("grape", 2);
	hMap.put("orange", 10);
	hMap.put("mango", 5);
	hMap.put("strawberry", 7);
	hMap.put("banana", 6);
	ASSERT_TRUE(hMap.containsKey("banana"));
	ASSERT_TRUE(hMap.containsKey("orange"));
	hMap.put("apple", 6);
	ASSERT_EQ(hMap.getSize(), 7);
}


TEST(HashMap, getTest)
{
	HashMap<std::string, int> hMap;
	hMap.put("apple", 3);
	hMap.put("peach", 5);
	hMap.put("grape", 2);
	hMap.put("orange", 10);
	hMap.put("apple", 6);
	ASSERT_EQ(6, hMap.get("apple"));
	ASSERT_EQ(10, hMap.get("orange"));
	ASSERT_EQ(hMap.getSize(), 4);
}

TEST(HashMap, removeTest)
{
	HashMap<std::string, int> hMap;
	hMap.put("apple", 3);
	hMap.put("peach", 5);
	hMap.put("grape", 2);
	hMap.put("orange", 10);
	hMap.put("mango", 5);
	hMap.put("strawberry", 7);
	hMap.put("banana", 6);
	hMap.remove("banana");
	hMap.remove("orange");
	ASSERT_FALSE(hMap.containsKey("banana"));
	ASSERT_FALSE(hMap.containsKey("orange"));
	ASSERT_TRUE(hMap.containsKey("mango"));
	hMap.put("peach", 10);
	ASSERT_EQ(hMap.getSize(), 5);
}

TEST(HashMap, iteratorTest)
{
	HashMap<std::string, int> hMap;
	std::set<std::string> keySet;
	std::set<int> valueSet;
	hMap.put("apple", 3);
	keySet.insert("apple");
	valueSet.insert(3);
	hMap.put("peach", 5);
	keySet.insert("peach");
	valueSet.insert(5);
	hMap.put("grape", 2);
	keySet.insert("grape");
	valueSet.insert(2);
	hMap.put("orange", 10);
	keySet.insert("orange");
	valueSet.insert(10);
	hMap.put("mango", 5);
	keySet.insert("mango");
	hMap.put("coconut", 2);
	keySet.insert("coconut");
	hMap.put("strawberry", 10);
	keySet.insert("strawberry");

	ASSERT_EQ(valueSet, hMap.getValueSet());
	ASSERT_EQ(keySet, hMap.getKeySet());
}
