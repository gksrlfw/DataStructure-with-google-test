#ifndef SINGLESORTEDLINKEDLIST_H_
#define SINGLESORTEDLINKEDLIST_H_
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class SingleSortedLinkedList {
private:
	// =============================== //
	struct Node {
		int item{ 0 };
		Node* next{ nullptr };
		Node() = default;
		Node(int value, Node* next = nullptr) : item{ value }, next{ next }{}
	};
	class ListIterator : public std::iterator<std::input_iterator_tag, int> {
		Node* p;
	public:
		explicit ListIterator(Node* _p) : p(_p) {}
		ListIterator& operator++() noexcept {
			p = p->next; return *this;
		}
		ListIterator operator++(int) noexcept {
			ListIterator retval = *this; p = p->next; return retval;
		}
		bool operator==(ListIterator other) const noexcept { return p == other.p; }
		bool operator!=(ListIterator other) const noexcept { return p != other.p; }
		int operator*() const noexcept { return p->item; }
	};
	// =============================== //
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
	void copyList(const SingleSortedLinkedList& srcList) noexcept {
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
	SingleSortedLinkedList() = default;
	SingleSortedLinkedList(std::initializer_list<int> initList) noexcept {
		for (auto n : initList) add(n);
	}
	SingleSortedLinkedList(const SingleSortedLinkedList& other) noexcept {
		copyList(other);
	}
	SingleSortedLinkedList(SingleSortedLinkedList&& other) noexcept {
		size = other.size;
		head = other.head;
		tail = other.tail;
		other.head = nullptr;
	}
	virtual ~SingleSortedLinkedList() {
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
		head = nullptr;
		size = 0;
	}

	const SingleSortedLinkedList& operator=(const SingleSortedLinkedList& other) noexcept {
		clear();
		copyList(other);
		return *this;
	}
	const SingleSortedLinkedList& operator=(SingleSortedLinkedList&& other) noexcept {
		clear();
		size = other.size;
		head = other.head;
		tail = other.tail;
		other.head = nullptr;
		return *this;
	}
	int operator[](int index) const {
		return getNode(index)->item;
	}
	//int& operator[](int index){
	//	return getNode(index)->item;
	//}

	int peekFront() const {
		if (isEmpty()) throw std::runtime_error("ERROR: peekFront");
		return head->item;
	}
	int popFront() {
		if (isEmpty()) throw std::runtime_error("ERROR: popFront");
		int retval{ head->item };
		Node* delNode{ head };
		head = head->next;
		if (head == nullptr) tail = nullptr;
		delete delNode;
		return retval;
	}
	void add(int value) noexcept {
		Node* newNode{ new Node{value} };
		if (isEmpty()) {
			head = tail = newNode;
		}
		else if (value <= head->item) {
			newNode->next = head;
			head = newNode;
		}
		else if (value >= tail->item) {
			tail->next = newNode;
			tail = newNode;
		}
		else {
			Node* curr{ head };
			Node* prev{ nullptr };
			while (curr) {
				if (value <= curr->item) {
					prev->next = newNode;
					newNode->next = curr;
					break;
				}
				else {
					prev = curr;
					curr = curr->next;
				}
			}
		}
		++size;
	}
	int peekBack() const {
		if (isEmpty()) throw std::runtime_error("ERROR: peekBack");
		return tail->item;
	}
	int popBack() {
		if (isEmpty()) throw std::runtime_error("ERROR: popBack");
		if (size == 1) {
			return popFront();
		}
		else {
			Node* prev{ head };
			while (prev->next != tail) {
				prev = prev->next;
			}
			int retval{ tail->item };
			prev->next = nullptr;
			delete tail;
			tail = prev;
			--size;
			return retval;
		}
	}
	bool find(int key) const noexcept {
		Node* curr{ head };
		while (curr) {
			if (curr->item == key) return true;
			else if (curr->item > key) return false;
			curr = curr->next;
		}
		return false;
	}
	void removeFirst(int key) noexcept {
		Node dummy{ -1,head };
		Node* prev{ &dummy };
		Node* curr{ head };
		while (curr) {
			if (curr->item == key) {
				prev->next = curr->next;
				if (curr == tail) tail = (prev == &dummy) ? nullptr : prev;
				delete curr;
				--size;
				head = dummy.next;
				break;
			}
			else if (curr->item > key) break;
			else {
				prev = curr;
				curr = curr->next;
			}
		}
	}
	void removeAll(int key) noexcept {
		Node dummy{ -1,head };
		Node* prev{ &dummy };
		Node* curr{ head };
		while (curr) {
			if (curr->item == key) {
				Node* next{ curr->next };
				prev->next = curr->next;
				if (curr == tail) tail = (prev == &dummy) ? nullptr : prev;
				delete curr;
				curr = next;
				--size;
			}
			else if (curr->item > key) break;
			else {
				prev = curr;
				curr = curr->next;
			}
		}
		head = dummy.next;
	}
	ListIterator begin() { return ListIterator(head); }
	ListIterator end() { return ListIterator(nullptr); }
};

#endif /* SINGLESORTEDLINKEDLIST_H_ */
