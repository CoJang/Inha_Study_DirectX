// Practice_Matrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyMatrix.h"

int main()
{
	MyMatrix Matrix1(3);
	MyMatrix Matrix2(3);
	MyMatrix Matrix3(3);

	Matrix1[0][0] = 2;  Matrix1[0][1] = 0;  Matrix1[0][2] = 1;
	Matrix1[1][0] = 0; Matrix1[1][1] = -1;  Matrix1[1][2] = -3;
	Matrix1[2][0] = 0; Matrix1[2][1] = 0; Matrix1[2][2] = 1;
	MyMatrix::PrintMatrix(Matrix1);

	MyMatrix::PrintMatrix(MyMatrix::InverseMatrix(Matrix1));

	Matrix3 = MyMatrix::InverseMatrix(Matrix1) * Matrix1;
	MyMatrix::PrintMatrix(Matrix3);

	Matrix2[0][0] = 4; Matrix2[0][1] = 5; Matrix2[0][2] = 5;
	Matrix2[1][0] = 1; Matrix2[1][1] = 7; Matrix2[1][2] = 1;
	Matrix2[2][0] = 1; Matrix2[2][1] = 5; Matrix2[2][2] = 2;

	MyMatrix::PrintMatrix(Matrix1 * Matrix2);


    return 0;
}

