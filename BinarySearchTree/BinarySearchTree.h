#pragma once
#ifndef TREE_H_
#define TREE_H_
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <stack>
#include <vector>
#include <iostream>
#include <initializer_list>
#include <cassert>
#include <utility>

class BST {
public:
	enum class TreeTraversal { INORDER, PREORDER, POSTORDER };
private:
	struct TreeNode {
		int key;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int key = -1, TreeNode * left = nullptr, TreeNode * right = nullptr)
			:key(key), left(left), right(right) {}
	};
	TreeNode* root = nullptr;
	int size = 0;
	std::vector<int> list;
	TreeTraversal traversalMethod = TreeTraversal::INORDER;

public:
	BST() = default;
	BST(std::initializer_list<int> l) {
		for (auto i : l) add(i);
	}
	BST(const BST& other) {
		list.clear();
		preOrder(other.root);
		for (auto n : list)
			add(n);
	}
	BST(BST&& other) {
		size = other.size;
		root = other.root;
		other.root = nullptr;
		other.size = 0;
	}
	virtual ~BST() {
		clear();
	}
	int numberOfNodes() const noexcept {
		//return size;
		return numberOfNodes(root);
	}
	int getHeight() const noexcept {
		return getHeight(root) - 1;
	}

	bool isEmpty() const noexcept {
		return size == 0;
		// return root==nullptr
	}
	bool isFull() const noexcept {
		return false;
	}
	void clear() noexcept {
		deleteNodes(root);
		root = nullptr;
		assert(size == 0);
	}

	const BST& operator=(const BST& other) noexcept {
		clear();
		list.clear();
		preOrder(other.root);
		for (auto n : list)
			add(n);
		return *this;
	}
	const BST& operator=(BST&& other) noexcept {
		clear();
		size = other.size;
		root = other.root;
		other.root = nullptr;
		other.size = 0;
		return *this;
	}

	// 현재노드(처음은 root)값이랑 새 노드 값이랑 같으면
	// 현재노드값이 더 크고 왼쪽노드가 있으면 왼쪽으로 계속간다.
	// 현재노드값이 더 작고 오른쪽노드가 있으면 오른쪽으로 계속간다.
	void add(int key) noexcept {
		TreeNode* newNode = new TreeNode(key);
		if (isEmpty()) root = newNode;
		else {
			TreeNode* parent = findNode(root, key);
			if (parent->key == key) {
				delete newNode;
				return;
			}
			else if (parent->key > key) parent->left = newNode;
			else parent->right = newNode;
		}
		++size;
	}

	bool find(int key) const noexcept {
		if (isEmpty()) return false;
		return findNode(root, key)->key == key;
	}

	TreeNode* findNode(TreeNode* node, int key) const noexcept {
		if (node->key == key) return node;
		TreeNode* next = node->key > key ? node->left : node->right;
		return next ? findNode(next, key) : node;
	}

	// next, prev를 위해서
	// stack은 부모노드를 유지한다.
	TreeNode* findNode(TreeNode* node, int key, std::stack<TreeNode*>& stack) const noexcept {
		if (node->key == key) return node;
		// 내가 찾는 노드가 아니면 stack에 넣는다. (결국 stack에 들어가는 노드들은 조상 노드들이 된다.)
		stack.push(node);
		TreeNode* next{ (node->key > key) ? node->left : node->right };
		return next ? findNode(next, key, stack) : node;
	}

	void setIteratorType(TreeTraversal traversalMethod) {
		this->traversalMethod = traversalMethod;
	}
	/*
	 * 오른쪽 서브트리가 있는 경우: 오른쪽 서브트리에서 가장 작은 값 (오른쪽 이후 계속 왼쪽) > leftDescendant
	 * 오른쪽 서브트리가 없는 경우: 자신보다 키 값이 큰 부모노드 > rightAncestor
	 */

	int next(int key) const {
		if (isEmpty()) std::runtime_error("next: empty tree");
		std::stack<TreeNode*> parents;
		TreeNode* cur = findNode(root, key, parents);
		if (cur->key != key) throw std::invalid_argument("");
		if (cur->right) {
			cur = cur->right;
			while (cur->left) cur = cur->left;
			return cur->key;
		}
		else {
			while (!parents.empty()) {
				TreeNode* parent = parents.top();
				parents.pop();
				if (parent->key > key) return parent->key;
			}
			return key;
		}
	}

	/*
	 * 왼쪽 서브트리가 있는 경우: 왼쪽 서브트리에서 가장 큰 값 (왼쪽이후 계속 오른쪽)
	 * 왼쪽 서브트리가 없는 경우: 자신보다 키 값이 작은 부모노드
	 */
	int prev(int key) const {
		if (isEmpty()) std::runtime_error("prev: empty tree");
		std::stack<TreeNode*> parents;
		TreeNode* curr{ findNode(root, key, parents) };
		if (curr->key != key) throw std::invalid_argument("");
		if (curr->left) {
			curr = curr->left;
			while (curr->right) curr = curr->right;
			return curr->key;
		}
		else {

			while (!parents.empty()) {
				TreeNode* parent{ parents.top() };
				parents.pop();
				if (parent->key < key) return parent->key;
			}
			return key;
		}
	}

	void remove(int key) noexcept {
		if (isEmpty()) return;
		root = remove(root, key);
	}

	TreeNode* remove(TreeNode* node, int key) noexcept {
		if (node == nullptr) return node;
		if (node->key == key) node = removeNode(node);
		else if (node->key > key) node->left = remove(node->left, key);
		else node->right = remove(node->right, key);
		return node;
	}

	// 단말노드 : 바로 삭제
	// 오른쪽 자식 노드가 없을 때 : 왼쪽 자식 노드를 하나 위로
	// 왼쪽자식노드가 없을 때 : 오른쪽 자식 노드를 하나 위로
	// 둘다 있을 때 : 왼쪽 부분 트리 중 가장 큰 노드를 찾아 삭제할 노드값과 바꾼다.
	// (왼쪽 부분트리의 모든 노드보다 크고 오른쪽 부분 트리의 모든 노드보다 작다)
	TreeNode* removeNode(TreeNode* node) noexcept {
		TreeNode* subTree = nullptr;
		if (node->left && node->right) {
			TreeNode* prev = getPrevNode(node->left);
			node->key = prev->key;
			node->left = remove(node->left, prev->key);
			return node;
		}
		else if (node->left == nullptr) subTree = node->right;
		else if (node->right == nullptr) subTree = node->right;
		delete node;
		--size;
		return subTree;
	}

	TreeNode* getPrevNode(TreeNode* node) noexcept {
		if (node->right != nullptr) return getPrevNode(node->right);
		else return node;
	}

	// 해당 범위 내의 모든 원소 리턴
	std::vector<int> rangeSearch(int left, int right) const noexcept {
		std::vector<int> result;
		if (isEmpty()) return result;
		rangeSearchInorder(root, left, right, result);
		return result;
	}
	void rangeSearchInorder(TreeNode* node, int left, int right, std::vector<int>& result) const noexcept {
		if (node->left != nullptr) {
			if (node->key >= left) rangeSearchInorder(node->left, left, right, result);
		}
		if (node->key >= left && node->key <= right) result.push_back(node->key);
		if (node->right != nullptr) {
			if (node->key <= right) rangeSearchInorder(node->right, left, right, result);
		}
	}

	std::pair<int, int> nearestNeighbor(int key) const noexcept {
		std::pair<int, int> result;
		std::stack<TreeNode*> parents;
		TreeNode* cur = findNode(root, key, parents);
		if (cur->key == key) {
			result.first = prev(key);
			result.second = next(key);
		}
		else {
			parents.push(cur);
			TreeNode* nextNode = nullptr;
			bool foundNext = false;
			bool foundPrev = false;
			while (!parents.empty() && !(foundNext && foundPrev)) {
				nextNode = parents.top();
				parents.pop();
				if (!foundNext && nextNode->key > key) {
					result.second = nextNode->key;
					foundNext = true;
				}
				if (!foundPrev && nextNode->key < key) {
					result.first = nextNode->key;
					foundPrev = true;
				}
			}
			if (!foundPrev) result.first = result.second;
			if (!foundNext) result.second = result.first;
		}
		return result;
	}

	void balanceTree() noexcept {
		list.clear();
		inOrder(root);
		clear();
		balanceTree(0, list.size() - 1);
	}
	void balanceTree(int left, int right) {
		if (left == right) add(list[left]);
		else if (left + 1 == right) {
			add(list[right]);
			add(list[left]);
		}
		else {
			int mid = (left + (right - left) / 2);
			add(list[mid]);
			balanceTree(left, mid - 1);
			balanceTree(mid + 1, right);
		}
	}

	std::vector<int>::iterator begin() {
		list.clear();
		switch (traversalMethod) {
		case TreeTraversal::INORDER: inOrder(root); break;
		case TreeTraversal::PREORDER: preOrder(root); break;
		case TreeTraversal::POSTORDER: postOrder(root); break;
		}
		return list.begin();
	}
	std::vector<int>::iterator end() {
		return list.end();
	}
private:
	int numberOfNodes(TreeNode* node) const noexcept {
		if (node == nullptr) return 0;
		else return numberOfNodes(node->left) + numberOfNodes(node->right) + 1;
	}
	int getHeight(TreeNode* node) const noexcept {
		if (node == nullptr) return 0;
		else return std::max(getHeight(node->left), getHeight(node->right)) + 1;
	}
	void addNode(TreeNode* currNode, TreeNode* newNode) {
		if (currNode->key == newNode->key) {
			delete newNode;
			--size;
			return;
		}
		else if (currNode->key > newNode->key) {
			if (currNode->left) addNode(currNode->left, newNode);
			else {
				currNode->left = newNode;
				return;
			}
		}
		else {
			if (currNode->right) addNode(currNode->right, newNode);
			else {
				currNode->right = newNode;
				return;
			}
		}
	}
	void deleteNodes(TreeNode* node) {
		if (node == nullptr) return;
		else if (node->left && node->right) {
			deleteNodes(node->left);
			deleteNodes(node->right);
		}
		else if (node->left == nullptr) deleteNodes(node->right);
		else if (node->right == nullptr) deleteNodes(node->left);

		delete node;
		--size;
	}

	void preOrder(TreeNode* node) {
		list.push_back(node->key);
		if (node->left != nullptr) preOrder(node->left);
		if (node->right != nullptr) preOrder(node->right);
	}
	void inOrder(TreeNode* node) {
		if (node->left != nullptr) inOrder(node->left);
		list.push_back(node->key);
		if (node->right != nullptr) inOrder(node->right);
	}
	void postOrder(TreeNode* node) {
		if (node->left != nullptr) postOrder(node->left);
		if (node->right != nullptr) postOrder(node->right);
		list.push_back(node->key);
	}
};

#endif /* TREE_H_ */
