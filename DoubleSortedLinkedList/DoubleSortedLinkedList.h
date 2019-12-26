#ifndef DOUBLESORTEDLINKEDLIST_H_
#define DOUBLESORTEDLINKEDLIST_H_
#include <stdexcept>
#include <iterator>
#include <iostream>

class DoubleSortedLinkedList {
private:
	// ======================== //
	struct Node {
		int item{ 0 };
		Node* prev{ nullptr };
		Node* next{ nullptr };
		Node() = default;
		Node(int value, Node* prev = nullptr, Node* next = nullptr) :
			item{ value }, prev{ prev }, next{ next }{}
	};
	class ListIterator : public std::iterator<std::input_iterator_tag, int> {
		Node* p;
	public:
		explicit ListIterator(Node* p) : p{ p } {}
		const ListIterator& operator++() noexcept {
			p = p->next; return *this;
		}
		ListIterator operator++(int) noexcept {
			ListIterator retval = *this; p = p->next; return retval;
		}
		bool operator==(const ListIterator& other) const noexcept { return p == other.p; }
		bool operator!=(const ListIterator& other) const noexcept { return p != other.p; }
		int operator*() const { return p->item; }
	};
	// ======================== //
	Node* head{ nullptr };
	Node* tail{ nullptr };
	int size{ 0 };

	Node* getNode(int index) const {
		Node* curr{ head };
		if (index >= 0 && index < size) {
			for (int i = 0; i < index; i++)
				curr = curr->next;
			return curr;
		}
		else throw std::range_error("ERROR: getNode(int)");
	}
	void copyList(const DoubleSortedLinkedList& srcList) noexcept {
		Node* src_it{ srcList.head };
		Node* prev{ nullptr };
		Node* curr{ head };
		while (src_it) {
			Node* newNode = new Node(src_it->item);
			if (curr == nullptr) {
				head = newNode;
			}
			else {
				curr->prev = prev;
				curr->next = newNode;
			}
			prev = curr;
			curr = newNode;
			if (src_it == srcList.tail) tail = curr;
			src_it = src_it->next;
			++size;
		}
	}

public:
	DoubleSortedLinkedList() = default;
	DoubleSortedLinkedList(std::initializer_list<int> initList) {
		for (auto n : initList) add(n);
	}

	DoubleSortedLinkedList(const DoubleSortedLinkedList& other) {
		copyList(other);
	}
	DoubleSortedLinkedList(DoubleSortedLinkedList&& other) :
		head{ other.head }, tail{ other.tail }, size{ other.size }{
		other.head = other.tail = nullptr;
		other.size = 0;
	}
	virtual ~DoubleSortedLinkedList() {
		clear();
	}
	bool isEmpty() const noexcept {
		return head == nullptr;
	}
	bool isFull() const noexcept {
		return false;
	}
	int getSize() const noexcept {
		return size;
	}
	void clear() {
		Node* curr = head;
		while (curr != nullptr) {
			Node* delNode = curr;
			curr = curr->next;
			delete delNode;
		}
		head = nullptr;
		size = 0;
	}

	const DoubleSortedLinkedList& operator=(const DoubleSortedLinkedList& other) {
		clear();
		copyList(other);
		return *this;
	}
	const DoubleSortedLinkedList& operator=(DoubleSortedLinkedList&& other) {
		clear();
		head = other.head;
		size = other.size;
		other.head = other.tail = nullptr;
		other.size = 0;
		return *this;
	}

	const int& operator[](int index) const {
		if (index >= 0 && index < size) {
			return getNode(index)->item;
		}
		else throw std::range_error("ERROR: [] const");
	}
	int& operator[](int index) {
		if (index >= 0 && index < size) {
			return getNode(index)->item;
		}
		else throw std::range_error("ERROR: []");
	}

	void add(int value) noexcept {
		Node* newNode = new Node(value);
		if (isEmpty()) head = tail = newNode;
		else if (value <= head->item) {
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		else if (value >= tail->item) {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		else {
			Node dummy(0, nullptr, head);
			head->prev = &dummy;
			Node* cur = head;
			while (cur) {
				if (cur->item >= value) {
					cur->prev->next = newNode;
					newNode->prev = cur->prev;
					newNode->next = cur;
					cur->prev = newNode;
				}
				cur = cur->next;
			}
			head = dummy.next;
			head->prev = nullptr;
		}
		++size;
	}
	int peekFront() const {
		if (isEmpty()) throw std::runtime_error("ERROR: peekFront");
		return head->item;
	}
	int popFront() {
		if (isEmpty()) throw std::runtime_error("ERROR: peekFront");
		int temp = head->item;
		Node* delNode = head;
		head = head->next;
		if (head) head->prev = nullptr;
		else tail = nullptr;
		--size;
		delete delNode;
		return temp;
	}
	int peekBack() const {
		if (isEmpty()) throw std::runtime_error("ERROR: peekBack");
		return tail->item;
	}
	int popBack() {
		if (isEmpty()) throw std::runtime_error("ERROR: peekBack");
		int temp = tail->item;
		Node* prev = tail->prev;
		if (prev) tail->next = nullptr;
		else head = nullptr;
		--size;
		delete tail;
		tail = prev;
		return temp;
	}
	bool find(int key) const {
		if (isEmpty()) return false;
		Node* cur = head;
		while (cur) {
			if (cur->item == key) return true;
			if (cur->item > key) return false;
			cur = cur->next;
		}
		return false;
	}
	void removeFirst(int key) {
		Node dummy(0, nullptr, head);
		head->prev = &dummy;
		Node* cur = head;
		while (cur) {
			if (cur->item == key) {
				if (cur->next) cur->next->prev = cur->prev;
				cur->prev->next = cur->next;
				delete cur;
				--size;
				break;
			}
			if (cur->item > key) break;
			cur = cur->next;
		}
		head = dummy.next;
		if (head) head->prev = nullptr;
	}
	void removeAll(int key) {
		Node dummy(0, nullptr, head);
		head->prev = &dummy;
		Node* cur = head;
		while (cur) {
			Node* next = cur->next;
			if (cur->item == key) {
				if (cur->next) cur->next->prev = cur->prev;
				cur->prev->next = cur->next;
				delete cur;
				--size;
			}
			if (cur->item > key) break;
			cur = next;
		}
		head = dummy.next;
		if (head) head->prev = nullptr;
	}
	ListIterator begin() { return ListIterator(head); }
	ListIterator end() { return ListIterator(nullptr); }
};

#endif /* DOUBLESORTEDLINKEDLIST_H_ */

