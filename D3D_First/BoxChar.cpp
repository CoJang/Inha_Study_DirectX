#include "stdafx.h"
#include "BCBody.h"
#include "BCHead.h"
#include "BCLeftArm.h"
#include "BCRightArm.h"
#include "BCLeftLeg.h"
#include "BCRightLeg.h"
#include "BoxChar.h"


BoxChar::BoxChar()
	:position(0, 4.1f, 0)
	,angle(0.0f)
	,velocity(0.0f)
	,dir(0, 0, -1)
	,state(IDLE)
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
	TexturePath = TEXT("texture/5173c405cba4b429.png");
	D3DXCreateTextureFromFile(DEVICE, TexturePath, &Texture);

	D3DXVECTOR3 Pivot;
	D3DXVECTOR3 Scale;
	D3DXCOLOR color;
	
	BCBody* Body = new BCBody;
	Pivot = D3DXVECTOR3(0, 0, 0);
	Scale = D3DXVECTOR3(0.8f, 1.5f, 0.5f);
	Body->Init(Pivot, Scale, D3DCOLOR_XRGB(0, 255, 255));
	Bodies.push_back(Body);

	BCHead* Head = new BCHead;
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Pivot = D3DXVECTOR3(0, 2.5f, 0);
	Head->Init(Pivot, Scale, D3DCOLOR_XRGB(255, 255, 255));
	Bodies.push_back(Head);

	BCLeftArm* LeftArm = new BCLeftArm;
	Pivot = D3DXVECTOR3(1.2f, 0.5f, 0); // »ó´ëÁÂÇ¥
	Scale = D3DXVECTOR3(0.4f, 1.1f, 0.5f);
	LeftArm->Init(Pivot, Scale, D3DCOLOR_XRGB(255, 0, 0));
	LeftArm->SetPivot(D3DXVECTOR3(0, Scale.y * -0.5f, 0));
	Bodies.push_back(LeftArm);

	BCRightArm* RightArm = new BCRightArm;
	Pivot = D3DXVECTOR3(-1.2f, 0.5f, 0);
	Scale = D3DXVECTOR3(0.4f, 1.1f, 0.5f);
	RightArm->Init(Pivot, Scale, D3DCOLOR_XRGB(0, 0, 255));
	RightArm->SetPivot(D3DXVECTOR3(0, Scale.y * -0.5f, 0));
	Bodies.push_back(RightArm);

	BCLeftLeg* LeftLeg = new BCLeftLeg;
	Pivot = D3DXVECTOR3(0.4f, -2.6f, 0);
	Scale = D3DXVECTOR3(0.4f, 1.3f, 0.5f);
	LeftLeg->Init(Pivot, Scale, D3DCOLOR_XRGB(255, 0, 0));
	LeftLeg->SetPivot(D3DXVECTOR3(0, Scale.y * -0.5f, 0));
	Bodies.push_back(LeftLeg);

	BCRightLeg* RightLeg = new BCRightLeg;
	Pivot = D3DXVECTOR3(-0.4f, -2.6f, 0);
	Scale = D3DXVECTOR3(0.4f, 1.3f, 0.5f);
	RightLeg->Init(Pivot, Scale, D3DCOLOR_XRGB(0, 0, 255));
	RightLeg->SetPivot(D3DXVECTOR3(0, Scale.y * -0.5f, 0));
	Bodies.push_back(RightLeg);
}

void BoxChar::InputCheck(float delta)
{
	velocity = 0;
	bool IsKeyDown = false;
	D3DXMATRIXA16 TempRot;
	D3DXMatrixIdentity(&TempRot);
	
	// 'W' = 0x57 'A' = 0x41 'S' = 0x53 'D' = 0x44
	if (GetKeyState('W') & 0x8000)
	{
		IsKeyDown = true;
		velocity = 10.5f * delta;
		state = WALK;
	}
	if (GetKeyState('A') & 0x8000)
	{
		IsKeyDown = true;
		D3DXVec3TransformNormal(&dir, &dir, D3DXMatrixRotationY(&TempRot, -5.0f * delta));
		angle -= 5.0f * delta;
	}
	if (GetKeyState('S') & 0x8000)
	{
		IsKeyDown = true;
		velocity = -8.5f * delta;
		state = WALK;
	}
	if (GetKeyState('D') & 0x8000)
	{
		IsKeyDown = true;
		D3DXVec3TransformNormal(&dir, &dir, D3DXMatrixRotationY(&TempRot, 5.0f * delta));
		angle += 5.0f * delta;
	}

	if(!IsKeyDown)
	{
		state = IDLE;
	}

	D3DXVec3Normalize(&dir, &dir);
}

void BoxChar::Update(float delta)
{
	position += dir * velocity;
	D3DXMatrixTranslation(&TransMat, position.x, position.y, position.z);
	D3DXMatrixRotationY(&RotateMat, angle);

	WorldMat = ScaleMat * RotateMat * TransMat;

	switch(state)
	{
	case IDLE:
		IdleAnim(delta);
		break;
	case WALK:
		WalkAnim(delta);
		break;
	case RUN:
		RunAnim(delta);
		break;
	}
}

void BoxChar::IdleAnim(float delta)
{
	float speed = 5.0f;

	for (int i = 0; i < Bodies.size(); i++)
	{
		float AngleX = Bodies[i]->GetAngleX();

		if(fabs(AngleX) > EPSILON)
		{
			if(AngleX > EPSILON)
			{
				Bodies[i]->SetAngleX(Bodies[i]->GetAngleX() - speed * delta);
			}
			else if(AngleX < EPSILON)
			{
				Bodies[i]->SetAngleX(Bodies[i]->GetAngleX() + speed * delta);
			}
		}

		Bodies[i]->Update(delta, WorldMat);
	}
}

void BoxChar::WalkAnim(float delta)
{
	float speed = 5.0f;
	float MaxAngle = 1.0f;

	static vector<float> AnimAngle = 
	{
		0.0f,  // Body
		0.0f,  // Head	
		1.0f,  // Left Arm
		-1.0f,  // Right Arm
		-1.0f,  // Left Leg	
		1.0f   // Right Leg
	};
									
	for (int i = 0; i < Bodies.size(); i++)
	{
		if(fabs(Bodies[i]->GetAngleX()) > MaxAngle)
		{
			if(Bodies[i]->GetAngleX() > 0)
				Bodies[i]->SetAngleX(MaxAngle);
			else
				Bodies[i]->SetAngleX(-MaxAngle);
			
			AnimAngle[i] *= -1;
		}
				
		Bodies[i]->SetAngleX(Bodies[i]->GetAngleX() + AnimAngle[i] * speed * delta);
		Bodies[i]->Update(delta, WorldMat);
	}
}

void BoxChar::RunAnim(float delta)
{
	float speed = 5.0f;
	float MaxAngle = 1.0f;
	
	static vector<float> AnimAngle =
	{
		0.0f,  // Body
		0.0f,  // Head	
		1.0f,  // Left Arm
		-1.0f,  // Right Arm
		-1.0f,  // Left Leg	
		1.0f   // Right Leg
	};
	
	for (int i = 0; i < Bodies.size(); i++)
	{
		if (fabs(Bodies[i]->GetAngleX()) > MaxAngle)
		{
			if (Bodies[i]->GetAngleX() > 0)
				Bodies[i]->SetAngleX(MaxAngle);
			else
				Bodies[i]->SetAngleX(-MaxAngle);
			
			AnimAngle[i] *= -1;
		}

		Bodies[i]->SetAngleX(Bodies[i]->GetAngleX() + AnimAngle[i] * speed * delta);
		Bodies[i]->Update(delta);
	}
}

void BoxChar::Draw(float delta)
{
	//DEVICE->SetRenderState(D3DRS_CULLMODE, false);
	DEVICE->SetTexture(0, Texture);

	for( Box* B : Bodies )
	{
		B->Draw(delta);
	}
	DEVICE->SetTexture(0, NULL);
	//DEVICE->SetRenderState(D3DRS_CULLMODE, true);
}


BoxCharBot::BoxCharBot()
	:Speed(0)
	,Dest(0, 0, 0)
	,DestIndex(0)
{
}

void BoxCharBot::Update(float delta)
{
	if (fabs(position.x - Dest.x) < EPSILON && fabs(position.z - Dest.z) < EPSILON)
	{
		position.x = Dest.x; position.z = Dest.z;
		SetState(IDLE, 0);
		SetLook(DestList[DestIndex++ % DestList.size()]);
	}
	else
	{
		SetState(WALK, 5.0f);
	}
	
	velocity = Speed * delta;
	position += dir * velocity;
	D3DXMatrixTranslation(&TransMat, position.x, position.y, position.z);
	WorldMat = RotateMat * TransMat;
	
	switch (state)
	{
	case IDLE:
		IdleAnim(delta);
		break;
	case WALK:
		WalkAnim(delta);
		break;
	case RUN:
		RunAnim(delta);
		break;
	}
}

void BoxCharBot::SetLook(D3DXVECTOR3 target)
{
	Dest = target;
	D3DXVECTOR3 LookAt = position - (target - position);
	D3DXMATRIXA16 LookAtMat;
	D3DXMatrixIdentity(&LookAtMat);

	LookAt.y = position.y;
	D3DXMatrixLookAtLH(&LookAtMat, &position, &LookAt, &D3DXVECTOR3(0, 1, 0));
	LookAtMat._41 = LookAtMat._42 = LookAtMat._43 = 0.0f;
	D3DXMatrixTranspose(&LookAtMat, &LookAtMat);

	dir.x = LookAtMat._31; dir.y = LookAtMat._32; dir.z = LookAtMat._33;
	D3DXVec3Normalize(&dir, &-dir);

	RotateMat = LookAtMat;
}

void BoxCharBot::SetState(AnimState anim_state, float speed)
{
	state = anim_state;
	Speed = speed;
}

void BoxCharBot::SetDestList(vector<PC_VERTEX>& vertexlist)
{
	for(int i = 0; i < vertexlist.size(); i++)
	{
		DestList.push_back(vertexlist[i].p);
	}
}
