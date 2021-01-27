#include <iostream>
#include "intbox.hh"

intbox::~intbox() {}
 
singleton::singleton(int value) {
	this->value = value;
}

bool singleton::contains(int a) const {
	if(value == a) {
		return true;
	}
	return false;
}

void singleton::show(std::ostream& s) const {
	s << value;
}

interval::interval(int low, int high) {
	this->low = low;
	this->high = high;
}

bool interval::contains(int a) const {
	if(low > high) {
		throw "low should be less than high\n";
	}
	if(low <= a && high >= a) {
		return true;
	}
	return false;
}

void interval::show(std::ostream& s) const {
s << "[" << low << "," << high << "]";
}

collection::collection(size_t size) {
	this->size = size;
	clt = new intbox*[this->size]();
}
collection::~collection() {
	for(int i = 0; i < size; i++) {
		delete clt[i];
	}
	delete[] clt;
}

void collection::set_item(unsigned i, intbox* item) {
	clt[i] = item;
}

bool collection::contains(int a) const {
	for(int i = 0; i < size; i++) {
		if(clt[i] != nullptr) {
			if(clt[i]->contains(a)) {
				return true;
			}
		}
	}
	return false;
}

void collection::show(std::ostream& s) const {
	s << "{";
	if(size == 0) {
		s << "}";
		return;
	}
	
	for(int i = 0; i < size - 1; i++) {
		if(clt[i] != nullptr) {
			clt[i]->show(s);
			s << ",";
		}
	}
	clt[size - 1]->show(s);
	s << "}";
}
// int main() {
	// intbox* sing1 = new singleton(6);

	// collection* c1 = new collection(2);
	// intbox* sing2 = new singleton(9);
	// intbox* sing3 = new singleton(13);
	// c1->set_item(0, sing2);
	// c1->set_item(1, sing3);
	
	// intbox* int1 = new interval(1, 5);
	
	// collection* c2 = new collection(3);
	// c2->set_item(0, sing1);
	// c2->set_item(1, c1);
	// c2->set_item(2, int1);
	// c2->show(std::cout);
	
// }