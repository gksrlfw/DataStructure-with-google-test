#include "pch.h"
#include "gtest/gtest.h"
#include <string>

TEST(BST_recursiveimpl_noparentlink, initTest)
{
	BST tree;
	ASSERT_EQ(tree.numberOfNodes(), 0);
	ASSERT_TRUE(tree.isEmpty());
}

// add, inorder traversal, number of nodes
TEST(BST_recursiveimpl_noparentlink, addTest)
{
	BST tree;
	tree.add(3);
	tree.add(5);
	tree.add(1);
	ASSERT_EQ(3, tree.numberOfNodes());
	std::string output{ "" };
	for (auto i : tree)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "1,3,5,");

	tree.clear();
	tree.add(1);
	tree.add(3);
	tree.add(5);
	output = "";
	for (auto i : tree)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "1,3,5,");

	tree.clear();
	tree.add(5);
	tree.add(3);
	tree.add(1);
	output = "";
	for (auto i : tree)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "1,3,5,");
}


TEST(BST_recursiveimpl_noparentlink, initializerTest)
{
	BST tree{ 4,1,3,6,5,2 };
	ASSERT_EQ(6, tree.numberOfNodes());
	std::string output{ "" };
	for (auto i : tree)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "1,2,3,4,5,6,");
}

// add, inorder traversal, number of nodes
TEST(BST_recursiveimpl_noparentlink, heightTest)
{
	BST tree;
	tree.add(1);
	tree.add(3);
	tree.add(5);
	ASSERT_EQ(tree.getHeight(), 2);
	tree.clear();
	tree.add(7);
	tree.add(5);
	tree.add(3);
	tree.add(1);
	ASSERT_EQ(tree.getHeight(), 3);

	tree.clear();
	tree.add(5);
	tree.add(7);
	tree.add(3);
	tree.add(1);
	ASSERT_EQ(tree.getHeight(), 2);

	std::string output{ "" };
	for (auto i : tree)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "1,3,5,7,");
}

TEST(BST_recursiveimpl_noparentlink, findTest)
{
	BST tree{ 7,1,3,9,10,4,2 };

	ASSERT_EQ(7, tree.numberOfNodes());
	ASSERT_TRUE(tree.find(3));
	ASSERT_TRUE(tree.find(2));
	ASSERT_TRUE(tree.find(7));
	ASSERT_TRUE(tree.find(10));
	ASSERT_FALSE(tree.find(0));
	ASSERT_FALSE(tree.find(5));
	ASSERT_FALSE(tree.find(11));

	std::string output{ "" };
	for (auto i : tree)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "1,2,3,4,7,9,10,");
}

TEST(BST_recursiveimpl_noparentlink, traversalTest)
{
	BST tree;
	tree.add(5);
	tree.add(2);
	tree.add(7);
	tree.add(1);
	tree.add(3);
	tree.add(6);
	tree.add(8);

	std::string output{ "" };
	for (auto i : tree)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "1,2,3,5,6,7,8,");
	output = "";
	tree.setIteratorType(BST::TreeTraversal::PREORDER);
	for (auto i : tree)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "5,2,1,3,7,6,8,");
	output = "";
	tree.setIteratorType(BST::TreeTraversal::POSTORDER);
	for (auto i : tree)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "1,3,2,6,8,7,5,");
}

TEST(BST_recursiveimpl_noparentlink, nextTest)
{
	BST tree{ 7,1,3,9,10,4,2,8 };

	ASSERT_EQ(4, tree.next(3));
	ASSERT_THROW(tree.next(6), std::invalid_argument);
	ASSERT_EQ(7, tree.next(4));
	ASSERT_EQ(8, tree.next(7));
	ASSERT_EQ(10, tree.next(9));
}

TEST(BST_recursiveimpl_noparentlink, prevTest)
{
	BST tree{ 7,1,3,9,10,4,2,8 };

	ASSERT_EQ(2, tree.prev(3));
	ASSERT_EQ(3, tree.prev(4));
	ASSERT_THROW(tree.prev(6), std::invalid_argument);
	ASSERT_EQ(7, tree.prev(8));
	ASSERT_EQ(9, tree.prev(10));
}

TEST(BST_recursiveimpl_noparentlink, removeTest)
{
	BST tree{ 7,1,3,9,10,4,2,8 };

	tree.remove(10);
	std::string output{ "" };
	for (auto i : tree)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "1,2,3,4,7,8,9,");
	tree.remove(7);
	output = "";
	for (auto i : tree)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "1,2,3,4,8,9,");
	tree.remove(1);
	output = "";
	for (auto i : tree)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "2,3,4,8,9,");

	BST tree1{ 5,3,7 };
	tree1.remove(3);
	tree1.remove(5);
	ASSERT_EQ(tree1.numberOfNodes(), 1);
	tree1.remove(7);
	ASSERT_TRUE(tree1.isEmpty());
	tree1.add(6);
	ASSERT_EQ(tree1.numberOfNodes(), 1);
}

TEST(BST_recursiveimpl_noparentlink, balanceTest)
{
	BST tree{ 7,1,3,9,10,4,2,8,5 };
	ASSERT_EQ(4, tree.getHeight());
	tree.balanceTree();
	ASSERT_EQ(3, tree.getHeight());
	tree.setIteratorType(BST::TreeTraversal::PREORDER);
	std::string output{ "" };
	for (auto i : tree)
		output += std::to_string(i) + ",";
	ASSERT_EQ(output, "5,2,1,4,3,8,7,10,9,");
}

TEST(BST_recursiveimpl_noparentlink, rangeSearchTest) {
	BST tree{ 6,7,2,3,10,1,19,20 };
	std::vector<int> range = tree.rangeSearch(4, 19);
	std::string output = "";
	for (auto n : range)
		output += std::to_string(n) + ",";
	ASSERT_EQ(output, "6,7,10,19,");
	range = tree.rangeSearch(2, 18);
	output = "";
	for (auto n : range)
		output += std::to_string(n) + ",";
	ASSERT_EQ(output, "2,3,6,7,10,");
	range = tree.rangeSearch(2, 10);
	output = "";
	for (auto n : range)
		output += std::to_string(n) + ",";
	ASSERT_EQ(output, "2,3,6,7,10,");
	range = tree.rangeSearch(20, 30);
	output = "";
	for (auto n : range)
		output += std::to_string(n) + ",";
	ASSERT_EQ(output, "20,");
	range = tree.rangeSearch(-5, 3);
	output = "";
	for (auto n : range)
		output += std::to_string(n) + ",";
	ASSERT_EQ(output, "1,2,3,");
}

TEST(BST_recursiveimpl_noparentlink, nearestNeighborTest) {
	BST tree{ 6,7,2,3,10,1,19,20 };
	std::pair<int, int> neighbor = tree.nearestNeighbor(4);
	ASSERT_EQ(neighbor.first, 3);
	ASSERT_EQ(neighbor.second, 6);
	neighbor = tree.nearestNeighbor(2);
	ASSERT_EQ(neighbor.first, 1);
	ASSERT_EQ(neighbor.second, 3);
	neighbor = tree.nearestNeighbor(1);
	ASSERT_EQ(neighbor.first, 1);
	ASSERT_EQ(neighbor.second, 2);
	neighbor = tree.nearestNeighbor(20);
	ASSERT_EQ(neighbor.first, 19);
	ASSERT_EQ(neighbor.second, 20);
	neighbor = tree.nearestNeighbor(21);
	ASSERT_EQ(neighbor.first, 20);
	ASSERT_EQ(neighbor.second, 20);
	neighbor = tree.nearestNeighbor(-5);
	ASSERT_EQ(neighbor.first, 1);
	ASSERT_EQ(neighbor.second, 1);

}

BST foo() {
	BST tree{ 3,1,2,4,5 };
	return tree;
}

TEST(BST_recursiveimpl_noparentlink, Big5)
{
	BST tree1{ 3,1,2,4,5 };
	BST tree2{ 8,6,7,9,10 };
	BST tree3;
	BST tree4(tree2);
	tree3 = tree1;
	ASSERT_EQ(tree1.getHeight(), tree3.getHeight());
	ASSERT_EQ(tree2.getHeight(), tree4.getHeight());
	ASSERT_EQ(tree1.numberOfNodes(), tree3.numberOfNodes());
	ASSERT_EQ(tree2.numberOfNodes(), tree4.numberOfNodes());
	tree1.setIteratorType(BST::TreeTraversal::PREORDER);
	std::string output1 = "";
	for (auto i : tree1)
		output1 += std::to_string(i) + ",";
	tree3.setIteratorType(BST::TreeTraversal::PREORDER);
	std::string output3 = "";
	for (auto i : tree3)
		output3 += std::to_string(i) + ",";
	ASSERT_EQ(output1, output3);
	tree2.setIteratorType(BST::TreeTraversal::PREORDER);
	std::string output2 = "";
	for (auto i : tree2)
		output2 += std::to_string(i) + ",";
	tree4.setIteratorType(BST::TreeTraversal::PREORDER);
	std::string output4 = "";
	for (auto i : tree4)
		output4 += std::to_string(i) + ",";
	ASSERT_EQ(output2, output4);
	tree2 = foo();
	ASSERT_EQ(tree1.getHeight(), tree2.getHeight());
	ASSERT_EQ(tree1.numberOfNodes(), tree2.numberOfNodes());
	tree1.setIteratorType(BST::TreeTraversal::PREORDER);
	output1 = "";
	for (auto i : tree1)
		output1 += std::to_string(i) + ",";
	tree2.setIteratorType(BST::TreeTraversal::PREORDER);
	output2 = "";
	for (auto i : tree2)
		output2 += std::to_string(i) + ",";
	ASSERT_EQ(output1, output2);
}

