#include <iostream>

class rational {
	private:
	long int numer, denom;
	public:
	rational();
	rational(long int rational); 
	rational(long int numer, long int denom); 
	long int getNumer();
	long int getDenom();
	void setNumer(long int n);
	void setDenom(long int d);
	rational operator+(rational r);
	rational operator-(rational r);
	rational operator*(rational r);
	rational operator/(rational r);
};

std::ostream& operator<<(std::ostream& out, rational r);