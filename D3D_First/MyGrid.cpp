#include "stdafx.h"
#include "MyGrid.h"


MyGrid::MyGrid()
{
}


MyGrid::~MyGrid()
{
}

void MyGrid::Init(int lineNum, float cellsize)
{
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	float blightness = 0.5f;
	material.Diffuse = D3DXCOLOR(blightness, blightness, blightness, 1.0f);
	material.Ambient = D3DXCOLOR(blightness, blightness, blightness, 1.0f);
	material.Specular = D3DXCOLOR(blightness, blightness, blightness, 1.0f);
	
	//PC_VERTEX pcv;
	//int Num = lineNum;
	//float CellSize = cellsize;
	//float MaxSize = Num * CellSize;
	//int Cnt = 0;
	//// set color code

	//for (float x = -MaxSize; x <= Num * CellSize; x += CellSize)
	//	for (float y = -MaxSize; y <= Num * CellSize; y += CellSize)
	//	{
	//		if (x == 0 || y == 0) continue;
	//		
	//		pcv.p = D3DXVECTOR3(x, 0, y);
	//		vec_pc_vertices.push_back(pcv);
	//		pcv.p = D3DXVECTOR3(x, 0, MaxSize);
	//		vec_pc_vertices.push_back(pcv);

	//		pcv.p = D3DXVECTOR3(x, 0, y);
	//		vec_pc_vertices.push_back(pcv);
	//		pcv.p = D3DXVECTOR3(MaxSize, 0, y);
	//		vec_pc_vertices.push_back(pcv);
	//		Cnt++;
	//	}

	
	float Max = lineNum * cellsize;
	float Min = -Max;
	PNT_VERTEX v;
	v.n = D3DXVECTOR3(0, 1, 0);
	
	for (int i = 0; i < lineNum * 2; ++i)
	{
		for (int j = 0; j < lineNum * 2; ++j)
		{
			v.p = D3DXVECTOR3{ Min + j * cellsize, 0, Max - i * cellsize };
			vec_Vertexs.push_back(v);
			v.p = D3DXVECTOR3{ Min + j * cellsize + cellsize, 0, Max - i * cellsize };
			vec_Vertexs.push_back(v);
			v.p = D3DXVECTOR3{ Min + j * cellsize, 0, Max - i * cellsize - cellsize };
			vec_Vertexs.push_back(v);

			v.p = D3DXVECTOR3{ Min + j * cellsize, 0, Max - i * cellsize - cellsize };
			vec_Vertexs.push_back(v);
			v.p = D3DXVECTOR3{ Min + j * cellsize + cellsize, 0, Max - i * cellsize };
			vec_Vertexs.push_back(v);
			v.p = D3DXVECTOR3{ Min + j * cellsize + cellsize, 0, Max - i * cellsize - cellsize };
			vec_Vertexs.push_back(v);
		}
	}
}

void MyGrid::Update(float delta)
{
}

void MyGrid::Draw(float delta)
{
	//DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	
	D3DXMATRIXA16 WorldMat;
	D3DXMatrixIdentity(&WorldMat);

	DEVICE->SetMaterial(&material);
	DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	DEVICE->SetFVF(PNT_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
							vec_Vertexs.size() / 3,
							&vec_Vertexs[0],
							sizeof(PNT_VERTEX));
	
	//DEVICE->SetRenderState(D3DRS_LIGHTING, true);
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

	Pyramid Gizmo;
	D3DXMATRIXA16 RotMat;

	D3DXMatrixRotationZ(&RotMat, D3DX_PI / 2.0f);
	Gizmo.Init(D3DCOLOR_XRGB(255, 0, 0), RotMat);
	vec_GizmoVector.push_back(Gizmo);

	D3DXMatrixRotationZ(&RotMat, D3DX_PI);
	Gizmo.Init(D3DCOLOR_XRGB(0, 255, 0), RotMat);
	vec_GizmoVector.push_back(Gizmo);

	D3DXMatrixRotationX(&RotMat, -D3DX_PI / 2.0f);
	Gizmo.Init(D3DCOLOR_XRGB(0, 0, 255), RotMat);
	vec_GizmoVector.push_back(Gizmo);
}

void AxisLine::Update(float delta)
{
}

void AxisLine::Draw(float delta)
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	
	DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	DEVICE->SetFVF(PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_LINELIST,
							vec_Vertexs.size() / 2,
							&vec_Vertexs[0],
							sizeof(PC_VERTEX));

	for( Pyramid p : vec_GizmoVector )
	{
		p.Draw(delta);
	}

	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
}

Pyramid::Pyramid()
{
}

Pyramid::~Pyramid()
{
}

void Pyramid::Init(D3DCOLOR color, D3DXMATRIXA16& rotatemat)
{
	RotateMat = rotatemat;

	PC_VERTEX v;
	v.c = color;

	v.p = D3DXVECTOR3(0, 0, 0); vec_Vertexs.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); vec_Vertexs.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); vec_Vertexs.push_back(v);
	
	v.p = D3DXVECTOR3(0, 0, 0); vec_Vertexs.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1); vec_Vertexs.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); vec_Vertexs.push_back(v);
	
	v.p = D3DXVECTOR3(0, 0, 0); vec_Vertexs.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); vec_Vertexs.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1); vec_Vertexs.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0); vec_Vertexs.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); vec_Vertexs.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); vec_Vertexs.push_back(v);

	v.p = D3DXVECTOR3(-1, -1, -1); vec_Vertexs.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); vec_Vertexs.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1); vec_Vertexs.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); vec_Vertexs.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1); vec_Vertexs.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); vec_Vertexs.push_back(v);
	
}

void Pyramid::Update(float delta)
{

}

void Pyramid::Draw(float delta)
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_CULLMODE, false);
	
	D3DXMatrixScaling(&ScaleMat, 0.1f, 2.0f, 0.1f);
	WorldMat = ScaleMat * RotateMat * TransMat;

	
	DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	DEVICE->SetFVF(PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
							vec_Vertexs.size() / 3,
							&vec_Vertexs[0],
							sizeof(PC_VERTEX));
	

	DEVICE->SetRenderState(D3DRS_CULLMODE, true);
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
}
