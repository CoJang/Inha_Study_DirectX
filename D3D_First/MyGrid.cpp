#include "stdafx.h"
#include "MyGrid.h"


MyGrid::MyGrid()
{
}


MyGrid::~MyGrid()
{
}

void MyGrid::Init()
{
	PC_VERTEX v;
	int Num = 15;
	float CellSize = 1.0f;
	float MaxSize = Num * CellSize;
	int Cnt = 0;
	v.c = D3DCOLOR_XRGB(255, 255, 255);

	for (float x = -MaxSize; x <= Num * CellSize; x += CellSize)
		for (float y = -MaxSize; y <= Num * CellSize; y += CellSize)
		{
			if (x == 0 || y == 0) continue;
			//if( Cnt % 5 == 0) v.c = D3DCOLOR_XRGB(255, 255, 255);
			//else v.c = D3DCOLOR_XRGB(100, 100, 100);
			
			v.p = D3DXVECTOR3(x, 0, y);
			vec_Vertexs.push_back(v);
			v.p = D3DXVECTOR3(x, 0, MaxSize);
			vec_Vertexs.push_back(v);

			v.p = D3DXVECTOR3(x, 0, y);
			vec_Vertexs.push_back(v);
			v.p = D3DXVECTOR3(MaxSize, 0, y);
			vec_Vertexs.push_back(v);
			Cnt++;
		}
}

void MyGrid::Update(float delta)
{
}

void MyGrid::Draw(float delta)
{
	D3DXMATRIXA16 WorldMat;
	D3DXMatrixIdentity(&WorldMat);

	DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	DEVICE->SetFVF(PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_LINELIST,
							vec_Vertexs.size() / 2,
							&vec_Vertexs[0],
							sizeof(PC_VERTEX));
}

AxisLine::AxisLine()
{
}

AxisLine::~AxisLine()
{
}

void AxisLine::Init()
{
	PC_VERTEX v;
	float axisLineSize = 15;
	v.p = D3DXVECTOR3(axisLineSize, 0, 0);
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	vec_Vertexs.push_back(v);

	v.p = D3DXVECTOR3(-axisLineSize, 0, 0);
	vec_Vertexs.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, axisLineSize, 0);
	vec_Vertexs.push_back(v);

	v.p = D3DXVECTOR3(0, -axisLineSize, 0);
	vec_Vertexs.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0, 0, axisLineSize);
	vec_Vertexs.push_back(v);

	v.p = D3DXVECTOR3(0, 0, -axisLineSize);
	vec_Vertexs.push_back(v);
}

void AxisLine::Update(float delta)
{
}

void AxisLine::Draw(float delta)
{
	DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	DEVICE->SetFVF(PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_LINELIST,
							vec_Vertexs.size() / 2,
							&vec_Vertexs[0],
							sizeof(PC_VERTEX));
}
