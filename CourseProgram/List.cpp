#include "List.h"

// constructor
List::List()
{
	size = 0;
	head = nullptr;
	tail = nullptr;
}

// destructor
List::~List()
{
	clear();
}

// inserting an element at the end of the list
void List::push_back(string data)
{
	if (head == nullptr)
	{
		this->head = this->tail = new Node(data);
	}
	else
	{
		Node* temp = new Node(data, nullptr, tail);
		tail->next = temp;
		tail = temp;
	}
	size++;
}

// inserting an element at the beginning of the list
void List::push_front(string data)
{
	if (!(isEmpty()))
	{
		Node* lasthead = head;
		head = new Node(data, head);
		lasthead->prev = head;
	}
	else
	{
		head = new Node(data, head);
	}
	size++;
}

 //remove the last element
void List::pop_back()
{
	if (isEmpty())
		throw "Error! Linked list is Empty.";
	else
	{
		Node* todelete = tail;
		tail = tail->prev;
		delete todelete;
		size--;
	}
}

// remove the first element
void List::pop_front()
{
	if (head != nullptr) {
		Node* temp = this->head;
		head = head->next;
		delete temp;
		size--;
	}
	else throw "Error! Linked list is Empty.";
}

// clear list
void List::clear()
{
	while (size) {
		pop_front();
	}
}

// getting list size
size_t List::GetSize()
{
	return size;
}

// output the list to the console
void List::print_to_console()
{
	Node* cursor = head;
	if (head)
	{
		while (cursor->next)
		{
			std::cout << cursor->data << " ";
			cursor = cursor->next;
		}
		std::cout << cursor->data;
		std::cout << std::endl;
	}
	else throw "Error! List is empty.";
}

// getting an element by index
string List::at(const int index)
{
	if (index >= size || index < 0)
		throw "Error! Incorrect input.";
	int counter = 0;
	Node* current = head;
	while (current != nullptr)
	{
		if (counter == index)
			return current->data;
		current = current->next;
		counter++;
	}
}

// checking the list for emptiness
bool List::isEmpty()
{
	if (head == nullptr)
		return true;
	else return false;
}

// replacing the element by index with the passed element
void List::set(size_t index, string data)
{
	if (index >= size || index < 0)
		throw "Error! Incorrect input.";
	Node* cursor = head;
	for (size_t i = 0; i < index; i++)
		cursor = cursor->next;
	cursor->data = data;
}

// insert into an arbitrary place in the list by index
void List::insert(string data, size_t index)
{
	if (!isEmpty())
	{
		if (index >= size || index < 0)
			throw "Error! Incorrect input.";
	}
	else
	{
		if (index != size)
			throw "Error! Incorrect input.";
	}
	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		if (index == size)
			push_back(data);
		else {
			if (index < (size - 1) / 2)
			{
				Node* previous = this->head;
				for (size_t i = 0; i < index - 1; i++)
				{
					previous = previous->next;
				}
				previous->next = new Node(data, previous->next, previous);
			}
			else
			{
				Node* previous = this->tail;
				for (size_t i = size - 1; i > index - 1; i--)
				{
					previous = previous->prev;
				}
				previous->next = new Node(data, previous->next, previous);
			}
			size++;
		}
	}
}

// êeverse the order of items in the list
void List::reverse()
{
	if (head == nullptr)
		throw "Error! Linked list is empty.";
	if (!head || !head->next)
		return;
	tail = head;
	Node* temp = nullptr;
	Node* current = head;
	while (current != nullptr)
	{
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	head = temp->prev;
}

// deleting an element by index
void List::remove(size_t index)
{
	if (index >= size || index < 0)
		throw "Error! Incorrect input.";	
	if (index == 0)
		this->pop_front();
	else if (index == size - 1)
		this->pop_back();
	else {
		Node* cursor = head;
		for (size_t i = 0; i < index; i++) 
		{
			cursor = cursor->next;	
		}			
		Node* temp = cursor;
		cursor->prev->next = cursor->next;
		cursor->next->prev = cursor->prev;
		delete temp;
		size--;
	}
	
}

// getting the first item in the list
string List::top()
{
	if (head)	
		return head->data;
	else throw "Error! Stack is empty.";
}
