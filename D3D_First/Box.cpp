#include "stdafx.h"
#include "Box.h"


Box::Box()
	: Position(0, 0, 0)
	, MovePivot(0, 0, 0)
	, RotateAngle(0, 0, 0)
	, MaxAngle(0.0f)
	, AnimDirection(0)
{
}


Box::~Box()
{
}

void Box::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXCOLOR color)
{
	Position = pos;
	Scale = scale;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = D3DXCOLOR(color.r * 0.5f, color.g * 0.5f, color.b * 0.5f, 1.0f);
	material.Diffuse = D3DXCOLOR(color.r, color.g, color.b, 1.0f);
	material.Specular = D3DXCOLOR(color.r, color.g, color.b, 1.0f);
	
	D3DXMatrixScaling(&ScaleMat, Scale.x, Scale.y, Scale.z);

	PNT_VERTEX vertex;
	std::vector<PNT_VERTEX> vec;
	vertex.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	vec.push_back(vertex);

	vertex.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	vec.push_back(vertex);

	vertex.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	vec.push_back(vertex);

	vertex.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	vec.push_back(vertex);

	vertex.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vec.push_back(vertex);

	vertex.p = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vec.push_back(vertex);

	vertex.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vec.push_back(vertex);

	vertex.p = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	vec.push_back(vertex);


	// : front
	vec_Vertexs.push_back(vec[0]);
	vec_Vertexs.push_back(vec[1]);
	vec_Vertexs.push_back(vec[2]);

	vec_Vertexs.push_back(vec[0]);
	vec_Vertexs.push_back(vec[2]);
	vec_Vertexs.push_back(vec[3]);

	// : back
	vec_Vertexs.push_back(vec[4]);
	vec_Vertexs.push_back(vec[6]);
	vec_Vertexs.push_back(vec[5]);

	vec_Vertexs.push_back(vec[4]);
	vec_Vertexs.push_back(vec[7]);
	vec_Vertexs.push_back(vec[6]);
	// : left
	vec_Vertexs.push_back(vec[4]);
	vec_Vertexs.push_back(vec[5]);
	vec_Vertexs.push_back(vec[1]);

	vec_Vertexs.push_back(vec[4]);
	vec_Vertexs.push_back(vec[1]);
	vec_Vertexs.push_back(vec[0]);

	// : right
	vec_Vertexs.push_back(vec[3]);
	vec_Vertexs.push_back(vec[2]);
	vec_Vertexs.push_back(vec[6]);

	vec_Vertexs.push_back(vec[3]);
	vec_Vertexs.push_back(vec[6]);
	vec_Vertexs.push_back(vec[7]);

	// : up
	vec_Vertexs.push_back(vec[1]);
	vec_Vertexs.push_back(vec[5]);
	vec_Vertexs.push_back(vec[6]);

	vec_Vertexs.push_back(vec[1]);
	vec_Vertexs.push_back(vec[6]);
	vec_Vertexs.push_back(vec[2]);

	// : down					 
	vec_Vertexs.push_back(vec[4]);
	vec_Vertexs.push_back(vec[0]);
	vec_Vertexs.push_back(vec[3]);

	vec_Vertexs.push_back(vec[4]);
	vec_Vertexs.push_back(vec[3]);
	vec_Vertexs.push_back(vec[7]);


	D3DXVECTOR3 u, v, n;
	for (int i = 0; i < 36; i += 3)
	{
		u = vec_Vertexs[i + 1].p - vec_Vertexs[i].p;
		v = vec_Vertexs[i + 2].p - vec_Vertexs[i].p;

		D3DXVec3Cross(&n, &u, &v);
		D3DXVec3Normalize(&n, &n);
		
		vec_Vertexs[i + 0].n = n;
		vec_Vertexs[i + 1].n = n;
		vec_Vertexs[i + 2].n = n;
	}
}

void Box::Update(float delta)
{
	D3DXMatrixTranslation(&TransMat, Position.x, Position.y, Position.z);

	WorldMat = ScaleMat * RotateMat * TransMat;
}

void Box::Update(float delta, D3DXMATRIXA16 & worldmat)
{
	D3DXMATRIXA16 AxisMat;
	D3DXMatrixIdentity(&AxisMat);
	
	D3DXMatrixTranslation(&AxisMat, MovePivot.x, MovePivot.y, MovePivot.z);
	//WorldMat = ScaleMat * AxisMat;
	WorldMat = AxisMat * ScaleMat;

	D3DXMatrixTranslation(&TransMat, Position.x - MovePivot.x, Position.y - MovePivot.y, Position.z - MovePivot.z);

	D3DXMATRIXA16 XRotMat, YRotMat, ZRotMat;
	D3DXMatrixIdentity(&XRotMat);
	D3DXMatrixIdentity(&YRotMat);
	D3DXMatrixIdentity(&ZRotMat);

	D3DXMatrixRotationX(&XRotMat, RotateAngle.x);
	D3DXMatrixRotationY(&YRotMat, RotateAngle.y);
	D3DXMatrixRotationZ(&ZRotMat, RotateAngle.z);
	RotateMat = XRotMat * YRotMat * ZRotMat;
	
	WorldMat *= RotateMat * TransMat * worldmat;
	//  ÆÈÅ¥ºêsrt * ÆÈ¿ùµåsrt * ¿ùµåsrt
	//  ÆÈÅ¥ºêst * ÆÈ¿ùµå rt * ¿ùµå srt
}

void Box::Draw(float delta)
{
	//DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	
	//DEVICE->SetRenderState(D3DRS_CULLMODE, false);

	DEVICE->SetMaterial(&material);
	DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	DEVICE->SetFVF(PNT_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
							vec_Vertexs.size() / 3,
							&vec_Vertexs[0],
							sizeof(PNT_VERTEX));


	//PC_VERTEX v;
	//std::vector<PC_VERTEX> normalVector;
	//v.c = D3DCOLOR_XRGB(255, 255, 255);

	//v.p = D3DXVECTOR3(0, 0, 0);
	//normalVector.push_back(v);
	//
	//v.p = vec_Vertexs[0].n * 5;
	//normalVector.push_back(v);

	//DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	//
	//DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	//DEVICE->SetFVF(PC_VERTEX::FVF);
	//DEVICE->DrawPrimitiveUP(D3DPT_LINELIST,
	//						normalVector.size() / 2,
	//						&normalVector[0],
	//						sizeof(PC_VERTEX));

	//DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	//DEVICE->SetRenderState(D3DRS_CULLMODE, true);
}
