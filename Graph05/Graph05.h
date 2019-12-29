// �������, ����׷���, ����ġ, ������������ �ִܰŸ� �� ���ã��

#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <initializer_list>
#include <queue>
#include <stack>
#include <vector>
#include <map>
using namespace std;

class Graph {
	int capacity = 5;
	int size = 0;
	// ����ġ�� 0�� �� �����Ƿ� -1�� �ʱ�ȭ�Ѵ�.
	vector<vector<int>> graph{ 5, vector<int>(5, -1) };
	queue<int> freeIndex;
	map<string, int> nodes;
	map<int, string> inverseNodes;

	void increaseCapacity() {
		for (int i = capacity; i < capacity * 2; i++)
			freeIndex.push(i);
		capacity *= 2;
		graph.resize(capacity);
		for (int i = 0; i < capacity; i++) {
			graph[i].resize(capacity, -1);
			graph[i][i] = 0;
		}
	}
public:
	Graph() {
		for (int i = 0; i < capacity; i++) freeIndex.push(i);
		for (int i = 0; i < capacity; i++) graph[i][i] = 0;
	}
	Graph(std::initializer_list<std::string> list) : Graph{} {
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

	int indegree(const string& node) {
		if (nodes.find(node) == nodes.end())
			throw std::invalid_argument("indegree: No such node: " + node);
		int idx = nodes[node];
		int count = 0;
		for (int i = 0; i < capacity; i++)
			if (graph[i][idx] > 0)
				++count;
		return count;
	}

	int outdegree(const string& node) {
		if (nodes.find(node) == nodes.end())
			throw std::invalid_argument("outdegree: No such node: " + node);
		int idx = nodes[node];
		int count = 0;
		for (int i = 0; i < capacity; i++)
			if (graph[idx][i] > 0)
				count++;
		return count;
	}
	void addNode(const string& node) {
		if (size == capacity) increaseCapacity();
		if (nodes.find(node) != nodes.end())
			throw std::invalid_argument("node already exists");
		int idx = freeIndex.front();
		freeIndex.pop();
		nodes[node] = idx;
		inverseNodes[idx] = node;
		++size;
	}

	void addEdge(const string& from, const string& to, int weight) {
		if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end())
			throw std::invalid_argument("addEdge: node does not exists");
		int fromIdx = nodes[from];
		int toIdx = nodes[to];
		graph[fromIdx][toIdx] = weight;
	}

	void removeNode(const string& node) {
		if (nodes.find(node) == nodes.end())
			throw std::invalid_argument("removeNode: node does not exists");
		int delIdx = nodes[node];
		nodes.erase(node);
		inverseNodes.erase(delIdx);
		freeIndex.push(delIdx);
		for (int i = 0; i < capacity; i++) {
			graph[delIdx][i] = -1;
			graph[i][delIdx] = -1;
			graph[i][i] = 0;
		}
		--size;
	}

	void removeEdge(const string& from, const string& to) {
		if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end())
			throw std::invalid_argument("removeEdge: node does not exists");
		int fromIdx = nodes[from];
		int toIdx = nodes[to];
		if (graph[fromIdx][toIdx] == -1)
			throw std::invalid_argument("removeEdge: edge does not exists");
		graph[fromIdx][toIdx] = -1;
	}

	// ���۳��� ������� �ִܰŸ��� ��θ� ã�´�.
	// �켱���� ť�� �̿��Ͽ� ���� ����ġ�� ª�� �������� ���ʴ�� �˻��Ѵ�.
	int dijkstraAlgorithm(const string& startNode, const string endNode, vector<string>& path) {
		if (nodes.find(startNode) == nodes.end())
			std::invalid_argument("dijkstraAlgorithm: No such source node: " + startNode);
		if (nodes.find(endNode) == nodes.end())
			std::invalid_argument("dijkstraAlgorithm: No such destination node: " + endNode);

		struct Visited {
			string prev;
			int distance;
			bool done;
			Visited(const string& prev = "none", int distance = INT_MAX, bool done = false)
				:prev(prev), distance(distance), done(done) {}
		};
		// visited �� �ʱ�ȭ
		map<string, Visited> visited;
		for (auto node : nodes) visited[node.first] = Visited();

		struct Data {
			string node;
			int distance;
			Data(const string& node, int distance = INT_MAX)
				:node(node), distance(distance) {}
		};
		// ť �ȿ��� �Ÿ��� �̿��ؼ� ��
		auto temp = [](Data& a, Data& b) {return a.distance > b.distance; };
		priority_queue<Data, vector<Data>, decltype(temp)> queue(temp);

		queue.emplace(startNode, 0);
		visited[startNode].distance = 0;
		while (!queue.empty()) {
			Data curNode = queue.top();
			queue.pop();
			if (!visited[curNode.node].done) {
				visited[curNode.node].done = true;
				int idx = nodes[curNode.node];
				for (int i = 0; i < capacity; i++) {
					// ����ġ�� 0�϶��� �������
					if (graph[idx][i] > 0) {	
						string nextNode = inverseNodes[i];
						int accumulatedWeight = curNode.distance + graph[idx][i];
						// ���� ���� ��ΰ� �� ª�� ���� �����ϰ� ť�� �����Ѵ�.
						if (accumulatedWeight < visited[nextNode].distance) {
							visited[nextNode].distance = accumulatedWeight;
							visited[nextNode].prev = curNode.node;
							queue.emplace(nextNode, accumulatedWeight);
						}
					}
				}
			}
		}
		// �Ųٷ� ��� ����
		string cur = endNode;
		while (cur != startNode) {
			path.push_back(cur);
			cur = visited[cur].prev;
		}
		path.push_back(cur);
		reverse(path.begin(), path.end());
		return visited[endNode].distance;
	}
	std::map<std::string, int>::iterator begin() { return nodes.begin(); }
	std::map<std::string, int>::iterator end() { return nodes.end(); }
};

#endif /* GRAPH_H_ */
