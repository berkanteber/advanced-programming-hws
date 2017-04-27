/***********************************************************
Berkan Teber berkanteber 19080
************************************************************
HW5 - Operations with Polynomials
***********************************************************/

#include <iostream>
#include "berkanteber_Teber_Berkan_HW5_polynomial.h"

using namespace std;


int main()
{
	int orderOfp1, orderOfp2, orderOfp3, orderOfp4; // order of the first and second polynomials respectively

	cout<<"Enter the order of the first polynomial (p1)"<<endl;
	cin>> orderOfp1; // get order of the first polynomial from user
	Polynomial p1 = Polynomial(orderOfp1); // create polynomial p1

	
	cout<<endl<< "Enter the coefficients for polynomial p1 (starting from the coefficient of the highest order term)"<<endl;
	cin >> p1;

	cout << endl <<"The polynomial p1 is: " << endl << p1 << endl <<endl;

	cout<<"Enter the order of the second polynomial (p2) "<<endl;
	cin>> orderOfp2; // get order of the second polynomial from user
	Polynomial p2 = Polynomial(orderOfp2); // create polynomial p2

	cout<<endl<<"Enter the coefficients for polynomial p2 (starting from the coefficient of the highest order term)"<<endl;
	cin >> p2;

	cout << endl<<"The polynomial p2 is: " << endl<< p2 << endl <<endl; // print p2

	cout<<"Enter the orders of the third (p3) and fourth (p4) polynomials "<<endl;
	cin>> orderOfp3 >> orderOfp4; // get orders of the thirdand fourth polynomials from the user
	
	Polynomial p3 = Polynomial(orderOfp3); // create polynomial p3
	Polynomial p4 = Polynomial(orderOfp4); // create polynomial p4

	cout<<endl<<"Enter the coefficients for polynomials p3 and p4 (starting from the coefficient of the highest order term)"<<endl;
	cin >> p3 >> p4;

	cout << endl<<"The polynomial p3 and p4 are: " << endl << p3 << endl << p4 << endl<<endl;

	p2 = p2; // self assignment

	cout<<"Polynomial p2 after the operation p2 = p2 is: "<< endl << p2 << endl << endl;
	
	Polynomial p5; //default constructor
	p5 = p1 + p2;

	cout << "Polynomial p5 after the operation p5 = p1 + p2: " << endl<< p5 <<endl << endl;

	if(p4 < p5)
		cout<< "The order of p4 is smaller than the order of p5" <<endl<<endl;
	else if (p4 > p5)
		cout<< "The order of p4 is greater than the order of p5" <<endl<<endl;
	else
		cout << "The orders of p4 and p5 are equal" << endl << endl;
	
	Polynomial p6 = Polynomial(p1 / 2.5);
		
	cout << "Polynomial p6 after created by copy constructor Polynomial p6 = Polynomial(p1 / 2.5) is: " << endl << p6 <<endl <<endl;
	
	p1 += p3;
	
	cout << "Polynomial p1 after the operation p1 += p3: " << endl << p1 <<endl <<endl;

	p5 = p1 / 2;
	cout<<"Polynomial p5 after the operation p5 = p1 / 2 is: "<< endl << p5 << endl <<endl;

	p3 = p5 / 5 + p1 / 4;
	cout << "Polynomial p3 after the operation p3 = p5 / 5 + p1 / 4: " << endl << p3 <<endl <<endl;

	Polynomial p7;
	p7 = p3 + p5 + p6;
	cout << "Polynomial p7 after the operation p7 = p3 + p5 + p6: " << endl << p7 <<endl <<endl;

	p2 = p3 += p1 += p4;

	cout << "After the operation p2 = p3 += p1 += p4: " << endl; 
	cout << "Polynomial p1: "<< p1 <<endl;
	cout << "Polynomial p3: "<< p3 <<endl;
	cout << "Polynomial p2: "<< p2 <<endl;

	double x;

	cout<<"Enter an x value to find p1(x) (corresponding value of p1 at x)"<<endl;
	cin >> x;

	cout<<endl<< "p1(x) = "<< p1(x) <<endl<<endl; // find the value of polynomial p1 at given x

	cout << "Enter an x value to find p5(x) (corresponding value of p5 at x)"<<endl;
	cin >> x;

	cout<<endl<< "p5(x) = "<< p5(x) <<endl<<endl; // find the value of polynomial p5 at given x
	
	Polynomial p8 = ~p1;
	cout << "Polynomial p8 after the operation p8 = ~p1: " << endl << p8 <<endl << endl;

	/*
	cout << endl << "Enter an x value to find ~p4(x) (corresponding value of ~p4 at x)"<<endl;
	cin >> x;

	cout<<endl<< "~p4(x) = "<< (~p4)(x) <<endl<<endl;
	*/

	p4 = ~p2 + ~p6;
	cout << "Polynomial p4 after the operation p4 = ~p2 + ~p6: " << endl << p4 <<endl << endl;

	return 0;
}