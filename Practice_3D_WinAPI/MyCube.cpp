#include "stdafx.h"
#include "MyCube.h"

MyCube::MyCube()
	:position(0, 0, 0), velocity(0.1f), dir(0, 0, -1),
	angle(0.0f)
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

	OriginVertex[0] = { - cube_size, + cube_size, - cube_size };
	OriginVertex[1] = { + cube_size, + cube_size, - cube_size };
	OriginVertex[2] = { + cube_size, - cube_size, - cube_size };
	OriginVertex[3] = { - cube_size, - cube_size, - cube_size };
	OriginVertex[4] = { - cube_size, + cube_size, + cube_size };
	OriginVertex[5] = { + cube_size, + cube_size, + cube_size };
	OriginVertex[6] = { + cube_size, - cube_size, + cube_size };
	OriginVertex[7] = { - cube_size, - cube_size, + cube_size };
	
	//WorldMat = S * R * T
	//RotateMat = MyMatrix::RotationY(45);
	//MyMatrix::PrintMatrix(RotateMat);
	WorldMat = ScaleMat * RotateMat * TransMat;
}

void MyCube::Update(MyMatrix & viewport_mat)
{
	// 'W' = 0x57 'A' = 0x41 'S' = 0x53 'D' = 0x44
	if(GetKeyState(0x57) & 0x8000)
	{
		cout << "W key down!" << endl;
		position.x += velocity;
	}
	if (GetKeyState(0x41) & 0x8000)
	{
		cout << "A key down!" << endl;
		RotateMat = MyMatrix::RotationY(angle += 5.0f);
	}
	if (GetKeyState(0x53) & 0x8000)
	{
		cout << "S key down!" << endl;
		position.x -= velocity;
	}
	if (GetKeyState(0x44) & 0x8000)
	{
		cout << "D key down!" << endl;
		RotateMat = MyMatrix::RotationY(angle -= 5.0f);
	}

	TransMat = MyMatrix::Translation(position.x, position.y, position.z);
	
	WorldMat = ScaleMat * RotateMat * TransMat * viewport_mat;
	
	for(int i = 0; i < 8; i++)
	{
		vertex[i] = MyVector3::TransformCoord(OriginVertex[i], WorldMat);
	}
}

void MyCube::Render(HDC hdc)
{
	for(int i = 0; i < 8; i++)
		Rectangle(hdc, vertex[i].x - 2, vertex[i].y - 2, vertex[i].x + 2, vertex[i].y + 2);

	DrawCube(hdc);
}

void MyCube::DrawLine(HDC hdc, MyVector3& v1, MyVector3& v2)
{
	MoveToEx(hdc, v1.x, v1.y, NULL);
	LineTo(hdc, v2.x, v2.y);
}

void MyCube::DrawCube(HDC hdc)
{
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
