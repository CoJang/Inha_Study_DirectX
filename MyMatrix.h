#pragma once
#include <vector>

#define EPSILON 0.0001f

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
		cRow() { Dimension = 1; };
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
	static MyMatrix InverseMatrix(MyMatrix& mat);
	static MyMatrix TransposeMatrix(MyMatrix & mat);

protected:
	MyMatrix Minor(int row, int col);
	float Determinant();
	MyMatrix Adjoint();
	float Cofactor(int row, int col);
};

