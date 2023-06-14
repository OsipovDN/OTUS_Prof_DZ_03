#pragma once
#include <iostream>

template <typename T, typename _Alloc = std::allocator<T>>
class List {
	struct Node {
		T val;
		Node* next;
		Node(const T& count) :val(count), next(nullptr) {}
	};
	Node* first;
	Node* last;
	size_t size;

	using nAlloc = typename _Alloc::template rebind<Node>::other;
	nAlloc nd;
public:
	List() :first(nullptr), last(nullptr), size(0) {};
	explicit List(const T& val);
	bool is_empty()const { return first == nullptr; };
	void push_back(const T& val);
	void print() {
		Node* tmp = first;
		while (tmp != nullptr) {
			std::cout << tmp->val << " ";
			tmp = tmp->next;
		}
		std::cout << std::endl;
	}
	~List();
};
template <typename T, typename  _Alloc>
List<T, _Alloc>::List(const T& val) :List() {
	first = last = std::allocator_traits<nAlloc>::allocate(nd, 1);
	std::allocator_traits<nAlloc>::construct(nd, first, val);
	size += 1;
}

template <typename T, typename _Alloc>
List<T, _Alloc>::~List() {
	Node* temp = first;
	Node* buf = nullptr;
	while (temp->next != nullptr) {
		buf = temp->next;
		std::allocator_traits<nAlloc>::destroy(nd, temp);
		std::allocator_traits<nAlloc>::deallocate(nd, temp,1);
		temp = buf;
	}
	std::allocator_traits<nAlloc>::destroy(nd, temp);
	std::allocator_traits<nAlloc>::deallocate(nd, temp, 1);
}

template <typename T, typename _Alloc>
void List<T, _Alloc>::push_back(const T& val) {
	Node* temp = std::allocator_traits<nAlloc>::allocate(nd, 1);
	std::allocator_traits<nAlloc>::construct(nd, temp, val);
	if (size == 0)
		first = last = temp;
	else{
		last->next = temp;
		last = temp;
	}
	size += 1;
	return;

}









