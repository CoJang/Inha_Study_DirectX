#include "stdafx.h"
#include "ObjectSrc/MyGrid.h"
#include "ObjectSrc/PlayerSrc/BoxChar.h"
#include "MyCamera.h"

#include "ObjectSrc/Group.h"
#include "objUnit.h"

#include "GameScene.h"

GameScene::GameScene()
	:Sun(0)
	,FlashLight(1)
	,Torch(2)
{
}


GameScene::~GameScene()
{
	SafeDelete(Camera);
	SafeDelete(Grid);
	SafeDelete(Line);
	SafeDelete(Zemmin2);
	SafeDelete(Bot_Zemmin2);
	SafeDelete(map_surface);
	DEVICEMANAGER->Destroy();
}


void GameScene::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	static POINT MousePos;
	static POINT OldMousePos;
	
	switch (Msg)
	{
	case WM_MOUSEMOVE:
		switch(wParam)
		{
		case MK_LBUTTON:
			{
				MousePos.x = LOWORD(lParam);
				MousePos.y = HIWORD(lParam);

				D3DXMATRIXA16 tempX, tempY;
				D3DXVECTOR3 CameraPosition = *CamPos;
				D3DXMatrixRotationY(&tempX, (OldMousePos.x - MousePos.x) * -0.01f);
				D3DXMatrixRotationX(&tempY, (OldMousePos.y - MousePos.y) * 0.02f);
				
				D3DXVec3TransformCoord(CamPos, &CameraPosition, &(tempX * tempY));
				break;
			}
		default:
			break;
		}
		OldMousePos.x = LOWORD(lParam);
		OldMousePos.y = HIWORD(lParam);
		break;
	case WM_MOUSEWHEEL:
	{
		short Input = HIWORD(wParam);
		Input /= 120;
		//*CamFov += Input * 0.1f;
		CamPos->y += Input;
		CamPos->z += Input;
	}
	break;
	default:
		break;
	}
}

void GameScene::InitGameScene()
{
	SetLight();

	Grid = new MyGrid;
	Grid->Init(30, 0.5f);

	Line = new AxisLine;
	Line->Init();

	Zemmin2 = new BoxChar;
	Zemmin2->Init();
	OldCharPos = Zemmin2->GetPos();
	//Zemmin2->SetPos(Zemmin2->GetPos() + D3DXVECTOR3(0, 3.6f, 0));
	
	{
		bc = new BezierCurve;
		bc->Init();

		map_surface = new objUnit;
		map_surface->Init("Data", "map_surface.obj");
		map_surface->SetScale(0.1f, 0.1f, 0.1f);
		map_surface->SetAngleX(Deg2Rad(-90));
	}

	Bot_Zemmin2 = new BoxCharBot;
	Bot_Zemmin2->Init();
	Bot_Zemmin2->SetPos(D3DXVECTOR3(5, 4.1f, 5));
	Bot_Zemmin2->SetTexture(TEXT("texture/78075e030cd39335.png"));
	Bot_Zemmin2->SetDestList(bc->GetVertexList());
	Bot_Zemmin2->SetLook(D3DXVECTOR3(0, 0, 0));
	Bot_Zemmin2->SetState(AnimState::WALK, 5.0f);

	Camera = new MyCamera;
	Camera->Init();

	CamPos = Camera->GetCamPos();
	CamTarget = Camera->GetCamTarget();
	CamFov = Camera->GetCamFov();
}

void GameScene::SetLight()
{
	Sun.SetDiffuseColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	Sun.SetAmbientColor(D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f));
	Sun.SetSpecularColor(D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f));
	//Sun.SetLightState(false);

	FlashLight.SetDiffuseColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	FlashLight.SetAmbientColor(D3DXCOLOR(0.0f, 0.8f, 0.0f, 1.0f));
	FlashLight.SetSpecularColor(D3DXCOLOR(0.0f, 0.8f, 0.0f, 1.0f));
	FlashLight.SetDirection(D3DXVECTOR3(0, 1, 0));
	FlashLight.SetPosition(D3DXVECTOR3(0, 5, 0));
	FlashLight.SetRange(10.0f);
	//FlashLight.SetLightState(false);

	Torch.SetDiffuseColor(D3DXCOLOR(0.0f, 0.0f, 5.0f, 1.0f));
	Torch.SetAmbientColor(D3DXCOLOR(0.0f, 0.0f, 0.3f, 1.0f));
	Torch.SetSpecularColor(D3DXCOLOR(0.0f, 0.0f, 0.3f, 1.0f));
	Torch.SetPosition(D3DXVECTOR3(10, 3, 10));
	Torch.SetRange(5.0f);
	//Torch.SetLightState(false);
}

void GameScene::InputCheck(float delta)
{
	Zemmin2->InputCheck(delta);
	
	if (GetKeyState(VK_ADD) & 0x8000)
	{
		Torch.SetRange(Torch.GetRange() + delta);
	}

	if (GetKeyState(VK_SUBTRACT) & 0x8000)
	{
		Torch.SetRange(Torch.GetRange() - delta);
	}

	if (GetKeyState(VK_NUMPAD2) & 0x8000)
	{
		D3DXVECTOR3 pos = FlashLight.GetPosition();
		pos = D3DXVECTOR3(pos.x, pos.y, pos.z - delta);
		FlashLight.SetPosition(pos);
	}

	if (GetKeyState(VK_NUMPAD8) & 0x8000)
	{
		//D3DXVECTOR3 pos = FlashLight.GetPosition();
		D3DXVECTOR3 dir = FlashLight.GetDirection();
		D3DXMATRIXA16 RotMat;
		D3DXMatrixIdentity(&RotMat);
		D3DXMatrixRotationX(&RotMat, 1.0f);
		D3DXVec3TransformNormal(&dir, &dir, &RotMat);

		//dir = D3DXVECTOR3(dir.x, dir.y, dir.z + 1.0f);
		FlashLight.SetDirection(dir);
	}

	if (GetKeyState(VK_NUMPAD4) & 0x8000)
	{
		D3DXVECTOR3 pos = FlashLight.GetPosition();
		pos = D3DXVECTOR3(pos.x - delta, pos.y, pos.z);
		FlashLight.SetPosition(pos);
	}

	if (GetKeyState(VK_NUMPAD6) & 0x8000)
	{
		D3DXVECTOR3 pos = FlashLight.GetPosition();
		pos = D3DXVECTOR3(pos.x + delta, pos.y, pos.z);
		FlashLight.SetPosition(pos);
	}
}

void GameScene::Update(float delta)
{
	InputCheck(delta);
	
	Sun.LightUpdate(delta);
	FlashLight.LightUpdate(delta);
	Torch.LightUpdate(delta);
	
	Camera->Update(delta);
	Grid->Update(delta);
	Line->Update(delta);
	
	
	Zemmin2->Update(delta);

	Bot_Zemmin2->Update(delta);
	
	Camera->SetCamTarget(Zemmin2->GetPos());

	map_surface->Update(delta);
	
	
	if(OldCharPos != Zemmin2->GetPos())
	{
		MapCheck(Zemmin2->GetPos(), map_surface->GetGroups());
		OldCharPos = Zemmin2->GetPos();
	}



	
	//static float SunTimer = 0;
	//static float moveDir = -1.0f;
	//SunTimer += delta;
	
	//if(SunTimer > 1.0f)
	{
		D3DXVECTOR3 dir = Sun.GetDirection();

		D3DXMATRIXA16 RotMat;
		D3DXMatrixIdentity(&RotMat);
		D3DXMatrixRotationZ(&RotMat, 1.0f * delta);
		D3DXVec3TransformNormal(&dir, &dir, &RotMat);
	
		Sun.SetDirection(dir);
		//SunTimer = 0;
	}
}

void GameScene::Render(float delta)
{
	if(DEVICE)
	{
		DEVICE->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		DEVICE->BeginScene();

		map_surface->Render(delta);
		
		Grid->Draw(delta);
		Line->Draw(delta);
		Zemmin2->Draw(delta);
		
		Bot_Zemmin2->Draw(delta);

		FlashLight.DrawGizmo(delta);
		Torch.DrawGizmo(delta);

		{
			
			bc->Draw(delta);
		}
		

		DEVICE->EndScene();
		DEVICE->Present(NULL, NULL, NULL, NULL);
	}
}

float GameScene::MapCheck(D3DXVECTOR3& charpos, vector<Group*>& terrain)
{
	float U(0), V(0), Dist(0);
	bool IsHit = false;

	D3DXVECTOR3 TempPos = charpos + D3DXVECTOR3(0, 0.1f, 0);
	D3DXVECTOR3 TempDir = D3DXVECTOR3(0, -1, 0);
	
	for (int groupNum = 0; groupNum < terrain.size(); groupNum++)
	{
		for (int i = 0; i < terrain[groupNum]->GetVertex().size(); i += 3)
		{
			if(D3DXIntersectTri(&terrain[groupNum]->GetVertex()[i].p,
				&terrain[groupNum]->GetVertex()[i + 1].p,
				&terrain[groupNum]->GetVertex()[i + 2].p,
				&TempPos,
				&TempDir,
				&U, &V, &Dist))
			{
				IsHit = true;
				break;
			}
		}
		
		if (IsHit) break;
	}

	if(IsHit)
	{
		D3DXVECTOR3 MovedPos = TempPos + (TempDir * Dist);
		D3DXVECTOR3 Anchor(0, 4.1f, 0);
		Zemmin2->SetPos(MovedPos + Anchor);
	}
	return Dist;
}

