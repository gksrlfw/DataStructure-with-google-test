// �������, ������, ����ġ �׷���

#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <initializer_list>
#include <queue>
#include <vector>
#include <map>
using namespace std;

class Graph {
private:
	int capacity = 5;
	int size = 0;
	vector<vector<int>> graph{ 5, vector<int>(5, 0) };	// 5*5 ������ ����. 0���� �ʱ�ȭ
	queue<int> freeIndex;								// ��� ������ ���� ����
	map<string, int> nodes;								// ����� �̸��� ���� ����
	map<int, string> inverseNode;

	void increaseCapcity() {
		for (int i = capacity; i < capacity * 2; i++) 
			freeIndex.push(i);
		capacity *= 2;
		// ������ ���� �뷮 �ø���
		graph.resize(capacity);
		for (int i = 0; i < capacity; i++) graph[i].resize(capacity, 0);
	}
public:
	Graph() {
		for (int i = 0; i < capacity; i++)
			freeIndex.push(i);
	}
	Graph(initializer_list<string> list)
		:Graph{} {
		for (auto node : list) addNode(node);
	}
	virtual ~Graph() = default;
	bool isEmpty() const noexcept {
		return size == 0;
	}
	bool isFull() const noexcept {
		return false;
	}
	int getSize() const noexcept {
		return size;
	}

	// �������̸� indegree�� outdegree�� ����
	// indegree : ���� ��. outdegree : ���� ��
	int indegree(const string& node) {
		if (nodes.find(node) == nodes.end())
			throw invalid_argument("indegree: no such node" + node);
		int idx = nodes[node];
		int count = 0;
		for (int i = 0; i < capacity; i++)
			count += graph[i][idx];
		return count;
	}

	int outdegree(const string& node) {
		if (nodes.find(node) == nodes.end())
			throw std::invalid_argument("outdegree: No such node: " + node);
		int idx = nodes[node];
		int count = 0;
		for (int i = 0; i < capacity; i++)
			count += graph[idx][i];
		return count;
		// return indegree(node);	�ص���
	}

	void addNode(const string& node){
		if (size == capacity) increaseCapcity();
		if (nodes.find(node) != nodes.end())
			throw invalid_argument("node already exists");
		int idx = freeIndex.front();
		freeIndex.pop();
		nodes[node] = idx;
		inverseNode[idx] = node;
		++size;
	}

	void addEdge(const string& from, const string& to) {
		if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end())
			throw invalid_argument("addEdge: node does not exists");
		int fromIdx = nodes[from];
		int toIdx = nodes[to];
		// ������ �׷���
		graph[fromIdx][toIdx] = 1;
		graph[toIdx][fromIdx] = 1;
	}

	void removeNode(const string& node) {
		if(nodes.find(node)==nodes.end())
			throw invalid_argument("removeNode: node does not exists");
		if (isEmpty()) return;
		int delIdx = nodes[node];
		nodes.erase(node);
		inverseNode.erase(delIdx);
		freeIndex.push(delIdx);
		for (int i = 0; i < capacity; i++) {
			graph[delIdx][i] = 0;
			graph[i][delIdx] = 0;
		}
		--size;
	}

	void removeEdge(const std::string& from, const std::string& to) {
		if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end())
			throw std::invalid_argument("removeEdge: node does not exists");
		int fromIdx = nodes[from];
		int toIdx = nodes[to];
		if (graph[fromIdx][toIdx] != 1)
			throw std::invalid_argument("removeEdge: edge does not exists");
		// ������ �׷����� ���
		graph[fromIdx][toIdx] = 0;
		graph[toIdx][fromIdx] = 0;
	}
	std::map<std::string, int>::iterator begin() { return nodes.begin(); }
	std::map<std::string, int>::iterator end() { return nodes.end(); }
};

#endif /* GRAPH_H_ */
