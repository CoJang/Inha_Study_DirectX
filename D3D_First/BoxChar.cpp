#include "stdafx.h"
#include "Box.h"
#include "BoxChar.h"


BoxChar::BoxChar()
	:position(0, 3.5, 0)
	,angle(0.0f)
	,velocity(0.0f)
	,dir(0, 0, -1)
{
}


BoxChar::~BoxChar()
{
	for (int i = 0; i < Bodies.size(); i++)
	{
		delete Bodies[i];
		Bodies.erase(Bodies.begin() + i);
		i--;
	}
}

void BoxChar::Init()
{
	D3DXVECTOR3 Pivot;
	Pivot = D3DXVECTOR3(0, 0, 0);
	BodyPivots.push_back(Pivot);
	Pivot += position;
	Box* Body = new Box;
	Body->Init(Pivot, D3DXVECTOR3(0.8f, 1.5f, 0.5f), D3DCOLOR_XRGB(0, 255, 255));
	Bodies.push_back(Body);

	Box* Head = new Box;
	Pivot = D3DXVECTOR3(0, 2, 0);
	BodyPivots.push_back(Pivot);
	Pivot += position;
	Head->Init(Pivot, D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DCOLOR_XRGB(255, 255, 255));
	Bodies.push_back(Head);

	Box* LeftArm = new Box;
	Pivot = D3DXVECTOR3(1.2f, 0.5f, 0);
	BodyPivots.push_back(Pivot);
	Pivot += position;
	LeftArm->Init(Pivot, D3DXVECTOR3(0.4f, 1.0f, 0.5f), D3DCOLOR_XRGB(255, 0, 0));
	Bodies.push_back(LeftArm);
	cout << *BodyPivots[2] << endl;
	Bodies[2]->SetPivot(D3DXVECTOR3(1.0f, -0.5f, 0));

	Box* RightArm = new Box;
	Pivot = D3DXVECTOR3(-1.2f, 0.5f, 0);
	BodyPivots.push_back(Pivot);
	Pivot += position;
	RightArm->Init(Pivot, D3DXVECTOR3(0.4f, 0.7f, 0.5f), D3DCOLOR_XRGB(0, 0, 255));
	Bodies.push_back(RightArm);

	Box* LeftLeg = new Box;
	Pivot = D3DXVECTOR3(0.4f, -2.5f, 0);
	BodyPivots.push_back(Pivot);
	Pivot += position;
	LeftLeg->Init(Pivot, D3DXVECTOR3(0.4f, 1.0f, 0.5f), D3DCOLOR_XRGB(255, 0, 0));
	Bodies.push_back(LeftLeg);

	Box* RightLeg = new Box;
	Pivot = D3DXVECTOR3(-0.4f, -2.5f, 0);
	BodyPivots.push_back(Pivot);
	Pivot += position;
	RightLeg->Init(Pivot, D3DXVECTOR3(0.4f, 1.0f, 0.5f), D3DCOLOR_XRGB(0, 0, 255));
	Bodies.push_back(RightLeg);
   	
	for (int i = 0; i < Bodies.size(); i++)
	{
		D3DXVECTOR3 newPos = D3DXVECTOR3(BodyPivots[i].x, BodyPivots[i].y, BodyPivots[i].z);
		Bodies[i]->SetPos(newPos);
		//if(i > 1)
		//{
		//	Bodies[i]->SetPivot(D3DXVECTOR3(Bodies[i]->GetPos().x / 2, Bodies[i]->GetPos().y / 2, 0));
		//}
	}
}

void BoxChar::Update(float delta)
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

	D3DXVec3Normalize(&dir, &dir);

	position += dir * velocity;
	D3DXMatrixTranslation(&TransMat, position.x, position.y, position.z);
	D3DXMatrixRotationY(&RotateMat, angle);

	WorldMat = ScaleMat * RotateMat * TransMat;

	static float tempAngle = 0;
	tempAngle += 5.0f * delta;
	Bodies[2]->SetAngle(tempAngle, 'x');
	
	for(int i = 0; i < Bodies.size(); i++)
	{
		Bodies[i]->Update(delta, WorldMat);
	}
}

void BoxChar::Draw(float delta)
{
	//DEVICE->SetRenderState(D3DRS_CULLMODE, false);
	for( Box* B : Bodies )
	{
		B->Draw(delta);
	}
	//DEVICE->SetRenderState(D3DRS_CULLMODE, true);
}
