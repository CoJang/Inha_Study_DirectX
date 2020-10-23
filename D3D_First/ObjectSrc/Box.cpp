#include "stdafx.h"
#include "Box.h"


Box::Box()
	: Position(0, 0, 0)
	, MovePivot(0, 0, 0)
	, RotateAngle(0, 0, 0)
	, MaxAngle(0.0f)
	, AnimDirection(0)
	, texture(NULL)
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
	//material.Diffuse = D3DXCOLOR(color.r, color.g, color.b, 1.0f);
	//material.Ambient = D3DXCOLOR(color.r * 0.6f, color.g * 0.6f, color.b * 0.6f, 1.0f);
	//material.Specular = D3DXCOLOR(color.r, color.g, color.b, 1.0f);

	material.Diffuse = color;
	material.Ambient = color;
	material.Specular = color;
	
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

	//4
	vertex.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vec.push_back(vertex);
	//5
	vertex.p = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vec.push_back(vertex);
	//6
	vertex.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vec.push_back(vertex);
	//7
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
	D3DXMATRIXA16 AxisMat;
	D3DXMatrixIdentity(&AxisMat);

	D3DXMatrixTranslation(&AxisMat, MovePivot.x, MovePivot.y, MovePivot.z);
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

	WorldMat *= RotateMat * TransMat;
}

void Box::Update(float delta, D3DXMATRIXA16 & worldmat)
{
	D3DXMATRIXA16 AxisMat;
	D3DXMatrixIdentity(&AxisMat);
	
	D3DXMatrixTranslation(&AxisMat, MovePivot.x, MovePivot.y, MovePivot.z);
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
}

void Box::Draw(float delta)
{
	//DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	//DEVICE->SetRenderState(D3DRS_CULLMODE, false);

	DEVICE->SetMaterial(&material);
	DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	DEVICE->SetFVF(PNT_VERTEX::FVF);
	
	if (texture) DEVICE->SetTexture(0, *texture);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
							vec_Vertexs.size() / 3,
							&vec_Vertexs[0],
							sizeof(PNT_VERTEX));
	if (texture) DEVICE->SetTexture(0, NULL);

	//DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	//DEVICE->SetRenderState(D3DRS_CULLMODE, true);
}

void Box::LoadTexture(char* Path)
{
	texture = new LPDIRECT3DTEXTURE9;
	D3DXCreateTextureFromFileA(DEVICE, Path, texture);
}

void Box::SetMaterialColor(D3DXCOLOR color)
{
	material.Ambient = color;
	material.Diffuse = color;
	material.Specular = color;
}

SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
}

void SkyBox::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXCOLOR color)
{
	Position = pos;
	Scale = scale;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	//material.Diffuse = D3DXCOLOR(color.r, color.g, color.b, 1.0f);
	//material.Ambient = D3DXCOLOR(color.r * 0.6f, color.g * 0.6f, color.b * 0.6f, 1.0f);
	//material.Specular = D3DXCOLOR(color.r, color.g, color.b, 1.0f);

	material.Diffuse = color;
	material.Ambient = color;
	material.Specular = color;

	D3DXMatrixScaling(&ScaleMat, Scale.x, Scale.y, Scale.z);

	PNT_VERTEX vertex;
	std::vector<PNT_VERTEX> vec;
	vertex.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	vertex.t = D3DXVECTOR2(0, 1);
	vec.push_back(vertex);

	vertex.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	vertex.t = D3DXVECTOR2(0, 0);
	vec.push_back(vertex);

	vertex.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	vertex.t = D3DXVECTOR2(1, 0);
	vec.push_back(vertex);

	vertex.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	vertex.t = D3DXVECTOR2(1, 1);
	vec.push_back(vertex);

	//4
	vertex.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vertex.t = D3DXVECTOR2(0, 1);
	vec.push_back(vertex);
	//5
	vertex.p = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vertex.t = D3DXVECTOR2(0, 0);
	vec.push_back(vertex);
	//6
	vertex.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vertex.t = D3DXVECTOR2(1, 0);
	vec.push_back(vertex);
	//7
	vertex.p = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	vertex.t = D3DXVECTOR2(1, 1);
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
