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
	Dimension = 4;
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
	if (-EPSILON < mat.Determinant() && mat.Determinant() < EPSILON)
	{
		return MyMatrix();
	}

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

MyMatrix MyMatrix::Identity(int dimension)
{
	MyMatrix idMat(dimension);
	for (int i = 0; i < dimension; i++)
		idMat[i][i] = 1;

	return idMat;
}

MyMatrix MyMatrix::Translation(float x, float y, float z)
{
	MyMatrix TransMat = Identity(4);
	TransMat[3][0] = x; TransMat[3][1] = y; TransMat[3][2] = z;
	return TransMat;
}

MyMatrix MyMatrix::Translation(MyVector3& vec)
{
	MyMatrix TransMat = Identity(4);
	TransMat[3][0] = vec.x; TransMat[3][1] = vec.y; TransMat[3][2] = vec.z;
	return TransMat;
}

MyMatrix MyMatrix::ScaleMatrix(float x, float y, float z)
{
	MyMatrix ScaleMat = Identity(4);
	ScaleMat[0][0] = x; ScaleMat[1][1] = y; ScaleMat[2][2] = z; ScaleMat[3][3] = 1;
	return ScaleMat;
}

MyMatrix MyMatrix::RotationX(float angle)
{
	MyMatrix RotMat = Identity(4);
	RotMat[1][1] = cos(Deg2Rad(angle));  RotMat[1][2] = sin(Deg2Rad(angle));
	RotMat[2][1] = -sin(Deg2Rad(angle)); RotMat[2][2] = cos(Deg2Rad(angle));
	return RotMat;
}

MyMatrix MyMatrix::RotationY(float angle)
{
	MyMatrix RotMat = Identity(4);
	RotMat[0][0] = cos(Deg2Rad(angle));  RotMat[0][2] = -sin(Deg2Rad(angle));
	RotMat[2][0] = sin(Deg2Rad(angle)); RotMat[2][2] = cos(Deg2Rad(angle));
	return RotMat;
}

MyMatrix MyMatrix::RotationZ(float angle)
{
	MyMatrix RotMat = Identity(4);
	RotMat[0][0] = cos(Deg2Rad(angle));  RotMat[0][1] = sin(Deg2Rad(angle));
	RotMat[1][1] = -sin(Deg2Rad(angle)); RotMat[1][1] = cos(Deg2Rad(angle));
	return RotMat;
}

// lookat = target - eye
MyMatrix MyMatrix::View(MyVector3& eye, MyVector3& lookat, MyVector3& up)
{
	MyVector3 right = MyVector3::Cross(up, lookat);
	MyVector3 newUp = MyVector3::Cross(lookat, right).Normalize();
	
	MyMatrix viewMat(4);
	viewMat[0][0] = right.x; viewMat[0][1] = newUp.x; viewMat[0][2] = lookat.x;
	viewMat[1][0] = right.y; viewMat[1][1] = newUp.y; viewMat[1][2] = lookat.y;
	viewMat[2][0] = right.z; viewMat[2][1] = newUp.z; viewMat[2][2] = lookat.z;
	viewMat[3][0] = MyVector3::Dot(right * -1, eye);
	viewMat[3][1] = MyVector3::Dot(newUp * -1, eye);
	viewMat[3][2] = MyVector3::Dot(lookat * -1, eye);

	return viewMat;
}

MyMatrix MyMatrix::Projection(float fovY, float aspect, float nearz, float farz)
{
	float sy = 1.0f / tanf(Deg2Rad(fovY / 2.0f));
	float sx = sy / aspect;

	MyMatrix projMat(4);
	projMat[0][0] = sx; projMat[0][1] = 0;  projMat[0][2] = 0;
	projMat[1][0] = 0;  projMat[1][1] = sy; projMat[1][2] = 0;
	projMat[2][0] = 0;  projMat[2][1] = 0;  projMat[2][2] = farz / (farz - nearz); projMat[2][3] = 1;
	projMat[3][0] = 0;  projMat[3][1] = 0;  projMat[3][2] = -farz*nearz / (farz - nearz);

	return projMat;
}

MyMatrix MyMatrix::Viewport(float x, float y, float w, float h, float minz, float maxz)
{
	MyMatrix viewMat(4);
	viewMat[0][0] = w / 2.0f;		viewMat[0][1] = 0;			viewMat[0][2] = 0;
	viewMat[1][0] = 0;				viewMat[1][1] = -h/2.0f;	viewMat[1][2] = 0;
	viewMat[2][0] = 0;				viewMat[2][1] = 0;			viewMat[2][2] = maxz-minz;
	viewMat[3][0] = x + (w/2.0f);	viewMat[3][1] = y+(h/2.0f); viewMat[3][2] = minz; viewMat[3][3] = 1;
	
	return viewMat;
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
	if(Dimension == 1)
	{
		return (*this)[0][0];
	}
	
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

