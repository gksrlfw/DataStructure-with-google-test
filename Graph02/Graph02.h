// ��������Ʈ, ������, ����ġ �׷���

#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <initializer_list>
#include <queue>
#include <vector>
#include <list>
#include <map>
using namespace std;
class Graph {
private:
	// string : ��� �̸�. list<string> : �ش� ���� ����Ǿ��ִ� ��� ����
	map<string, list<string>> nodes;
public:
	Graph() = default;
	Graph(initializer_list<string> list)
		:Graph{} {
		for (auto node : list) addNode(node);
	}
	virtual ~Graph() = default;
	bool isEmpty() const noexcept {
		return nodes.size() == 0;
	}
	bool isFull() const noexcept {
		return false;
	}
	int getSize() const noexcept {
		return nodes.size();
	}

	int indegree(const string& node) {
		if (nodes.find(node) == nodes.end()) invalid_argument("indegree: no such node: " + node);
		return nodes[node].size();
	}

	int outdegree(const string& node) {
		if (nodes.find(node) == nodes.end()) invalid_argument("outdegree: no such node: " + node);
		return nodes[node].size();
	}

	void addNode(const string& node) {
		if (nodes.find(node) != nodes.end()) throw runtime_error("node already exists");
		// �ʱ⿡�� �� ����Ʈ ����
		list<string> list;
		nodes[node] = list;
	}

	void addEdge(const string& from, const string& to) {
		if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end())
			throw runtime_error("addEdge: node does not exists");
		// ������ �׷���
		nodes[from].push_front(to);
		nodes[to].push_front(from);
	}

	void removeNode(const string& node) {
		if (isEmpty()) return;
		if (nodes.find(node) == nodes.end()) throw runtime_error("removeNode: does not exists");
		// node�� ������ �ִ� �ٸ� ������ ã�Ƽ� �ű⿡ �ִ� node�� ���ش�.
		for (auto label : nodes[node])
			nodes[label].remove(node);
		// node ����
		nodes.erase(node);
	}

	void removeEdge(const string& from, const string& to) {
		if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end())
			throw std::runtime_error("removeEdge: does not exists");
		// �ش� ������ �ִ��� Ȯ��
		auto it = find(nodes[from].begin(), nodes[from].end(), to);
		if(it==nodes[from].end()) throw runtime_error("removeEdge: edge does not exists");
		nodes[from].remove(to);
		nodes[to].remove(from);
	}
	std::map<std::string, std::list<std::string>>::iterator begin() { return nodes.begin(); }
	std::map<std::string, std::list<std::string>>::iterator end() { return nodes.end(); }
};

#endif /* GRAPH_H_ */
