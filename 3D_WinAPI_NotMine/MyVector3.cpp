#include "stdafx.h"
#include "MyVector3.h"
#include <cmath>

MyVector3::MyVector3()
	: x(0.0f), y(0.0f), z(0.0f)
{
}

MyVector3::MyVector3(float _x, float _y, float _z)
	:x(_x), y(_y), z(_z)
{
}

MyVector3::~MyVector3()
{
}

bool MyVector3::operator==(MyVector3 & vec)
{
	return ((x - vec.x) < EPSILON && (y - vec.y) < EPSILON && (z - vec.z) < EPSILON) ? true : false; 
}

bool MyVector3::operator!=(MyVector3 & vec)
{
	//return ((x - vec.x) < EPSILON && (y - vec.y) < EPSILON && (z - vec.z) < EPSILON) ? false : true;
	return !(*this == vec);
}

MyVector3 MyVector3::operator+(MyVector3 & vec)
{
	return MyVector3({ x + vec.x, y + vec.y, z + vec.z });
}

MyVector3 MyVector3::operator-(MyVector3 & vec)
{
	return MyVector3({ x - vec.x, y - vec.y, z - vec.z });
}

MyVector3 MyVector3::operator*(float k)
{
	return MyVector3({ x * k, y * k, z * k });
}

MyVector3 MyVector3::operator/(float k)
{
	return MyVector3({ x / k, y / k, z / k });
}

float MyVector3::Dot(MyVector3 & v1, MyVector3 & v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

MyVector3 MyVector3::Cross(MyVector3 & v1, MyVector3 & v2)
{
	return MyVector3((v1.y * v2.z - v1.z * v2.y), (v1.z * v2.x - v1.x * v2.z), (v1.x * v2.y - v1.y * v2.x));
}

float MyVector3::Angle(MyVector3 & v1, MyVector3 & v2)
{
	return Rad2Deg(acos(Dot(v1, v2) / (v1.Length() * v2.Length()))); 
}

float MyVector3::Length()
{
	return sqrt(x*x + y*y + z*z);
}

MyVector3 MyVector3::Normalize()
{
	*this = *this / Length();
	return *this;
}

MyVector3 MyVector3::TransformCoord(MyVector3& vec, MyMatrix& mat)
{
	float w = 0;
	MyVector3 moved(0, 0,0 );
	moved.x = vec.x * mat[0][0] + vec.y * mat[1][0] + vec.z * mat[2][0] + 1.0 * mat[3][0];
	moved.y = vec.x * mat[0][1] + vec.y * mat[1][1] + vec.z * mat[2][1] + 1.0 * mat[3][1];
	moved.z = vec.x * mat[0][2] + vec.y * mat[1][2] + vec.z * mat[2][2] + 1.0 * mat[3][2];
	w =       vec.x * mat[0][3] + vec.y * mat[1][3] + vec.z * mat[2][3] + 1.0 * mat[3][3];

	if(abs(w) > EPSILON)
	{
		moved.x = moved.x / w;
		moved.y = moved.y / w;
		moved.z = moved.z / w;
	}
	return moved;
}

MyVector3 MyVector3::TransformNormal(MyVector3& vec, MyMatrix& mat)
{
	MyVector3 moved(0, 0, 0);
	moved.x = vec.x * mat[0][0] + vec.y * mat[1][0] + vec.z * mat[2][0];
	moved.y = vec.x * mat[0][1] + vec.y * mat[1][1] + vec.z * mat[2][1];
	moved.z = vec.x * mat[0][2] + vec.y * mat[1][2] + vec.z * mat[2][2];

	return moved;
}
