#pragma once
#include <cstdlib>
#include <iostream>
using namespace std;

template <class T>
struct Node {

	T data;
	Node<T>* next = 0;

	Node() {}

	Node(T d):data(d){}

	Node(const Node<T> &n) {
		data = n.data;
		if (n.next != 0) next = new Node<T>(n.next->data);
	}

	Node<T>* operator=(Node<T> &n) {
		data = n.data;
		next = n.next;
		return *this;
	}

};

template <class T>
class List {

protected:
	Node<T>* head;
	int size;

public:
	List():size(0) {
		head = new Node<T>();
	}

	List(const List &l) {
		head = new Node<T>(*l.head);
		size = l.size;
		if (size > 1) {
			Node<T>* temp = head;
			Node<T>* temp2 = l.head->next;
			while (temp2->next != 0) {
				temp->next = new Node<T>(*temp2);
				temp = temp->next;
				temp2 = temp2->next;
			}
		}
	}

	Node<T>* getTail() {
		if (size == 0) return NULL;
		else {
			Node<T>* temp = head;
			while (temp->next != 0) temp = temp->next;
			return temp;
		}
	}

	void push_back(T data) {
		if (size == 0) {
			head->data = data;		
			size++;
		}
		else {
			Node<T>* temp = new Node<T>(data);
			getTail()->next = temp;
			size++;
		}
	}

	T pop_back() {
		if (size == 0) return T();
		if (size == 1) {
			T res = head->data;
			head->data = 0; size--;
			return res;
		}
		else {
			Node<T>* temp = head;
			Node<T>* tail = getTail();
			T res = tail->data;
			while (temp->next != tail) temp = temp->next;
			temp->next = 0; size--;
			delete tail;
			return res;
		}
	}

	void print() {
		if (size >= 1) {
			Node<T>* temp = head;
			for (temp = head; temp; temp = temp->next) cout << temp->data << " ";
			cout << endl;
		}
	}

	int getSize() {
		return size;
	}

	void insert(T data, int pos) {
		if (pos > size || pos < 0) return;
		if (pos == 0) {
			Node<T>* res = new Node<T>(data);
			res->next = head;
			head = res;
			size++;
			return;
		}
		if (pos == size) push_back(data);
		else {
			Node<T>* temp_prev = head;
			Node<T>* temp;
			for (int i = 1; i < pos; i++) temp_prev = temp_prev->next;
			temp = temp_prev->next;
			Node<T>* res = new Node<T>(data);
			temp_prev->next = res;
			res->next = temp;
			size++;
		}
	}

	Node<T>* remove(int pos) {
		if (pos >= size || pos < 0) return NULL;
		if (pos == 0) {
			head->data = 0; size--;
			return head;
		}
		if (pos == size - 1) {
			pop_back(); 
			return getTail();
		}
		else {
			Node<T>* temp_prev = head;
			Node<T>* temp;
			for (int i = 1; i < pos; i++) temp_prev = temp_prev->next;
			temp = temp_prev->next;
			temp_prev->next = temp->next;
			delete temp; size--;
			return temp_prev;
		}
	}

	Node<T>* remove(Node<T> e) {
		if (size == 0) return NULL;
		if (e.data == head->data) {
			head->data = 0; size--;
			return head;
		}
		if (e.data == getTail()->data) {
			pop_back();
			return getTail();
		}
		else {
			Node<T>* temp_prev = head;
			Node<T>* temp;
			while (temp_prev->next != 0) {
				if (temp_prev->next->data == e.data) {
					temp = temp_prev->next;
					temp_prev->next = temp->next;
					delete temp; size--;
					break;
				}
				temp_prev = temp_prev->next;
			}
			return temp_prev;
		}
	}

};