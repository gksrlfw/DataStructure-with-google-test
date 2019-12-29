#include "pch.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

TEST(GraphAdjacentList, addTest)
{
	Graph graph{ "A","B","C","D","E" };
	graph.addEdge("A", "B", 2);
	graph.addEdge("A", "C", 3);
	graph.addEdge("A", "E", 5);
	graph.addEdge("B", "C", 7);
	graph.addEdge("B", "D", 6);
	graph.addEdge("C", "E", 1);
	graph.addEdge("D", "C", 3);
	graph.addEdge("E", "D", 2);
	ASSERT_EQ(0, graph.indegree("A"));
	ASSERT_EQ(3, graph.outdegree("A"));
	ASSERT_EQ(3, graph.indegree("C"));
	ASSERT_EQ(1, graph.outdegree("C"));
	std::string output = "";
	for (auto s : graph) {
		output += s.first + ",";
	}
	ASSERT_EQ(output, "A,B,C,D,E,");
}

TEST(GraphAdjacentList, removeTest)
{
	Graph graph{ "A","B","C","D","E" };
	graph.addEdge("A", "B", 2);
	graph.addEdge("A", "C", 3);
	graph.addEdge("A", "E", 5);
	graph.addEdge("B", "C", 7);
	graph.addEdge("B", "D", 6);
	graph.addEdge("C", "E", 1);
	graph.addEdge("D", "C", 3);
	graph.addEdge("E", "D", 2);
	ASSERT_EQ(1, graph.indegree("B"));
	ASSERT_EQ(2, graph.outdegree("B"));
	graph.removeNode("C");
	ASSERT_EQ(0, graph.indegree("A"));
	ASSERT_EQ(2, graph.outdegree("A"));
	graph.removeEdge("A", "B");
	ASSERT_EQ(0, graph.indegree("B"));
	ASSERT_EQ(1, graph.outdegree("A"));
	std::string output = "";
	for (auto node : graph) {
		output += node.first + ",";
	}
	ASSERT_EQ(output, "A,B,D,E,");
}

TEST(GraphAdjacentList, dijkstraTest)
{
	Graph graph{ "A","B","C","D","E" };
	graph.addEdge("A", "B", 2);
	graph.addEdge("A", "C", 3);
	graph.addEdge("A", "E", 5);
	graph.addEdge("B", "C", 7);
	graph.addEdge("B", "D", 6);
	graph.addEdge("C", "E", 1);
	graph.addEdge("D", "C", 3);
	graph.addEdge("E", "D", 2);
	ASSERT_EQ(6, graph.dijkstraAlgorithm("A", "D"));
}
