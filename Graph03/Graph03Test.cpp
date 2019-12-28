#include "pch.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

TEST(GraphAdjacentMatrix, addTest)
{
	Graph graph{ "A","B","C","D","E" };
	graph.addEdge("A", "B");
	graph.addEdge("A", "C");
	graph.addEdge("C", "D");
	graph.addEdge("C", "E");
	graph.addEdge("D", "E");
	ASSERT_EQ(0, graph.indegree("A"));
	ASSERT_EQ(2, graph.outdegree("A"));
	std::string output = "";
	for (auto s : graph) {
		output += s.first + ",";
	}
	ASSERT_EQ(output, "A,B,C,D,E,");
	graph.addNode("F");
	ASSERT_EQ(0, graph.indegree("F"));
	ASSERT_EQ(2, graph.indegree("E"));
	output = "";
	for (auto node : graph) {
		output += node.first + ",";
	}
	ASSERT_EQ(output, "A,B,C,D,E,F,");
}

TEST(GraphAdjacentMatrix, removeTest)
{
	Graph graph{ "A","B","C","D","E" };
	graph.addEdge("A", "B");
	graph.addEdge("A", "C");
	graph.addEdge("B", "D");
	graph.addEdge("C", "D");
	graph.addEdge("C", "E");
	graph.addEdge("D", "E");
	ASSERT_EQ(0, graph.indegree("A"));
	ASSERT_EQ(2, graph.outdegree("A"));
	graph.removeNode("C");
	ASSERT_EQ(0, graph.indegree("A"));
	ASSERT_EQ(1, graph.outdegree("A"));
	ASSERT_EQ(4, graph.getSize());
	graph.removeEdge("A", "B");
	ASSERT_EQ(0, graph.indegree("B"));
	ASSERT_EQ(0, graph.outdegree("A"));
	std::string output = "";
	for (auto node : graph) {
		output += node.first + ",";
	}
	ASSERT_EQ(output, "A,B,D,E,");
}

TEST(GraphAdjacentMatrix, bfsTest) {
	Graph graph{ "A","B","C","D","E" };
	graph.addEdge("A", "B");
	graph.addEdge("A", "C");
	graph.addEdge("B", "E");
	graph.addEdge("C", "D");
	graph.addEdge("C", "E");
	graph.addEdge("D", "E");
	std::vector<std::string> nodes = graph.bfs("A");
	std::string output = "";
	for (auto s : nodes) {
		output += s + ",";
	}
	ASSERT_EQ(output, "A,B,C,E,D,");
	graph.addNode("F");
	graph.addNode("G");
	graph.addEdge("B", "F");
	graph.addEdge("F", "E");
	graph.addEdge("D", "G");
	nodes = graph.bfs("A");
	output = "";
	for (auto s : nodes) {
		output += s + ",";
	}
	ASSERT_EQ(output, "A,B,C,E,F,D,G,");
}

TEST(GraphAdjacentMatrix, dfsTest) {
	Graph graph{ "A","B","C","D","E" };
	graph.addEdge("A", "B");
	graph.addEdge("A", "C");
	graph.addEdge("B", "E");
	graph.addEdge("C", "D");
	graph.addEdge("C", "E");
	graph.addEdge("D", "E");
	std::vector<std::string> nodes = graph.dfs("A");
	std::string output = "";
	for (auto s : nodes) {
		output += s + ",";
	}
	ASSERT_EQ(output, "A,C,E,D,B,");
	graph.addNode("F");
	graph.addNode("G");
	graph.addEdge("B", "F");
	graph.addEdge("F", "E");
	graph.addEdge("D", "G");
	nodes = graph.dfs("A");
	output = "";
	for (auto s : nodes) {
		output += s + ",";
	}
	ASSERT_EQ(output, "A,C,E,D,G,B,F,");
}

TEST(GraphAdjacentMatrix, bfsLengthTest) {
	Graph graph{ "A","B","C","D","E","F","G" };
	graph.addEdge("A", "B");
	graph.addEdge("A", "C");
	graph.addEdge("B", "E");
	graph.addEdge("C", "D");
	graph.addEdge("C", "E");
	graph.addEdge("D", "E");
	graph.addEdge("B", "F");
	graph.addEdge("F", "E");
	graph.addEdge("D", "G");
	ASSERT_EQ(2, graph.bfs("A", "E"));
	ASSERT_EQ(3, graph.bfs("A", "G"));
}

TEST(GraphAdjacentMatrix, MooreTest) {
	Graph graph{ "A","B","C","D","E","F","G" };
	graph.addEdge("A", "B");
	graph.addEdge("A", "C");
	graph.addEdge("B", "E");
	graph.addEdge("C", "D");
	graph.addEdge("C", "E");
	graph.addEdge("D", "E");
	graph.addEdge("B", "F");
	graph.addEdge("F", "E");
	graph.addEdge("D", "G");
	std::vector<std::string> route = graph.bfsWithRoute("A", "G");
	std::string output = "";
	for (auto s : route) {
		output += s + ",";
	}
	ASSERT_EQ(output, "G,D,C,");
}
