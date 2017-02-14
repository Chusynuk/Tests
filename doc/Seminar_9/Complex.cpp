/*
 * SEMINAR 9
 * FILE:   Complex.cpp
 */

#include <stdio.h>
#include <iostream>

using namespace std;

/* COMPLEX TEMPLATES */

template <typename tempComplex> 
class Complex {

	private:
		tempComplex Re, Im;

	public:
		
		// Constructor for any type
		Complex ( tempComplex re, tempComplex im ) : Re( re ), Im( im ) {}
		
		// Methods to get both Real and Imaginary parts
		tempComplex getRe() { return Re; }
		tempComplex getIm() { return Im; }

		// In order to manipulate easily through complex numbers
		template <typename C> friend ostream& operator << ( ostream & , const Complex<C> & );
		template <typename C> friend Complex<C> operator + ( const Complex<C> & , const Complex<C> & );
		template <typename C> friend Complex<C> operator * ( const Complex<C> & , const Complex<C> & );
};

template <typename tempComplex>
ostream& operator << ( ostream & os, const Complex<tempComplex> & C )
{
	os << "( " << C.Re << " ) + ( " << C.Im << " ) * i";
	return os;
}

template <typename tempComplex>
Complex<tempComplex> operator + ( const Complex<tempComplex> & C1, const Complex<tempComplex> & C2 )
{
	// (a + bi) + (c + di) = (a + c) + (b + d) * i
	Complex<tempComplex> add ( (C1.Re + C2.Re) , (C1.Im + C2.Im) );		

	return add;
}

template <typename tempComplex>
Complex<tempComplex> operator * ( const Complex<tempComplex> & C1, const Complex<tempComplex> & C2 )
{
	// (a + bi) * (c + di) = (ac - bd) + (ad + bc) * i 
	Complex<tempComplex> mult ( (C1.Re * C2.Re)-(C1.Im * C2.Im) , (C1.Re * C2.Im ) + ( C1.Im * C2.Re ) );				

	return mult;
}

int main( int argc, char** argv ) {

	/* COMPLEX EXAMPLE */
    Complex<int> C1(5,3), C2(2,6);
    std::cout << "\nINT COMPLEX EXAMPLE:\nC1 (5,3):\t" << C1 << "\n";
    std::cout << "C1 Real:\t" << C1.getRe() << "\n";
    std::cout << "C1 Imaginary:\t" << C1.getIm() << " * i" << "\n";
    std::cout << "C2 (2,6):\t" << C2 << "\n";
    std::cout << "\nC1 + C2:\t" << C1 + C2 << "\n";
    std::cout << "C1 * C2:\t" << C1 * C2 << "\n";

    Complex<double> C3(3.5,8.3), C4(4.7,8.1);
    std::cout << "\nDOUBLE COMPLEX EXAMPLE:\nC3 (3.5,8.3):\t" << C3 << "\n";
    std::cout << "C3 Real:\t" << C3.getRe() << "\n";
    std::cout << "C3 Imaginary:\t" << C3.getIm() << " * i" << "\n";
    std::cout << "C4 (4.7,8.1):\t" << C4 << "\n";
    std::cout << "\nC3 + C4:\t" << C3 + C4 << "\n";
    std::cout << "C3 * C4:\t" << C3 * C4 << "\n\n";

}
