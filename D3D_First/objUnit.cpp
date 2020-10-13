#include "stdafx.h"
#include "ObjectSrc/Group.h"
#include "ObjectSrc/OBJ_Loader.h"
#include "objUnit.h"

objUnit::objUnit()
	:Scale(1, 1, 1)
	, RotateAngle(0, 0, 0)
	, Position(0, 0, 0)
{
	D3DXMatrixIdentity(&ScaleMat);
	D3DXMatrixIdentity(&RotateMat);
	D3DXMatrixIdentity(&TransMat);
	D3DXMatrixIdentity(&WorldMat);
}

objUnit::~objUnit()
{
}


void objUnit::Init(char* folder, char* file)
{
	Loader Loder;
	Loder.LoadOBJ(vecGroup, folder, file);
}

void objUnit::Update(float delta)
{
	D3DXMatrixScaling(&ScaleMat, Scale.x, Scale.y, Scale.z);
	
	D3DXMATRIXA16 XRotMat, YRotMat, ZRotMat;
	D3DXMatrixIdentity(&XRotMat);
	//D3DXMatrixIdentity(&YRotMat);
	//D3DXMatrixIdentity(&ZRotMat);

	D3DXMatrixRotationX(&XRotMat, RotateAngle.x);
	//D3DXMatrixRotationY(&YRotMat, RotateAngle.y);
	//D3DXMatrixRotationZ(&ZRotMat, RotateAngle.z);
	//RotateMat = XRotMat * YRotMat * ZRotMat;
	RotateMat = XRotMat;

	D3DXMatrixTranslation(&TransMat, Position.x, Position.y, Position.z);

	if (WorldMat != ScaleMat * RotateMat * TransMat)
	{
		WorldMat = ScaleMat * RotateMat * TransMat;
		RePositionVertice();
	}
}

void objUnit::Render(float delta)
{
	for each (auto p in vecGroup)
	{
		p->Render(delta);
	}
}



void objUnit::RePositionVertice()
{
	D3DXMatrixScaling(&ScaleMat, Scale.x, Scale.y, Scale.z);
	D3DXMatrixRotationX(&RotateMat, RotateAngle.x);
	D3DXMatrixTranslation(&TransMat, Position.x, Position.y, Position.z);
	WorldMat = ScaleMat * RotateMat * TransMat;
	
	for(int groupNum = 0; groupNum < vecGroup.size(); groupNum++)
		for (int i = 0; i < vecGroup[groupNum]->GetVertex().size(); i += 3)
		{
			D3DXVec3TransformCoord(&vecGroup[groupNum]->GetVertex()[i].p, &vecGroup[groupNum]->GetVertex()[i].p, &WorldMat);
			D3DXVec3TransformCoord(&vecGroup[groupNum]->GetVertex()[i + 1].p, &vecGroup[groupNum]->GetVertex()[i + 1].p, &WorldMat);
			D3DXVec3TransformCoord(&vecGroup[groupNum]->GetVertex()[i + 2].p, &vecGroup[groupNum]->GetVertex()[i + 2].p, &WorldMat);
		}
}
