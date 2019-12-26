#ifndef DOUBLEUNSORTEDLINKEDLIST_H_
#define DOUBLEUNSORTEDLINKEDLIST_H_
#include <stdexcept>
#include <iterator>

class DoubleUnsortedLinkedList {
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
	// 복사생성자, 대입연산자를 위한 놈 > tail 세팅해줘야됨
	void copyList(const DoubleUnsortedLinkedList& srcList) noexcept {
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
			// 이거만 추가하면됨
			// 원래 복사하려던놈의 tail이 오면 내가 만든 리스트에서도 그 노드를 tail로 만들어준다.
			if (src_it == srcList.tail) tail = curr;
			src_it = src_it->next;
			++size;
		}
	}

public:
	DoubleUnsortedLinkedList() = default;
	DoubleUnsortedLinkedList(std::initializer_list<int> initList) {
		for (auto it = std::rbegin(initList); it != std::rend(initList); ++it)
			pushFront(*it);
	}

	DoubleUnsortedLinkedList(const DoubleUnsortedLinkedList& other) {
		copyList(other);
	}
	// 이동 복사생성자
	DoubleUnsortedLinkedList(DoubleUnsortedLinkedList&& other) :
		head{ other.head }, size{ other.size }, tail{ other.tail } {
		other.head = nullptr;
		other.size = 0;
	}
	virtual ~DoubleUnsortedLinkedList() {
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

	const DoubleUnsortedLinkedList& operator=(const DoubleUnsortedLinkedList& other) {
		clear();
		copyList(other);
		return *this;
	}
	// 이동 >> 걔가 갖고있던걸 내껄로 만드는 것 & 걔가 반납해도 내꺼는 반납하면 안됨
	const DoubleUnsortedLinkedList& operator=(DoubleUnsortedLinkedList&& other) {
		clear();
		head = other.head;
		tail = other.tail;
		size = other.size;
		other.head = nullptr;
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

	void pushFront(int value) noexcept {
		Node* newNode = new Node(value);
		if (isEmpty()) head = tail = newNode;
		else {
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		++size;
	}

	int peekFront() const {
		if (isEmpty()) throw std::runtime_error("ERROR: peekFront");
		return head->item;
	}

	int popFront() {
		if (isEmpty()) throw std::runtime_error("ERROR: popFront");
		Node* delNode = head;
		int temp = delNode->item;
		head = head->next;
		if (head) head->prev = nullptr;
		else tail = nullptr;
		delete delNode;
		--size;
		return temp;
	}

	void pushBack(int value) noexcept {
		Node* newNode = new Node(value);
		if (isEmpty()) head = tail = newNode;
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		++size;
	}

	int peekBack() const {
		if (isEmpty()) throw std::runtime_error("ERROR: peekBack");
		return tail->item;
	}

	int popBack() {
		if (isEmpty()) throw std::runtime_error("ERROR: popBack");
		int temp = tail->item;
		Node* prev = tail->prev;
		if (prev) prev->next = nullptr;
		else head = nullptr;
		delete tail;
		tail = prev;
		--size;
		return temp;
	}

	bool find(int key) const {
		if (isEmpty()) return false;
		Node* cur = head;
		while (cur != nullptr) {
			if (cur->item == key) return true;
			cur = cur->next;
		}
		return false;
	}

	void removeFirst(int key) {
		if (isEmpty()) return;
		Node* cur = head;
		while (cur) {
			if (cur->item == key) {
				if (cur == tail) tail = cur->prev;
				if (cur->prev) cur->prev->next = cur->next;
				else head = cur->next;
				if (cur->next) cur->next->prev = cur->prev;
				delete cur;
				--size;
				break;
			}
			cur = cur->next;
		}
	}

	void removeAll(int key) {

		Node* curr = head;
		while (curr) {
			if (curr->item == key) {
				Node* next{ curr->next };

				if (curr->prev) curr->prev->next = curr->next;
				else head = curr->next;
				if (curr->next) curr->next->prev = curr->prev;
				delete curr;
				curr = next;
				--size;
			}
			else curr = curr->next;
		}
	}
	ListIterator begin() { return ListIterator(head); }
	ListIterator end() { return ListIterator(nullptr); }
};

#endif /* DOUBLEUNSORTEDLINKEDLIST_H_ */
