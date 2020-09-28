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

void Box::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DCOLOR color)
{
	Position = pos;
	Scale = scale;
	D3DXMatrixScaling(&ScaleMat, Scale.x, Scale.y, Scale.z);
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
	//DEVICE->SetRenderState(D3DRS_CULLMODE, false);
	DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	DEVICE->SetFVF(PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
							vec_Vertexs.size() / 3,
							&vec_Vertexs[8],
							sizeof(PC_VERTEX));

	//DEVICE->SetRenderState(D3DRS_CULLMODE, true);
	
	//vector<PC_VERTEX> verIndex;
	//PC_VERTEX v;

	//v.c = 0xffffff;
	//v.p = D3DXVECTOR3(0, 0, 0);
	//verIndex.push_back(v);
	//v.c = 0xffffff;
	//v.p = D3DXVECTOR3(MovePivot.x * 3, -MovePivot.y * 3, MovePivot.z * 3);
	//verIndex.push_back(v);

	//v.c = 0xffffff;
	//v.p = D3DXVECTOR3(0, 0, 0);
	//verIndex.push_back(v);
	//v.c = 0xffffff;
	//v.p = D3DXVECTOR3(MovePivot.x * 3, 0, -MovePivot.y * 3);
	//verIndex.push_back(v);
	

	//DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	//DEVICE->SetFVF(PC_VERTEX::FVF);

	//DEVICE->DrawPrimitiveUP
	//(
	//	D3DPT_LINELIST,
	//	verIndex.size() / 2,
	//	&verIndex[0],
	//	sizeof PC_VERTEX
	//);
}
