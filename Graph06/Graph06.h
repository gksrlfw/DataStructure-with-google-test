// 인접리스트, 방향그래프, 가중치, 목적노드까지의 최단거리 및 경로찾기
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
#include <functional>
#include <map>
using namespace std;

class Graph {
	struct Edge {
		string node;
		int weight;
		Edge(string node, int weight = -1)
			:node(node), weight(weight) {}
	};

	map<string, list<Edge>> outNodes;
	map<string, list<Edge>> inNodes;
	bool findNode(const list<Edge>& edges, const string& node) {
		for (auto edge : edges)
			if (edge.node == node) return true;
		return false;
	}
public:
	Graph() = default;
	Graph(std::initializer_list<std::string> list) : Graph{} {
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
			throw std::runtime_error("node already exists");
		list<Edge> inList;
		list<Edge> outList;
		inNodes[node] = inList;
		outNodes[node] = outList;
	}

	void addEdge(const string& from, const string& to, int weight) {
		if (outNodes.find(from) == outNodes.end() || outNodes.find(to) == outNodes.end())
			throw std::runtime_error("addEdge: node does not exists");
		outNodes[from].emplace_front(to, weight);
		inNodes[to].emplace_front(from, weight);
	}

	void removeNode(const string& node) {
		if (isEmpty()) return;
		outNodes.erase(node);
		for (auto& other : outNodes)
			other.second.remove_if([&node](Edge neighbor) {return neighbor.node == node; });
		inNodes.erase(node);
		for(auto& other: inNodes)
			other.second.remove_if([&node](Edge neighbor) {return neighbor.node == node; });
	}

	void removeEdge(const string& from, const string& to) {
		if (outNodes.find(from) == outNodes.end() || outNodes.find(to) == outNodes.end())
			throw std::runtime_error("removeEdge: node does not exists");
		if (!findNode(outNodes[from], to))
			throw std::runtime_error("removeEdge: edge does not exists");
		outNodes[from].remove_if([&to](Edge neighbor) { return neighbor.node == to; });
		inNodes[to].remove_if([&from](Edge neighbor) { return neighbor.node == from; });
	}

	int dijkstraAlgorithm(const string& startNode, const string& endNode) {
		struct Visited {
			string prev;
			int distance;
			bool done;
			Visited(const string prev="", int distance=INT_MAX, bool done=false)
				:prev(prev), distance(distance), done(done) {}
		};
		map<string, Visited> visited;
		for (auto node : outNodes) visited[node.first] = Visited();

		struct Data {
			string node;
			int distance;
			Data(string node, int distance)
				:node(node), distance(distance) {}
		};
		auto temp = [](Data& a, Data& b) {return a.distance > b.distance; };
		priority_queue<Data, vector<Data>, decltype(temp)> queue(temp);
		visited[startNode].distance = 0;
		queue.emplace(startNode, 0);
		while (!queue.empty()) {
			Data curNode = queue.top();
			queue.pop();
			if (!visited[curNode.node].done) {
				visited[curNode.node].done = true;
				for (auto nextNode : outNodes[curNode.node]) {
					int accumulatedWeight = curNode.distance + nextNode.weight;
					if (accumulatedWeight < visited[nextNode.node].distance) {
						visited[nextNode.node].distance = accumulatedWeight;
						queue.emplace(nextNode.node, accumulatedWeight);
					}
				}
			}
		}
		// 전체를 다 구한 뒤 endNode의 거리를 리턴한다.
		return visited[endNode].distance;
	}
	std::map<std::string, std::list<Edge>>::iterator begin() { return outNodes.begin(); }
	std::map<std::string, std::list<Edge>>::iterator end() { return outNodes.end(); }
};

#endif /* GRAPH_H_ */
