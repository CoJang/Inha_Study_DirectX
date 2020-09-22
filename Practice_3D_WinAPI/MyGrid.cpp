#include "stdafx.h"
#include "MyGrid.h"


MyGrid::MyGrid()
{
	CellSize = 3.0f;
	MaxSize = 15.0f;
	
	ScaleMat = MyMatrix::Identity(4);
	RotateMat = MyMatrix::Identity(4);
	TransMat = MyMatrix::Identity(4);
	WorldMat = MyMatrix::Identity(4);
}

MyGrid::~MyGrid()
{
}

void MyGrid::InitGrid()
{
	for (float i = -MaxSize; i < MaxSize + CellSize; i += CellSize)
	{
		vec_Vertex.push_back(MyVector3(i, 0, -MaxSize));
		vec_Vertex.push_back(MyVector3(i, 0, MaxSize));
		vec_Vertex.push_back(MyVector3(-MaxSize, 0, i));
		vec_Vertex.push_back(MyVector3(MaxSize, 0, i));
	}
}

void MyGrid::Update()
{
}

void MyGrid::Render(HDC hdc, MyMatrix & viewport_mat)
{
	WorldMat = ScaleMat * RotateMat * TransMat;
	
	for (int i = 0; i < 11; i++)
	{
		MyVector3 v1 = vec_Vertex[4 * i + 0];
		MyVector3 v2 = vec_Vertex[4 * i + 1];
		MyVector3 v3 = vec_Vertex[4 * i + 2];
		MyVector3 v4 = vec_Vertex[4 * i + 3];

		v1 = MyVector3::TransformCoord(v1, WorldMat);
		v2 = MyVector3::TransformCoord(v2, WorldMat);
		v3 = MyVector3::TransformCoord(v3, WorldMat);
		v4 = MyVector3::TransformCoord(v4, WorldMat);

		v1 = MyVector3::TransformCoord(v1, viewport_mat);
		v2 = MyVector3::TransformCoord(v2, viewport_mat);
		v3 = MyVector3::TransformCoord(v3, viewport_mat);
		v4 = MyVector3::TransformCoord(v4, viewport_mat);

		DrawLine(hdc, v1, v2);
		DrawLine(hdc, v3, v4);
	}
}

void MyGrid::DrawLine(HDC hdc, MyVector3& v1, MyVector3& v2)
{
	MoveToEx(hdc, v1.x, v1.y, NULL);
	LineTo(hdc, v2.x, v2.y);
}
