// 인접리스트, 방향그래프, 비가중치, 목적노드까지의 거리 및 경로찾기

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
#include <list>
#include <map>
using namespace std;
class Graph {
	// 무방향 그래프 :map<string, list<string>> nodes 하나 유지
	map<string, list<string>> outNodes;
	map<string, list<string>> inNodes;
public:
	Graph() = default;
	Graph(initializer_list<string> list)
		:Graph{} {
		for (auto node : list) addNode(node);
	}
	virtual ~Graph() = default;
	bool isEmpty() const noexcept {
		return outNodes.size() == 0;
	}
	bool isFull() const noexcept {
		return false;
	}
	int getSize() const noexcept {
		return outNodes.size();
	}

	int indegree(const string& node) {
		if (inNodes.find(node) == inNodes.end())
			invalid_argument("indegree: no such node: " + node);
		return inNodes[node].size();
	}

	int outdegree(const string& node) {
		if (outNodes.find(node) == outNodes.end())
			invalid_argument("outdegree: no such node: " + node);
		return outNodes[node].size();
	}

	void addNode(const string& node) {
		if (outNodes.find(node) != outNodes.end())
			invalid_argument("node already exists");
		outNodes[node] = list<string>{};
		inNodes[node] = list<string>{};
	}

	void addEdge(const string& from, const string& to) {
		if (outNodes.find(from) == outNodes.end() || outNodes.find(to) == outNodes.end())
			invalid_argument("addEdge: node does not exists ");
		outNodes[from].push_front(to);
		inNodes[to].push_front(from);
	}

	void removeNode(const string& node) {
		if (isEmpty()) return;
		if(outNodes.find(node)==outNodes.end())
			throw std::runtime_error("removeNode: node does not exists");
		outNodes.erase(node);
		for (auto& other : outNodes)
			other.second.remove(node);
		inNodes.erase(node);
		for (auto& other : inNodes)
			other.second.remove(node);
	}

	void removeEdge(const string& from, const string& to) {
		if (outNodes.find(from) == outNodes.end() || outNodes.find(to) == outNodes.end())
			throw std::runtime_error("removeEdge: node does not exists");
		auto it = std::find(outNodes[from].begin(), outNodes[from].end(), to);
		if (it == outNodes[from].end())
			throw std::runtime_error("removeEdge: edge does not exists");
		it = std::find(inNodes[to].begin(), inNodes[to].end(), from);
		if (it == inNodes[to].end())
			throw std::runtime_error("removeEdge: edge does not exists");
		outNodes[from].remove(to);
		inNodes[to].remove(from);
	}

	// 시작노드로 도달할 수 있는 모든 노드 탐색
	vector<string> bfs(string startNode) {
		if (outNodes.find(startNode) == outNodes.end())
			throw std::invalid_argument("bfs: no such starting node: " + startNode);
		queue<string> queue;
		map<string, bool> visited;
		vector<string> result;
		queue.push(startNode);
		visited[startNode] = true;
		while (!queue.empty()) {
			string curNode = queue.front();
			queue.pop();
			result.push_back(curNode);
			for (string nextNode : outNodes[curNode]) {
				if (!visited[nextNode]) {
					visited[nextNode] = true;
					queue.push(nextNode);
				}
			}
		}
		return result;
	}

	vector<string> constructRoute(map<string, int>& visited, string endNode) {
		vector<string> result;
		string curNode = endNode;
		int length = visited[curNode];
		while (length > 0) {
			result.push_back(curNode);
			bool found = false;
			for (auto nextNode : inNodes[curNode]) {
				if (visited[nextNode]==length-1) {	// 이전에 방문한 노드일 때
					curNode = nextNode;
					found = true;
					break;
				}
			}
			if (!found) throw std::runtime_error("Error occurred: Route Construction");
			--length;
		}
		return result;
	}

	// 시작노드에서 목적노드까지의 경로
	vector<string> bfsWithRoute(string startNode, string endNode) {
		if (outNodes.find(startNode) == outNodes.end())
			throw std::invalid_argument("bfs: no such start node: " + startNode);
		if (outNodes.find(endNode) == outNodes.end())
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
			Data curNode = queue.front();
			queue.pop();
			if (curNode.node == endNode) return constructRoute(visited, endNode);
			for (auto nextNode : outNodes[curNode.node]) {
				if (!visited[nextNode]) {
					visited[nextNode] = curNode.length + 1;
					queue.emplace(nextNode, curNode.length + 1);
				}

			}
		}
		return vector<string>{};
	}

	// 시작노드로 도달할 수 있는 모든 노드 탐색 (깊이 우선 탐색)
	vector<string> dfs(string startNode) {
		if(outNodes.find(startNode)==outNodes.end())
			throw std::invalid_argument("dfs: no such starting node: "+startNode);
		stack<string> stack;
		map<string, bool> visited;
		vector<string> result;
		stack.push(startNode);
		visited[startNode] = true;
		while (!stack.empty()) {
			string curNode = stack.top();
			stack.pop();
			result.push_back(curNode);
			for (auto nextNode : outNodes[curNode]) {
				if (!visited[nextNode]) {
					visited[nextNode] = true;
					stack.push(nextNode);
				}
			}
		}
		return result;
	}
	std::map<std::string, std::list<std::string>>::iterator begin() { return outNodes.begin(); }
	std::map<std::string, std::list<std::string>>::iterator end() { return outNodes.end(); }
};

#endif /* GRAPH_H_ */
