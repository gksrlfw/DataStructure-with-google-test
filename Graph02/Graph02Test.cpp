#include "gtest/gtest.h"
#include <iostream>
#include "pch.h"
#include <string>
 
 TEST(GraphAdjacentMatrix, addTest)
 {
	 Graph graph{"A","B","C","D","E"};
	 graph.addEdge("A","B");
	 graph.addEdge("A","C");
	 graph.addEdge("C","D");
	 graph.addEdge("C","E");
	 graph.addEdge("D","E");
	 ASSERT_EQ(2, graph.indegree("A"));
	 ASSERT_EQ(2, graph.outdegree("A"));
	 std::string output = "";
	 for(auto s: graph){
		 output += s.first+",";
	 }
	 ASSERT_EQ(output,"A,B,C,D,E,");
	 graph.addNode("F");
	 ASSERT_EQ(0, graph.indegree("F"));
	 ASSERT_EQ(2, graph.outdegree("E"));
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
	ASSERT_EQ(2, graph.indegree("A"));
	ASSERT_EQ(2, graph.outdegree("A"));
	graph.removeNode("C");
	ASSERT_EQ(1, graph.indegree("A"));
	ASSERT_EQ(1, graph.outdegree("A"));
	ASSERT_EQ(4, graph.getSize());
	graph.removeEdge("A", "B");
	ASSERT_EQ(1, graph.indegree("B"));
	ASSERT_EQ(0, graph.outdegree("A"));
}
