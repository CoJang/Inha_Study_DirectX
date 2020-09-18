#pragma once
#include "MyMatrix.h"

class MyCube
{
private:
	MyVector3 vertex[8];
	MyVector3 position;

	MyMatrix ScaleMat;
	MyMatrix RotateMat;
	MyMatrix TransMat;
	MyMatrix WorldMat;

	float cSize;
public:
	MyCube();
	~MyCube();

	void InitCube(float pos_x, float pos_y, float pos_z, float cube_size);
	void Update(MyMatrix & viewport_mat);
	void Render(HDC hdc);
	inline MyVector3 GetPos() { return position; };

	void DrawLine(HDC hdc, MyVector3 & v1, MyVector3 & v2);
};

