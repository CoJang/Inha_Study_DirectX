#include "stdafx.h"
#include "MyCube.h"

MyCube::MyCube()
	:position(0, 0, 0)
{
	ScaleMat = MyMatrix::ScaleMatrix(1, 1, 1);
	RotateMat = MyMatrix::Identity(4);
	TransMat = MyMatrix::Translation(0, 0, 0);
}


MyCube::~MyCube()
{
}

void MyCube::InitCube(float pos_x, float pos_y, float pos_z, float cube_size)
{
	cSize = cube_size; position = MyVector3(pos_x, pos_y, pos_z);
	vertex[0] = { pos_x - cube_size, pos_y + cube_size, pos_z - cube_size };
	vertex[1] = { pos_x + cube_size, pos_y + cube_size, pos_z - cube_size };
	vertex[2] = { pos_x + cube_size, pos_y - cube_size, pos_z - cube_size };
	vertex[3] = { pos_x - cube_size, pos_y - cube_size, pos_z - cube_size };
	vertex[4] = { pos_x - cube_size, pos_y + cube_size, pos_z + cube_size };
	vertex[5] = { pos_x + cube_size, pos_y + cube_size, pos_z + cube_size };
	vertex[6] = { pos_x + cube_size, pos_y - cube_size, pos_z + cube_size };
	vertex[7] = { pos_x - cube_size, pos_y - cube_size, pos_z + cube_size };
	
	//WorldMat = S * R * T
	WorldMat = ScaleMat * RotateMat * TransMat;
}

void MyCube::Update(MyMatrix & viewport_mat)
{
	for(int i = 0; i < 8; i++)
	{
		vertex[i] = MyVector3::TransformCoord(vertex[i], WorldMat);
		vertex[i] = MyVector3::TransformCoord(vertex[i], viewport_mat);
	}
}

void MyCube::Render(HDC hdc)
{
	for(int i = 0; i < 8; i++)
		Rectangle(hdc, vertex[i].x - 2, vertex[i].y - 2, vertex[i].x + 2, vertex[i].y + 2);


	DrawLine(hdc, vertex[0], vertex[1]);
	DrawLine(hdc, vertex[1], vertex[2]);
	DrawLine(hdc, vertex[2], vertex[3]);
	DrawLine(hdc, vertex[0], vertex[3]);

	DrawLine(hdc, vertex[1], vertex[5]);
	DrawLine(hdc, vertex[5], vertex[4]);
	DrawLine(hdc, vertex[0], vertex[4]);

	DrawLine(hdc, vertex[5], vertex[6]);
	DrawLine(hdc, vertex[2], vertex[6]);

	DrawLine(hdc, vertex[3], vertex[7]);
	DrawLine(hdc, vertex[4], vertex[7]);

	DrawLine(hdc, vertex[7], vertex[6]);
}

void MyCube::DrawLine(HDC hdc, MyVector3& v1, MyVector3& v2)
{
	MoveToEx(hdc, v1.x, v1.y, NULL);
	LineTo(hdc, v2.x, v2.y);
}
