#include "berkanteber_Teber_Berkan_HW5_polynomial.h"

/********************************************************/
/******************* MEMBER FUNCTIONS *******************/
/********************************************************/

/**************  Constructors & Destructor  **************/

// default constructor
Polynomial::Polynomial ()
{
	order = 0;
	coefficient = new double;
}

// constructor with given order
Polynomial::Polynomial (int n)
{
	order = n;
	coefficient = new double [order + 1];
}

// copy constructor
Polynomial::Polynomial (const Polynomial &copy)
{
	order = copy.order;
	coefficient = new double [order + 1];

	for (int i = 0; i <= order; i++)
		coefficient[i] = copy.coefficient[i];
}

// destructor
Polynomial::~Polynomial ()
{
	delete [] coefficient;
}


/*****************  Accessors & Mutators  *****************/

// access & read order
int Polynomial::readOrder () const
{
	return order;
}

// access & read coefficient of given order
double Polynomial::readCoefficient (int n) const
{
	return coefficient[n];
}

// access & change coefficient of given order
void Polynomial::changeCoefficient (int n, double value)
{
	coefficient[n] = value;
	return;
}

// recalculates order and shrinks if it is necessary
void Polynomial::recalculateOrder ()
{
	while (!coefficient[order] && order)	// shrinks the order until coefficient is 1 or order is 0
		order--;
}


/**********************  Operators  *********************/

// =
Polynomial Polynomial::operator= (const Polynomial & rhs)
{
	if (this != &rhs)	// unless they are already same (to prevent self destructing)
	{
		this->~Polynomial();		// destruct old one
		
								// construct new one and assign rhs to it
		order = rhs.readOrder();
		coefficient = new double[order + 1];
		for (int i = 0; i <= order; i++)
			coefficient[i] = rhs.coefficient[i];
	}
	
	return *this;
}
	
// >
bool Polynomial::operator > (const Polynomial & rhs)
{
	if (order > rhs.readOrder())	// if lhs is greater, return true
		return true;
	else							// else, return false
		return false;
}

// <
bool Polynomial::operator < (const Polynomial & rhs)
{
	if (order < rhs.readOrder())	// if lhs is smaller, return true
		return true;
	else							// else, return false
		return false;
}

// ()
double Polynomial::operator() (const double & value)
{
	double result = 0;

	for (int i = 0; i <= order; i++)				// sum for all orders
		result += coefficient[i] * pow(value, i);	// add coefficient * (value^order)

	return result;
}

// ~
Polynomial Polynomial::operator~ ()
{
	if (order == 0)	// if polynomial is constant, create a derivative polynomial = 0 and return it 
	{
		Polynomial derivative;
		derivative.coefficient[0] = 0;
		return derivative;
	}

	else	// create a derivative polynomial with (order - 1) and calculate new coefficients
	{
		Polynomial derivative (order - 1);

		for (int i = 0; i < order; i++)
			derivative.coefficient[i] = coefficient[i + 1] * (i + 1);
		
		return derivative;
	}
}



/********************************************************/
/*******************  FREE FUNCTIONS  *******************/
/********************************************************/

/**********************  Operators  *********************/

// >>
istream & operator >> (istream & is, Polynomial & polynomial)
{
	double val;
	int order = polynomial.readOrder();

	for (int i = order; i >= 0; i--)			// for all orders
	{
		is >> val;								// read and
		polynomial.changeCoefficient(i, val);	// change coefficient
	}

	polynomial.recalculateOrder();	// recalculates order and shrinks if it is necessary

	return is;
}

// <<
ostream & operator << (ostream & os, const Polynomial & polynomial)
{
	int order = polynomial.readOrder();
	double coefficient;
	
	if (order == 0 && polynomial.readCoefficient(0) == 0)	// if p(x) = 0
		os << "0";

	else	// p(x) != 0
	{
		for (int i = order; i >= 0; i--)		// for all orders
		{
			coefficient = polynomial.readCoefficient(i);

			if (coefficient)	// if coefficient is not 0
			{
				// write coefficients and signs

				if (i == order)	// first term
				{
					if (coefficient == -1)
						os << "-";
					else if (coefficient == 1)
						os << "";
					else 
						os << coefficient;
				}

				else			// other than first term
				{
					if (coefficient == -1)
						os << "-";
					else if (coefficient == 1)
						os << "+";
					else if (coefficient < 0)
						os << coefficient;
					else if (coefficient > 0)
						os << "+" << coefficient;
				}


				// write variables 

				if (i > 1)				// x^n, n>1
					os << "x^" << i;
				else if (i == 1)		// x^1
					os << "x";		
				else if (i == 0)		// constant
				{
					if (coefficient == -1 || coefficient == 1)
						os << "1";
				}
					
				os << " ";
			}
		}
	}

	return os;
}

// +
Polynomial operator + (const Polynomial & lhs, const Polynomial & rhs)
{
	// assign order_lhs, order_rhs, order_min, order_max

	int order_lhs = lhs.readOrder();
	int order_rhs = rhs.readOrder();
	int order_min, order_max;

	if (order_lhs >order_rhs)
	{
		order_min = order_rhs;
		order_max = order_lhs;
	}

	else
	{
		order_min = order_lhs;
		order_max = order_rhs;
	}


	// create a new polynomial (sum) with higher order
	Polynomial sum (order_max);

	// assign coefficients until order_min (common orders)
	double val;
	for (int i = 0; i <= order_min; i++)
	{
		val = lhs.readCoefficient(i) + rhs.readCoefficient(i);
		sum.changeCoefficient(i, val);
	}


	// assign coefficients from order_min + 1 to order_max (uncommon orders)

	if (order_max == order_lhs)
		for (int i = order_min + 1; i <= order_max; i++)
			sum.changeCoefficient(i, lhs.readCoefficient(i));
	else
		for (int i = order_min + 1; i <= order_max; i++)
			sum.changeCoefficient(i, rhs.readCoefficient(i));


	// recalculate order and shrink if it is necessary
	sum.recalculateOrder();

	return sum;
}

// +=
Polynomial operator += (Polynomial & lhs, const Polynomial & rhs)
{
	// used + and = operators to define += operator
	
	lhs = lhs + rhs;

	return lhs;
}

// /
Polynomial operator / (const Polynomial & lhs, const double & rhs)
{
	Polynomial result (lhs);	// copy lhs to result
	
	// divide all coefficients of result to rhs
	for (int i = 0; i <= result.readOrder(); i++)
		result.changeCoefficient(i, result.readCoefficient(i)/rhs);

	return result;
}