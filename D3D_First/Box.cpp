#include "stdafx.h"
#include "Box.h"


Box::Box()
	: position(0, 0, 0)
	, MovePivot(0, 0, 0)
	, Angle(0.0f)
	, MaxAngle(0.0f)
	, AnimDirection(0)
{
}


Box::~Box()
{
}

void Box::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DCOLOR color)
{
	position = pos;
	D3DXMatrixScaling(&ScaleMat, scale.x, scale.y, scale.z);
	PC_VERTEX v;
	v.c = color;

	v.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	vec_Vertexs.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	vec_Vertexs.push_back(v);

	v.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	vec_Vertexs.push_back(v);

	v.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	vec_Vertexs.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vec_Vertexs.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vec_Vertexs.push_back(v);

	v.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vec_Vertexs.push_back(v);

	v.p = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	vec_Vertexs.push_back(v);


	// : front
	vec_Vertexs.push_back(vec_Vertexs[0]);
	vec_Vertexs.push_back(vec_Vertexs[1]);
	vec_Vertexs.push_back(vec_Vertexs[2]);

	vec_Vertexs.push_back(vec_Vertexs[0]);
	vec_Vertexs.push_back(vec_Vertexs[2]);
	vec_Vertexs.push_back(vec_Vertexs[3]);

	// : back
	vec_Vertexs.push_back(vec_Vertexs[4]);
	vec_Vertexs.push_back(vec_Vertexs[6]);
	vec_Vertexs.push_back(vec_Vertexs[5]);

	vec_Vertexs.push_back(vec_Vertexs[4]);
	vec_Vertexs.push_back(vec_Vertexs[7]);
	vec_Vertexs.push_back(vec_Vertexs[6]);
	// : left
	vec_Vertexs.push_back(vec_Vertexs[4]);
	vec_Vertexs.push_back(vec_Vertexs[5]);
	vec_Vertexs.push_back(vec_Vertexs[1]);

	vec_Vertexs.push_back(vec_Vertexs[4]);
	vec_Vertexs.push_back(vec_Vertexs[1]);
	vec_Vertexs.push_back(vec_Vertexs[0]);

	// : right
	vec_Vertexs.push_back(vec_Vertexs[3]);
	vec_Vertexs.push_back(vec_Vertexs[2]);
	vec_Vertexs.push_back(vec_Vertexs[6]);

	vec_Vertexs.push_back(vec_Vertexs[3]);
	vec_Vertexs.push_back(vec_Vertexs[6]);
	vec_Vertexs.push_back(vec_Vertexs[7]);

	// : up
	vec_Vertexs.push_back(vec_Vertexs[1]);
	vec_Vertexs.push_back(vec_Vertexs[5]);
	vec_Vertexs.push_back(vec_Vertexs[6]);

	vec_Vertexs.push_back(vec_Vertexs[1]);
	vec_Vertexs.push_back(vec_Vertexs[6]);
	vec_Vertexs.push_back(vec_Vertexs[2]);

	// : down							 
	vec_Vertexs.push_back(vec_Vertexs[4]);
	vec_Vertexs.push_back(vec_Vertexs[0]);
	vec_Vertexs.push_back(vec_Vertexs[3]);

	vec_Vertexs.push_back(vec_Vertexs[4]);
	vec_Vertexs.push_back(vec_Vertexs[3]);
	vec_Vertexs.push_back(vec_Vertexs[7]);
}

void Box::Update(float delta)
{
	D3DXMatrixTranslation(&TransMat, position.x, position.y, position.z);

	WorldMat = ScaleMat * RotateMat * TransMat;
}

void Box::Update(float delta, D3DXMATRIXA16 & worldmat)
{
	D3DXMATRIXA16 AxisMat;
	D3DXMatrixIdentity(&AxisMat);
	
	D3DXMatrixTranslation(&AxisMat, MovePivot.x, MovePivot.y, MovePivot.z);
	WorldMat = ScaleMat * AxisMat;

	switch(RotateFlag)
	{
	case 'X':
	case 'x':
		D3DXMatrixRotationX(&RotateMat, Angle);
		break;
	case 'Y':
	case 'y':
		D3DXMatrixRotationY(&RotateMat, Angle);
		break;
	case 'Z':
	case 'z':
		D3DXMatrixRotationZ(&RotateMat, Angle);
		break;
	}
	
	D3DXMatrixTranslation(&TransMat, position.x - MovePivot.x, position.y - MovePivot.y, position.z - MovePivot.y);
	
	WorldMat *= RotateMat * TransMat * worldmat;
}

void Box::Draw(float delta)
{
	//DEVICE->SetRenderState(D3DRS_CULLMODE, false);
	DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	DEVICE->SetFVF(PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
							vec_Vertexs.size() / 3,
							&vec_Vertexs[8],
							sizeof(PC_VERTEX));
	//DEVICE->SetRenderState(D3DRS_CULLMODE, true);
}