#pragma once
#include <vector>
#include "MyVector3.h"

class MyMatrix
{
private:
	int Dimension;
	class cRow
	{
	private:
		int Dimension;
		std::vector<float> Datas;
	public:
		cRow() { Dimension = 4; };
		cRow(int dimension);
		~cRow();

		void Resize(int dimension);
		float & operator[](int index);
	};

	cRow* Rows;
public:
	MyMatrix();
	MyMatrix(int dimension);
	MyMatrix(const MyMatrix & mat);
	~MyMatrix();

	inline int GetDimension() { return Dimension; };

	bool operator==(MyMatrix & mat);
	bool operator!=(MyMatrix & mat);
	MyMatrix operator+(MyMatrix & mat);
	MyMatrix operator+=(MyMatrix& mat) { return *this + mat; };
	MyMatrix operator-(MyMatrix & mat);
	MyMatrix operator-=(MyMatrix& mat) { return *this - mat; };
	MyMatrix operator*(MyMatrix & mat);
	MyMatrix operator*=(MyMatrix& mat) { return *this * mat; };
	MyMatrix operator*(float k);
	MyMatrix operator*=(float k) { return *this * k; };
	MyMatrix operator/(float k);
	MyMatrix operator/=(float k) { return *this / k; }
	inline cRow & operator[](int index) 
	{ 
		if(index < Dimension)
			return Rows[index];
	};

	static void PrintMatrix(MyMatrix & mat);
	static MyMatrix InverseMatrix(MyMatrix & mat);
	static MyMatrix TransposeMatrix(MyMatrix & mat);

	// >> :
	static MyMatrix Identity(int dimension);
	static MyMatrix Translation(float x, float y, float z);
	static MyMatrix Translation(MyVector3 & vec);
	static MyMatrix ScaleMatrix(float x, float y, float z);
	static MyMatrix RotationX(float angle);
	static MyMatrix RotationY(float angle);
	static MyMatrix RotationZ(float angle);
	static MyMatrix View(MyVector3 & eye, MyVector3 & lookat, MyVector3 & up);
	static MyMatrix Projection(float fovY, float aspect, float nearz, float farz);
	static MyMatrix Viewport(float x, float y, float w, float h, float minz, float maxz);

protected:
	MyMatrix Minor(int row, int col);
	float Determinant();
	MyMatrix Adjoint();
	float Cofactor(int row, int col);
};

