#ifndef SINGLEUNSORTEDLINKEDLIST_H_
#define SINGLEUNSORTEDLINKEDLIST_H_
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class SingleUnsortedLinkedList {
private:
	struct Node {
		int item = 0;
		Node* next = nullptr;
		Node() = default;
		Node(int value, Node* next = nullptr) : item(value), next(next) {}
	};
	class ListIterator : public std::iterator<std::input_iterator_tag, int> {
		Node* p;
	public:
		explicit ListIterator(Node* p) : p{ p } {}
		ListIterator& operator++() noexcept {
			p = p->next; return *this;
		}
		ListIterator operator++(int) noexcept {
			ListIterator retval = *this; p = p->next; return retval;
		}
		bool operator==(const ListIterator& other) const noexcept { return p == other.p; }
		bool operator!=(const ListIterator& other) const noexcept { return p != other.p; }
		int operator*() const noexcept { return p->item; }
	};

	Node* head = nullptr;
	int size = 0;
	Node* getNode(int index) const {
		Node* cur = head;
		if (index >= 0 && index < size) {
			for (int i = 0; i < index; i++)
				cur = cur->next;
			return cur;
		}
		else throw std::range_error("ERROR: getNode(int)");
	}

	void copyList(const SingleUnsortedLinkedList& srcList) noexcept {
		Node* src_it{ srcList.head };
		Node* curr{ head };
		while (src_it) {
			Node* newNode = new Node(src_it->item);
			if (curr == nullptr) {
				head = newNode;
			}
			else {
				curr->next = newNode;
			}
			curr = newNode;
			src_it = src_it->next;
			++size;
		}
	}
public:
	SingleUnsortedLinkedList() = default;
	SingleUnsortedLinkedList(std::initializer_list<int> initList) noexcept {
		for (auto it = std::rbegin(initList); it != std::rend(initList); it++) {
			pushFront(*it);
		}
	}
	SingleUnsortedLinkedList(const SingleUnsortedLinkedList& other) noexcept {
		copyList(other);
	}
	SingleUnsortedLinkedList(SingleUnsortedLinkedList&& other) noexcept {
		size = other.size;
		head = other.head;
		other.head = nullptr;
	}
	virtual ~SingleUnsortedLinkedList() {
		clear();
	}

	bool isEmpty() const noexcept {
		// return size==0;
		return head == nullptr;
	}
	bool isFull() const noexcept {
		return false;
	}
	int getSize() const noexcept {
		return size;
	}
	void clear() noexcept {
		Node* curr{ head };
		while (curr) {
			Node* delNode{ curr };
			curr = curr->next;
			delete delNode;
		}
		size = 0;
	}

	const SingleUnsortedLinkedList& operator=(const SingleUnsortedLinkedList& other) noexcept {
		clear();
		copyList(other);
		return *this;
	}
	const SingleUnsortedLinkedList& operator=(SingleUnsortedLinkedList&& other) noexcept {
		clear();
		size = other.size;
		head = other.head;
		other.head = nullptr;
		return *this;
	}
	int operator[](int index) const {
		return getNode(index)->item;
	}
	int& operator[](int index) {
		return getNode(index)->item;
	}

	void pushFront(int value) noexcept {
		Node* newNode = new Node(value, head);
		head = newNode;
		++size;
	}

	int popFront() {
		if (isEmpty()) throw std::runtime_error("ERROR: popFront");
		int temp = head->item;
		Node* delNode = head;
		head = head->next;
		delete delNode;
		--size;
		return temp;
	}

	void pushBack(int value) noexcept {
		if (isEmpty()) pushFront(value);
		else {
			Node* newNode = new Node(value);
			Node* cur = head;
			while (cur->next) {
				cur = cur->next;
			}
			cur->next = newNode;
			++size;
		}
	}
	int popBack() {
		if (isEmpty()) throw std::runtime_error("ERROR: popBack");
		if (size == 1) return popFront();
		Node* cur = head;
		while (cur->next->next) cur = cur->next;
		int temp = cur->next->item;
		delete cur->next;
		cur->next = nullptr;
		--size;
		return temp;
	}

	int peekFront() const {
		if (isEmpty()) throw std::runtime_error("ERROR: peekFront");
		return head->item;
	}

	int peekBack() const {
		if (isEmpty()) throw std::runtime_error("ERROR: peekFront");
		Node* cur = head;
		while (cur->next) {
			cur = cur->next;
		}
		return cur->item;
	}

	bool find(int key) const noexcept {
		Node* cur = head;
		while (cur) {
			if (cur->item == key) return true;
			cur = cur->next;
		}
		return false;
	}

	void removeFirst(int key) noexcept {
		Node dummy(0, head);
		Node* prev = &dummy;
		Node* cur = head;
		while (cur) {
			if (cur->item == key) {
				prev->next = cur->next;
				delete cur;
				--size;
				head = dummy.next;
				break;
			}
			prev = cur;
			cur = cur->next;
		}
	}

	void removeAll(int key) noexcept {
		Node dummy(0, head);
		Node* prev = &dummy;
		Node* cur = head;
		while (cur) {
			if (cur->item == key) {
				Node* next = cur->next;
				prev->next = next;
				delete cur;
				cur = next;
				--size;
			}
			else {
				prev = cur;
				cur = cur->next;
			}
		}
		head = dummy.next;
	}

	void reverse() noexcept {
		if (size <= 1) return;
		Node* cur = head;
		Node* rev = nullptr;
		// cur를 끝까지 가면서 계속 뒤를 가르키게 한다.
		while (cur) {
			Node* next = cur->next;
			cur->next = rev;
			rev = cur;
			cur = next;
		}
		head = rev;
	}

	int middle() const noexcept {
		Node dummy(-1, head);
		Node* left = &dummy;
		Node* right = &dummy;
		// 하나는 한칸, 하나는 두칸씩 이동한다.
		while (right) {
			left = left->next;
			right = right->next;
			if (right) right = right->next;
		}
		return left->item;
	}

	int getNthFromBack(int index) {
		Node dummy(-1, head);
		Node* target = &dummy;
		Node* cur = &dummy;
		for (int i = 0; i < index + 1; i++) {
			cur = cur->next;
		}
		while (cur) {
			target = target->next;
			cur = cur->next;
		}
		return target->item;
	}
	ListIterator begin() { return ListIterator(head); }
	ListIterator end() { return ListIterator(nullptr); }
};

#endif /* SINGLEUNSORTEDLINKEDLIST_H_ */
