#ifndef _BERKANTEBER_TEBER_BERKAN_HW5_POLYNOMIAL_H
#define _BERKANTEBER_TEBER_BERKAN_HW5_POLYNOMIAL_H

#include <iostream>
#include <cmath>	// to use power function (in operator ())

using namespace std;


class Polynomial
{
private:
	
	int order;
	double* coefficient;	// coefficient array will be dynamically allocated

public:

	Polynomial ();							// defeault constructor
	Polynomial (int order);					// constructor with given order
	Polynomial (const Polynomial &copy);	// copy constructor
	~Polynomial ();							// destructor

	int readOrder () const;								// access & read order
	double readCoefficient (int order) const;			// access & read coefficient of given order
	void changeCoefficient (int order, double value);	// access & change coefficient of given order
	void recalculateOrder ();							// recalculates order and shrinks it if it is necessary

	Polynomial operator = (const Polynomial & rhs);		// operator =
	bool operator > (const Polynomial & rhs);			// operator >
	bool operator < (const Polynomial & rhs);			// operator <
	double operator () (const double & value);			// operator ()
	Polynomial operator ~ ();							// operator ()
};


istream & operator >> (istream & is, Polynomial & polynomial);			// operator >>
ostream & operator << (ostream & os, const Polynomial & polynomial);	// operator <<

Polynomial operator + (const Polynomial & lhs, const Polynomial & rhs);	// operator +
Polynomial operator += (Polynomial & lhs, const Polynomial & rhs);		// operator +=
Polynomial operator / (const Polynomial & lhs, const double & rhs);		// operator /

#endif