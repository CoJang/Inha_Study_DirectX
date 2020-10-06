#include "stdafx.h"
#include "DeviceManager.h"
#include "MyGrid.h"
#include "BoxChar.h"
#include "MyCamera.h"

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
		*CamFov += Input * 0.1f;
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

void GameScene::Update(float delta)
{
	Sun.LightUpdate(delta);
	FlashLight.LightUpdate(delta);
	Torch.LightUpdate(delta);
	
	Camera->Update(delta);
	Grid->Update(delta);
	Line->Update(delta);
	Zemmin2->InputCheck(delta);
	Zemmin2->Update(delta);
	Camera->SetCamTarget(Zemmin2->GetPos());


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
		pos = D3DXVECTOR3(pos.x - delta, pos.y, pos.z );
		FlashLight.SetPosition(pos);
	}

	if (GetKeyState(VK_NUMPAD6) & 0x8000)
	{
		D3DXVECTOR3 pos = FlashLight.GetPosition();
		pos = D3DXVECTOR3(pos.x + delta, pos.y, pos.z);
		FlashLight.SetPosition(pos);
	}

	
	static float SunTimer = 0;
	static float moveDir = -1.0f;
	SunTimer += delta;
	
	//if(SunTimer > 1.0f)
	{
		D3DXVECTOR3 dir = Sun.GetDirection();

		D3DXMATRIXA16 RotMat;
		D3DXMatrixIdentity(&RotMat);
		D3DXMatrixRotationZ(&RotMat, 1.0f * delta);
		D3DXVec3TransformNormal(&dir, &dir, &RotMat);
	
		Sun.SetDirection(dir);
		SunTimer = 0;
	}
}

void GameScene::Render(float delta)
{
	if(DEVICE)
	{
		DEVICE->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		DEVICE->BeginScene();

		Grid->Draw(delta);
		Line->Draw(delta);
		Zemmin2->Draw(delta);

		//FlashLight.DrawGizmo(delta);
		Torch.DrawGizmo(delta);

		DEVICE->EndScene();
		DEVICE->Present(NULL, NULL, NULL, NULL);
	}
}

