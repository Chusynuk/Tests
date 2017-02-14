/*
 * SEMINAR 9
 * FILE:   Matrix.cpp
 */

#include <stdio.h>
#include <iostream>

using namespace std;

const int rows = 5;
const int cols = 5;

/* MATRIX TEMPLATES */

template <class tempMatrix> 
class Matrix {

	private:
		tempMatrix M[rows][cols];

	public:

		// Constructor
		Matrix ()
		{
			int i, j;

			for ( i=0 ; i<rows ; i++ )
			{
				for ( j=0 ; j<cols ; i++)
				{
					M[i][j] = 0;
				}
			}
		}

		void showMatrix();
		
};

template<class tempMatrix>
void Matrix<tempMatrix>::showMatrix	()
{
	int i, j;

	for ( i=0 ; i<rows ; i++ )
	{
		for ( j=0 ; j<cols ; i++)
		{
			std::cin << M[i][j];
		}
	}
}

template <class tempMatrixe>
ostream& operator << ( ostream & os, const Matrix<tempMatrix> & M )
{
	os << "\n";

	int i, j;

	for ( i=0 ; i<rows ; i++ ) {
		os << "| ";

		for ( j=0 ; j<cols ; j++ )
		{
			os << M[i][j];
			if ( j!=cols-1 )	os << ", ";
		}

		os << " |\n";
	}


	return os;
}

int main( int argc, char** argv ) {

	/* Matrix EXAMPLE */
    Matrix<int> M1(), M2();
    std::cout << "\nINT Matrix EXAMPLE:M1 (5,5):\n" << M1 << "\n";

}