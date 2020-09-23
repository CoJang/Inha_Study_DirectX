#include "stdafx.h"
#include "MyCube.h"

MyCube::MyCube()
	:position(0, 0, 0), velocity(0.0f), dir(0, 0, -1),
	angle(0.0f)
{

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

	ScaleMat = MyMatrix::ScaleMatrix(1, 1, 1);
	RotateMat = MyMatrix::Identity(4);
	TransMat = MyMatrix::Translation(0, 0, 0);
	WorldMat = MyMatrix::Identity(4);
}

void MyCube::Update(MyMatrix & viewport_mat)
{
	velocity = 0;
	
	// 'W' = 0x57 'A' = 0x41 'S' = 0x53 'D' = 0x44
	if(GetKeyState('W') & 0x8000)
	{
		velocity = 0.5f;
	}
	if (GetKeyState('A') & 0x8000)
	{
		dir = MyVector3::TransformNormal(dir, MyMatrix::RotationY(5)).Normalize();
		angle -= 5.0f;
	}
	if (GetKeyState('S') & 0x8000)
	{
		velocity = -0.5f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		dir = MyVector3::TransformNormal(dir, MyMatrix::RotationY(-5)).Normalize();
		angle += 5.0f;
	}
	else
	{
		
	}

	position += dir * velocity;
	TransMat = MyMatrix::Translation(position.x, position.y, position.z);
	RotateMat = MyMatrix::RotationY(angle);
	
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
