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
	Box* Body = new Box;
	Body->Init(D3DXVECTOR3(position.x + Pivot.x, position.y + Pivot.y, position.z + Pivot.z),
		D3DXVECTOR3(0.8f, 1.5f, 0.5f), D3DCOLOR_XRGB(0, 255, 255));
	Bodies.push_back(Body);

	Box* Head = new Box;
	Pivot = D3DXVECTOR3(0, 2, 0);
	BodyPivots.push_back(Pivot);
	Head->Init(D3DXVECTOR3(position.x + Pivot.x, position.y + Pivot.y, position.z + Pivot.z),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DCOLOR_XRGB(255, 255, 255));
	Bodies.push_back(Head);

	Box* LeftArm = new Box;
	Pivot = D3DXVECTOR3(1.2f, 0.5f, 0);
	BodyPivots.push_back(Pivot);
	LeftArm->Init(D3DXVECTOR3(position.x + Pivot.x, position.y + Pivot.y, position.z + Pivot.z),
		D3DXVECTOR3(0.4f, 0.7f, 0.5f), D3DCOLOR_XRGB(255, 0, 0));
	Bodies.push_back(LeftArm);

	Box* RightArm = new Box;
	Pivot = D3DXVECTOR3(-1.2f, 0.5f, 0);
	BodyPivots.push_back(Pivot);
	RightArm->Init(D3DXVECTOR3(position.x + Pivot.x, position.y + Pivot.y, position.z + Pivot.z),
		D3DXVECTOR3(0.4f, 0.7f, 0.5f), D3DCOLOR_XRGB(0, 0, 255));
	Bodies.push_back(RightArm);

	Box* LeftLeg = new Box;
	Pivot = D3DXVECTOR3(0.4f, -2.5f, 0);
	BodyPivots.push_back(Pivot);
	LeftLeg->Init(D3DXVECTOR3(position.x + Pivot.x, position.y + Pivot.y, position.z + Pivot.z),
		D3DXVECTOR3(0.4f, 1.0f, 0.5f), D3DCOLOR_XRGB(255, 0, 0));
	Bodies.push_back(LeftLeg);

	Box* RightLeg = new Box;
	Pivot = D3DXVECTOR3(-0.4f, -2.5f, 0);
	BodyPivots.push_back(Pivot);
	RightLeg->Init(D3DXVECTOR3(position.x + Pivot.x, position.y + Pivot.y, position.z + Pivot.z),
		D3DXVECTOR3(0.4f, 1.0f, 0.5f), D3DCOLOR_XRGB(0, 0, 255));
	Bodies.push_back(RightLeg);

	AnimAngle.push_back(0);
	AnimAngle.push_back(0);
	AnimAngle.push_back(100);
	AnimAngle.push_back(100);
	AnimAngle.push_back(100);
	AnimAngle.push_back(100);
	
	Bodies[2]->SetPivot(D3DXVECTOR3(Bodies[2]->GetPos().x / 2, 0, 0));
	Bodies[3]->SetPivot(D3DXVECTOR3(Bodies[3]->GetPos().x / 2, 0, 0));
	Bodies[4]->SetPivot(D3DXVECTOR3(Bodies[4]->GetPos().x / 2, 0, 0));
	Bodies[5]->SetPivot(D3DXVECTOR3(Bodies[5]->GetPos().x / 2, 0, 0));
	
	for (int i = 0; i < Bodies.size(); i++)
	{
		D3DXVECTOR3 newPos = D3DXVECTOR3(BodyPivots[i].x, BodyPivots[i].y, BodyPivots[i].z);
		Bodies[i]->SetPos(newPos);
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
		Bodies[1]->SetAngle(0, 'y');
		for(int i = 2; i < Bodies.size(); i++)
			Bodies[i]->SetAngle(AnimAngle[i], 'x');
	}
	if (GetKeyState('A') & 0x8000)
	{
		D3DXVec3TransformNormal(&dir, &dir, D3DXMatrixRotationY(&temp, -5.0f * delta));
		angle -= 5.0f * delta;
		AnimAngle[1] = angle;
		
		for (int i = 2; i < Bodies.size(); i++)
			Bodies[i]->SetAngle(0, 'x');
	}
	if (GetKeyState('S') & 0x8000)
	{
		velocity = -8.5f * delta;
		Bodies[1]->SetAngle(0, 'y');
		for (int i = 2; i < Bodies.size(); i++)
			Bodies[i]->SetAngle(-AnimAngle[i], 'x');
	}
	if (GetKeyState('D') & 0x8000)
	{
		D3DXVec3TransformNormal(&dir, &dir, D3DXMatrixRotationY(&temp, 5.0f * delta));
		angle += 5.0f * delta;
		Bodies[1]->SetAngle(angle, 'y');
		
		for (int i = 2; i < Bodies.size(); i++)
			Bodies[i]->SetAngle(0, 'x');
	}
	//else
	//{
	//	for (int i = 0; i < Bodies.size(); i++)
	//		Bodies[i]->SetAngle(0, 'x');
	//}
	D3DXVec3Normalize(&dir, &dir);

	position += dir * velocity;
	D3DXMatrixTranslation(&TransMat, position.x, position.y, position.z);
	D3DXMatrixRotationY(&RotateMat, angle);

	WorldMat = ScaleMat * RotateMat * TransMat;
	
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
