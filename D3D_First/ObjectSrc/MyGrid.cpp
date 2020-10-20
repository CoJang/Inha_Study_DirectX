#include "stdafx.h"
#include "MyGrid.h"

void MyGrid::Init(int lineNum, float cellsize)
{
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	float blightness = 1.0f;
	material.Diffuse = D3DXCOLOR(blightness, blightness, blightness, 1.0f);
	material.Ambient = D3DXCOLOR(blightness, blightness, blightness, 1.0f);
	material.Specular = D3DXCOLOR(blightness, blightness, blightness, 1.0f);
	
	float Max = lineNum * cellsize;
	float Min = -Max;
	PC_VERTEX v;
	//v.n = D3DXVECTOR3(0, 1, 0);
	v.c = D3DCOLOR_XRGB(255, 255, 255);
	
	for (int i = 0; i < lineNum * 2; ++i)
	{
		for (int j = 0; j < lineNum * 2; ++j)
		{
			v.p = D3DXVECTOR3{ Min + j * cellsize, 0, Max - i * cellsize };
			vec_pc_vertices.push_back(v);
			v.p = D3DXVECTOR3{ Min + j * cellsize + cellsize, 0, Max - i * cellsize };
			vec_pc_vertices.push_back(v);
			v.p = D3DXVECTOR3{ Min + j * cellsize, 0, Max - i * cellsize - cellsize };
			vec_pc_vertices.push_back(v);

			v.p = D3DXVECTOR3{ Min + j * cellsize, 0, Max - i * cellsize - cellsize };
			vec_pc_vertices.push_back(v);
			v.p = D3DXVECTOR3{ Min + j * cellsize + cellsize, 0, Max - i * cellsize };
			vec_pc_vertices.push_back(v);
			v.p = D3DXVECTOR3{ Min + j * cellsize + cellsize, 0, Max - i * cellsize - cellsize };
			vec_pc_vertices.push_back(v);
		}
	}
}


void MyGrid::Draw(float delta)
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	
	D3DXMATRIXA16 WorldMat;
	D3DXMatrixIdentity(&WorldMat);

	//DEVICE->SetMaterial(&material);
	DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	DEVICE->SetFVF(PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
							vec_pc_vertices.size() / 3,
							&vec_pc_vertices[0],
							sizeof(PC_VERTEX));
	
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
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

void BezierCurve::Init()
{
	vector<PC_VERTEX> vertex;
	
	PC_VERTEX v;
	v.c = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

	D3DXMATRIXA16 rotationMat;
	D3DXMatrixIdentity(&rotationMat);
	D3DXMatrixRotationY(&rotationMat, Deg2Rad(60));
	
	v.p = D3DXVECTOR3(0, 0.1f, 10);
	vertex.push_back(v);

	for(int i = 0; i < 5; i++)
	{
		D3DXVec3TransformCoord(&v.p, &v.p, &rotationMat);
		vertex.push_back(v);
	}

	// for문을 사용하기 쉽게하기 위함
	v.p = D3DXVECTOR3(0, 0.1f, 10);
	vertex.push_back(v);

	vec_Straight = vertex;

	float n = 8;
	float alpha = 0;
	float beta = 0;
	v.c = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	// 2차 베지어 곡선
	// P(t) = (1-t)^2 * A + 2t(1-t) * B + t^2 * C 단 0 <= t <= 1

	for(int i = 0; i < 3; i++)
	{
		for(float t = 0.0f; t <= 1; t += 1.0f / n)
		{
			alpha = 1 - t;
			beta = alpha * alpha;

			v.p = beta * vertex[i * 2].p
				  + (2 * t) * (alpha) * vertex[i * 2 + 1].p
				  + (t * t) * vertex[i * 2 + 2].p;

			vec_Vertexs.push_back(v);
		}
	}

	cout << vec_Vertexs.size() << endl;
}


void BezierCurve::Draw(float delta)
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_CULLMODE, false);

	//D3DXMatrixScaling(&ScaleMat, 0.1f, 2.0f, 0.1f);
	WorldMat = ScaleMat * RotateMat * TransMat;


	DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	DEVICE->SetFVF(PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP,
							vec_Straight.size() - 1,
							&vec_Straight[0],
							sizeof(PC_VERTEX));

	DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP,
							vec_Vertexs.size() - 1,
							&vec_Vertexs[0],
							sizeof(PC_VERTEX));


	DEVICE->SetRenderState(D3DRS_CULLMODE, true);
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
}