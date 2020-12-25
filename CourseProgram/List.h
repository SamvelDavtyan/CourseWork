#pragma once
#include <iostream>
#include <string>

using namespace std;

class List
{
public:
	List();
	~List();
	void push_back(string data);
	void push_front(string data);
	void pop_back();
	void pop_front();
	void clear();
	size_t GetSize();
	string at(const int index);
	bool isEmpty();
	void remove(size_t index);
	void set(size_t index, string data);
	void insert(string data, size_t index);
	void reverse();
	void print_to_console();
	string top();
private:

	class Node
	{
	public:
		Node* next;
		Node* prev;
		string data;
		Node(string data ="\0", Node* next = nullptr, Node* prev =nullptr)
		{
			this->data = data;
			this->next = next;
			this->prev = prev;
		}
	};
	Node* head;
	Node* tail;
	size_t size;
};
