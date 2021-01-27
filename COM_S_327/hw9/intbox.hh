#include <iostream>

class intbox {
	public:
	virtual bool contains(int a) const=0;
	virtual void show(std::ostream& s) const=0;
	virtual ~intbox()=0;
};

class singleton : public intbox {
	protected:
	int value;
	public:
	singleton(int value);
	bool contains(int a) const override;
	void show(std::ostream& s) const override;
};

class interval : public intbox {
	protected:
	int low, high;
	public:
	interval(int low, int high);
	bool contains(int a) const override;
	void show(std::ostream& s) const override;
};

class collection : public intbox {
	protected:
	size_t size;
	intbox** clt;
	public:
	collection(size_t size);
	~collection();
	void set_item(unsigned i, intbox* item);
	bool contains(int a) const override;
	void show(std::ostream& s) const override;
	
	
};