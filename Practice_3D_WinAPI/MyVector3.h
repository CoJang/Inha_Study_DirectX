#pragma once

#define EPSILON 0.00001f
#define PI 3.1415926535
#define Deg2Rad(x) (x * PI / 180)
#define Rad2Deg(x) (x / PI * 180)

class MyMatrix;

class MyVector3
{
public:
	float x, y, z;
	MyVector3();
	MyVector3(float _x, float _y, float _z);
	~MyVector3();

	bool operator==(MyVector3 & vec);
	bool operator!=(MyVector3 & vec);
	MyVector3 operator+(MyVector3 & vec);
	MyVector3 operator+=(MyVector3 & vec) { *this = *this + vec; return *this; }
	MyVector3 operator-(MyVector3 & vec);
	MyVector3 operator*(float k);
	MyVector3 operator/(float k);

	static float Dot(MyVector3 & v1, MyVector3 & v2);
	static MyVector3 Cross(MyVector3 & v1, MyVector3 & v2);
	static float Angle(MyVector3 & v1, MyVector3 & v2);
	float Length();
	MyVector3 Normalize();

	// >> :
	static MyVector3 TransformCoord(MyVector3 & vec, MyMatrix & mat);  // 점 이동
	static MyVector3 TransformNormal(MyVector3 & vec, MyMatrix & mat); // 벡터 이동
};

