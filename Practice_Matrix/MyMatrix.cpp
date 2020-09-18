#include "stdafx.h"
#include "MyMatrix.h"


MyMatrix::cRow::cRow(int dimension)
{
	Dimension = dimension;
	for (int i = 0; i < Dimension; i++)
		Datas.push_back(0);
}

MyMatrix::cRow::~cRow()
{
}

void MyMatrix::cRow::Resize(int dimension)
{
	Datas.clear();
	Dimension = dimension;
	for (int i = 0; i < Dimension; i++)
		Datas.push_back(0);
}

float & MyMatrix::cRow::operator[](int index)
{
	return Datas[index];
}

MyMatrix::MyMatrix()
	:Rows()
{
	Dimension = 1;
	Rows = new cRow[Dimension];

	for (int i = 0; i < Dimension; i++)
	{
		Rows[i].Resize(Dimension);
		for (int j = 0; j < Dimension; j++)
			Rows[i][j] = 0;
	}
}

MyMatrix::MyMatrix(int dimension)
	:Rows()
{
	Dimension = dimension;
	Rows = new cRow[Dimension];

	for (int i = 0; i < Dimension; i++)
	{
		Rows[i].Resize(Dimension);
		for (int j = 0; j < Dimension; j++)
			Rows[i][j] = 0;
	}
}

MyMatrix::MyMatrix(const MyMatrix & mat)
	:Rows()
{
	Dimension = mat.Dimension;
	Rows = new cRow[Dimension];

	for (int i = 0; i < Dimension; i++)
	{
		Rows[i].Resize(Dimension);
		for (int j = 0; j < Dimension; j++)
		{
			Rows[i][j] = mat.Rows[i][j];
		}
	}
}

MyMatrix::~MyMatrix()
{
}

bool MyMatrix::operator==(MyMatrix & mat)
{
	if (Dimension != mat.Dimension) return false;

	for (int i = 0; i < Dimension; i++)
	{
		for (int j = 0; j < Dimension; j++)
		{
			if (Rows[i][j] - mat.Rows[i][j] > EPSILON)
				return false;
		}
	}

	return true;
}

bool MyMatrix::operator!=(MyMatrix & mat)
{
	if (Dimension != mat.Dimension) return true;

	for (int i = 0; i < Dimension; i++)
	{
		for (int j = 0; j < Dimension; j++)
		{
			if (Rows[i][j] - mat.Rows[i][j] > EPSILON)
				return true;
		}
	}

	return false;
}

MyMatrix MyMatrix::operator+(MyMatrix & mat)
{
	if (Dimension != mat.Dimension) return MyMatrix();

	for (int i = 0; i < Dimension; i++)
	{
		for (int j = 0; j < Dimension; j++)
		{
			Rows[i][j] += mat.Rows[i][j];
		}
	}

	return *this;
}

MyMatrix MyMatrix::operator-(MyMatrix & mat)
{
	if (Dimension != mat.Dimension) return MyMatrix();

	for (int i = 0; i < Dimension; i++)
	{
		for (int j = 0; j < Dimension; j++)
		{
			Rows[i][j] -= mat.Rows[i][j];
		}
	}

	return *this;
}

// 정방 행렬만 가능
MyMatrix MyMatrix::operator*(MyMatrix & mat)
{
	if (Dimension != mat.Dimension) return MyMatrix();

	MyMatrix temp(Dimension);

	for (int i = 0; i < Dimension; i++)
		for (int j = 0; j < Dimension; j++)
			for (int k = 0; k < Dimension; k++)
			{
				temp.Rows[i][j] += Rows[i][k] * mat.Rows[k][j];
			}
	
	return temp;
}

MyMatrix MyMatrix::operator*(float k)
{
	for (int i = 0; i < Dimension; i++)
	{
		for (int j = 0; j < Dimension; j++)
		{
			Rows[i][j] *= k;
		}
	}

	return *this;
}

MyMatrix MyMatrix::operator/(float k)
{
	if (k == 0) return MyMatrix();

	for (int i = 0; i < Dimension; i++)
	{
		for (int j = 0; j < Dimension; j++)
		{
			Rows[i][j] /= k;
		}
	}

	return *this;
}

void MyMatrix::PrintMatrix(MyMatrix & mat)
{
	for (int i = 0; i < mat.Dimension; i++)
	{
		for (int j = 0; j < mat.Dimension; j++)
		{
			printf("%.2f ", mat.Rows[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

MyMatrix MyMatrix::InverseMatrix(MyMatrix& mat)
{
	if (mat.Determinant() == 0) return MyMatrix();

	return mat.Adjoint() / mat.Determinant();
}

MyMatrix MyMatrix::TransposeMatrix(MyMatrix & mat)
{
	MyMatrix temp(mat.Dimension);

	for (int i = 0; i < temp.Dimension; i++)
	{
		for (int j = 0; j < temp.Dimension; j++)
		{
			temp[i][j] = mat[j][i];
		}
	}

	return temp;
}

float MyMatrix::Cofactor(int row, int col)
{
	return pow(-1, row + col) * Minor(row, col).Determinant();
}

MyMatrix MyMatrix::Minor(int row, int col)
{
	MyMatrix MinorMatrix(Dimension - 1);

	int Mrow = 0; int Mcol = 0;
	for (int i = 0; i < Dimension; i++)
	{
		if (i == row) continue;
		Mcol = 0;
		for (int j = 0; j < Dimension; j++)
		{
			if (j == col) continue;
			MinorMatrix[Mrow][Mcol++] = Rows[i][j];
		}
		Mrow++;
	}
	
	return MinorMatrix;
}

float MyMatrix::Determinant()
{
	if (Dimension == 2)
	{
		return (Rows[0][0] * Rows[1][1] - Rows[0][1] * Rows[1][0]);
	}

	float temp = 0;
	for (int i = 0; i < Dimension; i++)
	{
		temp += Rows[i][0] * Cofactor(i, 0);
	}

	return temp;
}

MyMatrix MyMatrix::Adjoint()
{
	MyMatrix adjoint(Dimension);

	for (int i = 0; i < Dimension; i++)
		for (int j = 0; j < Dimension; j++)
			adjoint[i][j] = Cofactor(j, i);

	return adjoint;
}

