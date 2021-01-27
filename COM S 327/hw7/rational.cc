#include <iostream>
#include "rational.hh"
#include <cmath>

int gcd(long int a, long int b);
int lcm(int a, int b);
void simplify(rational* r);

rational::rational() {
	this->numer = 0;
	this->denom = 1;
}

rational::rational(long int rational) {
	this->numer = rational;
	this->denom = 1;
}

rational::rational(long int numer, long int denom) {
	
	this->numer = numer;
	this->denom = denom;
	simplify(this);
}

rational rational::operator+(rational r) {
	rational sum;
	long int c = lcm(this->denom, r.denom);
	long int left = this->numer * (c / this->denom);
	long int right = r.numer * (c / r.denom);
	sum.numer = left + right;
	sum.denom = c;
	rational* rp = &sum;
	simplify(rp);
	return sum;
}

rational rational::operator-(rational r) {
	rational difference;
	long int c = lcm(this->denom, r.denom);
	long int left = this->numer * (c / this->denom);
	long int right = r.numer * (c / r.denom);
	difference.numer = left - right;
	difference.denom = c;
	rational* rp = &difference;
	simplify(rp);
	return difference;
}

rational rational::operator*(rational r) {
	rational product;
	product.numer = this->numer * r.numer;
	product.denom = this->denom * r.denom;
	rational* rp = &product;
	simplify(rp);
	return product;
}

rational rational::operator/(rational r) {
	rational quotient;
	quotient.numer = this->numer * r.denom;
	quotient.denom = this->denom * r.numer;
	rational* rp = &quotient;
	simplify(rp);
	return quotient;
}

std::ostream& operator<<(std::ostream& out, rational r) {
	if(r.getDenom() == 1) {
		out << r.getNumer();
	}
	else {
		out << r.getNumer() << "/" << r.getDenom();
	}
	return out;
}

//gets numerator
long int rational::getNumer() {
	return this->numer;
}

//gets denominator
long int rational::getDenom() {
	return this->denom;
}

//sets the numerator
void rational::setNumer(long int n) {
	this->numer = n;
}

//sets the denominator
void rational::setDenom(long int d) {
	this->denom = d;
}

//helper function for greatest common divisor, used to simplify fractions
int gcd(long int a, long int b) { 
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);   
}

//helper function to find least common multiple, used in add and subtract operators
int lcm(int a, int b) {  
    return (a*b)/gcd(a, b);  
 }  
 
//helper method that takes rational pointer and simplifies its numerator and denominator
void simplify(rational* r) {
	long int c = gcd((*r).getNumer(), (*r).getDenom());
	long int n = (*r).getNumer() / c;
	long int d = (*r).getDenom() / c;
	if(d < 0) {
		n *= -1;
		d *= -1;
	}
	(*r).setNumer(n);
	(*r).setDenom(d);
}