// 인접행렬, 방향그래프, 비가중치, 목적노드까지의 거리 및 경로찾기
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
		// 방향그래프
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

	// 시작노드로 도달할 수 있는 모든 노드 탐색 (너비 우선 탐색)
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

	// 시작노드에서 목적노드까지의 거리 (해당 경로는 모르고 거리만 안다.)
	int bfs(string startNode, string endNode) {
		if (nodes.find(startNode) == nodes.end())
			throw std::invalid_argument("bfs: no such start node: " + startNode);
		if (nodes.find(endNode) == nodes.end())
			throw std::invalid_argument("bfs: no such end node: " + startNode);

		// 노드의 이름과 길이를 같이 저장하는 구조체를 이용한다.
		struct Data {
			string node;
			int length = 0;
			Data(string node, int length)
				:node(node), length(length) {}
		};
		queue<Data> queue;
		map<string, bool> visited;
		// emplace : 생성자 인수를 전달해주면 새로 원소가 들어갈 장소에 바로 만들어준다. (push와 기능적으로 동일)
		queue.emplace(startNode, 0);
		visited[startNode] = true;
		while (!queue.empty()) {
			Data data(queue.front());
			queue.pop();
			// 이게 최단거리가 아닐수도 있지 않나???
			// bfs는 전부 탐색하면서 한칸씩 이동한다. 따라서 조건이 만족하는 순간이 그떄 가장 짧은 길이가 맞다. 더 있을 수도 있는것 같긴함..
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
		// 출발노드와 목적노드가 연결이 안되어있을 때.
		return -1;
	}

	// 목적노드까지의 경로 구축 < 목적 노드부터 거꾸로 올라가면서 루트를 저장한다.
	// visited에 저장되어있는 출발노드로부터의 거리를 이용한다.
	vector<string> constructRoute(map<string, int>& visited, string endNode) {
		vector<string> result;
		string curNode = endNode;
		int length = visited[endNode];
		while (length > 0) {
			result.push_back(curNode);
			int idx = nodes[curNode];
			bool found = false;
			for (int i = 0; i < capacity; i++) {
				// 현재 노드와 연결되어 있는 인접 노드 중 출발 노드에서 해당 노드까지의 거리가
				// length-1에 해당하는 노드
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

	// 시작노드에서 목적노드까지 경로
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

	// 시작노드로 도달할 수 있는 모든 노드 탐색
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
