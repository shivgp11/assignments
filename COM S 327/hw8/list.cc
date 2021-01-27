#include <iostream>
#include "hw8.hh"

list_builder::list_builder() {
	head = new struct node*();
}

list_builder::~list_builder() {
	(*this).reset();
	delete head;
	head = nullptr;
}

void list_builder::add_to_front(int value) {
	if(*head == nullptr) {
		*head = new struct node();
		(*head)->data = value;
		(*head)->next = nullptr;
	}
	else {
		struct node* newNode = new struct node();
		newNode->data = value;
		newNode->next = *head;
		*head = newNode;
	}
}

void list_builder::add_to_back(int value) {
	if(*head == nullptr) {
		*head = new struct node();
		(*head)->data = value;
		(*head)->next = nullptr;
	}
	else {
		struct node* previous = *head;
		while(previous->next != nullptr) {
			previous = previous->next;
		}
		struct node* newNode = new struct node();
		newNode->data = value;
		newNode->next = nullptr;
		previous->next = newNode;
	}
}

void list_builder::reset() {
	if(*head != nullptr) {
		struct node* current = *head;
		struct node* next;
		while(current != nullptr) {
			next = current->next;
			delete current;
			current = next;
		}
		*head = nullptr;
	}
}
//gives head to the fixed_list
struct node** list_builder::getHead() const {
	
	return head;
}

//helper method that returns the count of nodes in the list_builder
int list_builder::count() const{
	int count = 0;
	struct node* current = *(head);
	while(current != nullptr) {
		count++;
		current = current->next;
	}
	return count;
}

fixed_list::fixed_list(const list_builder& lb) {
	size = lb.count();
	if(size != 0) {
		int* temp = new int[size];
		struct node* current = *(lb.getHead());
		for(int i = 0; i < size; i++) {
			temp[i] = current->data;
			current = current->next;
		}
		list = temp;
	}
}

fixed_list::~fixed_list() {
	if(size != 0) {
		delete[] list;
	}
}

size_t fixed_list::Size() const {
	return size;
}

int fixed_list::operator[](size_t index) const {
	if(list == nullptr) {
		throw "Fixed list is empty\n";
	}
	if(index >= size) {
		throw "Index out of bounds\n";
	}
	return list[index];
}

std::ostream& operator<<(std::ostream& out, const fixed_list& fl) {
	out << "[";
	if(fl.size == 0) {
		out << "]";
		return out;
	}
	if(fl.size == 1) {
		out << (fl.list)[0] << "]";
		return out;
	}
	for(int i = 0; i < fl.Size() - 1; i++) {
		out << (fl.list)[i] << ",";
	}
	out << (fl.list)[fl.Size() - 1] << "]";
	return out;
}




