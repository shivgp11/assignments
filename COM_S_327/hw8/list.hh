#include <iostream>
struct node {
	int data;
	struct node* next;
};
class list_builder {
	private:
	struct node** head;
	list_builder(const list_builder& lb);
	list_builder& operator=(const list_builder& lb);
	
	public:
	list_builder();
	~list_builder();
	void add_to_front(int value);
	void add_to_back(int value);
	void reset();
	//additional helper functions
	struct node** getHead() const;
	int count() const;
};
class fixed_list {
	
	private:
	const int* list;
	size_t size;
	fixed_list(const fixed_list& fl);
	fixed_list& operator=(const fixed_list& fl);
	
	public: 
	fixed_list(const list_builder &lb);
	~fixed_list();
	size_t Size() const;
	int operator[](size_t index) const;
	friend std::ostream& operator<<(std::ostream& out, const fixed_list& fl);
};