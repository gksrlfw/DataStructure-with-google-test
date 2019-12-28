// �������, ����׷���, ����ġ, ������������ �Ÿ� �� ���ã��
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
private:
	int capacity = 5;
	int size = 0;
	vector<vector<int>> graph{ 5, vector<int>(5,0) };
	queue<int> freeIndex;
	map<string, int> nodes;
	map<int, string> inverseNodes;

	void increaseCapacity() {
		for (int i = capacity; i < capacity * 2; i++)
			freeIndex.push(i);
		capacity *= 2;
		graph.resize(capacity);
		for (int i = 0; i < capacity; i++) graph[i].resize(capacity, 0);
	}

public:
	Graph() {
		for (int i = 0; i < capacity; i++)
			freeIndex.push(i);
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
		if (nodes.find(node) == nodes.end()) throw invalid_argument("indegree: no such node: " + node);
		int idx = nodes[node];
		int count = 0;
		for (int i = 0; i < capacity; i++)
			count += graph[i][idx];
		return count;
	}

	int outdegree(const string& node) {
		if (nodes.find(node) == nodes.end()) throw invalid_argument("outdegree: no such node: " + node);
		int idx = nodes[node];
		int count = 0;
		for (int i = 0; i < capacity; i++)
			count += graph[idx][i];
		return count;
	}

	int addNode(const string& node) {
		if (size == capacity) increaseCapacity();
		if (nodes.find(node) != nodes.end())
			throw invalid_argument("node already exists");
		int idx = freeIndex.front();
		freeIndex.pop();
		nodes[node] = idx;
		inverseNodes[idx] = node;
		++size;
	}

	int addEdge(const string& from, const string& to) {
		if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end()) throw invalid_argument("addEdge: node does not exists");
		int fromIdx = nodes[from];
		int toIdx = nodes[to];
		// ����׷���
		graph[fromIdx][toIdx] = 1;
	}

	void removeNode(const string& node) {
		if (nodes.find(node) == nodes.end())
			throw invalid_argument("removeNode: node does not exists");
		if (isEmpty()) return;
		int delIdx = nodes[node];
		nodes.erase(node);
		inverseNodes.erase(delIdx);
		freeIndex.push(delIdx);
		for (int i = 0; i < capacity; i++) {
			graph[delIdx][i] = 0;
			graph[i][delIdx] = 0;
		}
		--size;
	}

	void removeEdge(const string& from, const string& to) {
		if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end())
			throw std::invalid_argument("removeEdge: node does not exists");
		int fromIdx = nodes[from];
		int toIdx = nodes[to];
		if (graph[fromIdx][toIdx] != 1) throw invalid_argument("removeEdge: edge does not exists");
		graph[fromIdx][toIdx] = 0;
	}

	// ���۳��� ������ �� �ִ� ��� ��� Ž�� (�ʺ� �켱 Ž��)
	vector<string> bfs(string startNode) {
		if (nodes.find(startNode) == nodes.end())
			throw invalid_argument("bfs: no such starting node: " + startNode);
		queue<string> queue;
		map<string, bool> visited;
		vector<string> result;
		queue.push(startNode);
		visited[startNode] = true;
		while (!queue.empty()) {
			string curNode = queue.front();
			queue.pop();
			result.push_back(curNode);
			int idx = nodes[curNode];
			for (int i = 0; i < capacity; i++) {
				if (graph[idx][i] > 0) {
					string nextNode = inverseNodes[i];
					if (!visited[nextNode]) {
						queue.push(nextNode);
						visited[nextNode] = true;
					}
				}
			}
		}
		return result;
	}

	// ���۳�忡�� ������������ �Ÿ� (�ش� ��δ� �𸣰� �Ÿ��� �ȴ�.)
	int bfs(string startNode, string endNode) {
		if (nodes.find(startNode) == nodes.end())
			throw std::invalid_argument("bfs: no such start node: " + startNode);
		if (nodes.find(endNode) == nodes.end())
			throw std::invalid_argument("bfs: no such end node: " + startNode);

		// ����� �̸��� ���̸� ���� �����ϴ� ����ü�� �̿��Ѵ�.
		struct Data {
			string node;
			int length = 0;
			Data(string node, int length)
				:node(node), length(length) {}
		};
		queue<Data> queue;
		map<string, bool> visited;
		// emplace : ������ �μ��� �������ָ� ���� ���Ұ� �� ��ҿ� �ٷ� ������ش�. (push�� ��������� ����)
		queue.emplace(startNode, 0);
		visited[startNode] = true;
		while (!queue.empty()) {
			Data data(queue.front());
			queue.pop();
			// �̰� �ִܰŸ��� �ƴҼ��� ���� �ʳ�???
			// bfs�� ���� Ž���ϸ鼭 ��ĭ�� �̵��Ѵ�. ���� ������ �����ϴ� ������ �׋� ���� ª�� ���̰� �´�. �� ���� ���� �ִ°� ������..
			if (data.node == endNode) return data.length;
			int idx = nodes[data.node];
			for (int i = 0; i < capacity; i++) {
				if (graph[idx][i] > 0) {
					string nextNode = inverseNodes[i];
					if (!visited[nextNode]) {
						queue.emplace(nextNode, data.length + 1);
						visited[nextNode] = true;
					}
				}
			}
		}
		// ��߳��� ������尡 ������ �ȵǾ����� ��.
		return -1;
	}

	// ������������ ��� ���� < ���� ������ �Ųٷ� �ö󰡸鼭 ��Ʈ�� �����Ѵ�.
	// visited�� ����Ǿ��ִ� ��߳��κ����� �Ÿ��� �̿��Ѵ�.
	vector<string> constructRoute(map<string, int>& visited, string endNode) {
		vector<string> result;
		string curNode = endNode;
		int length = visited[endNode];
		while (length > 0) {
			result.push_back(curNode);
			int idx = nodes[curNode];
			bool found = false;
			for (int i = 0; i < capacity; i++) {
				// ���� ���� ����Ǿ� �ִ� ���� ��� �� ��� ��忡�� �ش� �������� �Ÿ���
				// length-1�� �ش��ϴ� ���
				if (graph[i][idx] > 0) {
					string nextNode(inverseNodes[i]);
					if (visited[nextNode] == length - 1) {
						curNode = nextNode;
						found = true;
						break;
					}
				}
			}
			if (!found) throw std::runtime_error("Error occurred: Route Construction");
			--length;
		}
		return result;
	}

	// ���۳�忡�� ���������� ���
	vector<string> bfsWithRoute(string startNode, string endNode) {
		if (nodes.find(startNode) == nodes.end())
			throw std::invalid_argument("bfs: no such start node: " + startNode);
		if (nodes.find(endNode) == nodes.end())
			throw std::invalid_argument("bfs: no such end node: " + startNode);
		struct Data {
			string node;
			int length = 0;
			Data(string node, int length)
				:node(node), length(length) {}
		};
		queue<Data> queue;
		map<string, int> visited;
		queue.emplace(startNode, 0);
		visited[startNode] = 0;
		while (!queue.empty()) {
			Data data(queue.front());
			queue.pop();
			if (data.node == endNode) return constructRoute(visited, endNode);
			int idx = nodes[data.node];
			for (int i = 0; i < capacity; i++) {
				if (graph[idx][i] > 0) {
					string nextNode = inverseNodes[i];
					if (!visited[nextNode]) {
						queue.emplace(nextNode, data.length + 1);
						visited[nextNode] = data.length + 1;
					}
				}
			}
		}
		return vector<string>{};
	}

	// ���۳��� ������ �� �ִ� ��� ��� Ž��
	vector<string> dfs(string startNode) {
		if (nodes.find(startNode) == nodes.end())
			throw std::invalid_argument("dfs: no such start node: " + startNode);
		stack<string> stack;
		map<string, bool> visited;
		vector<string> result;
		stack.push(startNode);
		visited[startNode] = true;
		while (!stack.empty()) {
			string curNode = stack.top();
			stack.pop();
			result.push_back(curNode);
			int idx = nodes[curNode];
			for (int i = 0; i < capacity; i++) {
				if (graph[idx][i] > 0) {
					string nextNode = inverseNodes[i];
					if (!visited[nextNode]) {
						stack.push(nextNode);
						visited[nextNode] = true;
					}
				}
			}
		}
		return result;
	}
	std::map<std::string, int>::iterator begin() { return nodes.begin(); }
	std::map<std::string, int>::iterator end() { return nodes.end(); }
};

#endif /* GRAPH_H_ */
