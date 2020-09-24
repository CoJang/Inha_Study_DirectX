#include "stdafx.h"
#include "Box.h"


Box::Box()
	: angle(0.0f)
	, velocity(0.0f)
	, dir(0, 0, -1)
	, position(0, 0, 0)
{
}


Box::~Box()
{
}

void Box::Init()
{
	PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(0, 0, 255);

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
	vec_Vertexs[0].c = D3DCOLOR_XRGB(0, 255, 255);
	vec_Vertexs[1].c = D3DCOLOR_XRGB(0, 255, 255);
	vec_Vertexs[2].c = D3DCOLOR_XRGB(0, 255, 255);
	vec_Vertexs[3].c = D3DCOLOR_XRGB(0, 255, 255);
	
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
	velocity = 0;
	D3DXMATRIXA16 temp;
	D3DXMatrixIdentity(&temp);

	// 'W' = 0x57 'A' = 0x41 'S' = 0x53 'D' = 0x44
	if (GetKeyState('W') & 0x8000)
	{
		velocity = 10.5f * delta;
	}
	if (GetKeyState('A') & 0x8000)
	{
		D3DXVec3TransformNormal(&dir, &dir, D3DXMatrixRotationY(&temp, -5.0f * delta));
		angle -= 5.0f * delta;
	}
	if (GetKeyState('S') & 0x8000)
	{
		velocity = -8.5f * delta;
	}
	if (GetKeyState('D') & 0x8000)
	{
		D3DXVec3TransformNormal(&dir, &dir, D3DXMatrixRotationY(&temp, 5.0f * delta));
		angle += 5.0f * delta;
	}
	else
	{

	}

	position += dir * velocity;
	D3DXMatrixTranslation(&TransMat, position.x, position.y, position.z);
	D3DXMatrixRotationY(&RotateMat, angle);

	WorldMat = ScaleMat * RotateMat * TransMat;
}

void Box::Draw(float delta)
{
	DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	DEVICE->SetFVF(PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
							vec_Vertexs.size() / 3,
							&vec_Vertexs[8],
							sizeof(PC_VERTEX));
}
