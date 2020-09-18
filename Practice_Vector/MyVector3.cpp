#include "stdafx.h"
#include "MyVector3.h"
#include <math.h>


MyVector3::MyVector3(float _x, float _y, float _z)
{
	x = _x; y = _y; z = _z;
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
	return ((x - vec.x) < EPSILON && (y - vec.y) < EPSILON && (z - vec.z) < EPSILON) ? false : true;
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
