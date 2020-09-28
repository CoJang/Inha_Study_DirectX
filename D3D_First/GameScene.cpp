#include "stdafx.h"
#include "DeviceManager.h"
#include "MyGrid.h"
#include "BoxChar.h"
#include "MyCamera.h"
#include "GameScene.h"

GameScene::GameScene()
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
	Grid = new MyGrid;
	Grid->Init(15, 1.0f);

	Line = new AxisLine;
	Line->Init();

	Zemmin2 = new BoxChar;
	Zemmin2->Init();

	Camera = new MyCamera;
	Camera->Init();

	CamPos = Camera->GetCamPos();
	CamTarget = Camera->GetCamTarget();
	CamFov = Camera->GetCamFov();

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
}

void GameScene::Update(float delta)
{
	Camera->Update(delta);
	Grid->Update(delta);
	Line->Update(delta);
	Zemmin2->InputCheck(delta);
	Zemmin2->Update(delta);
	Camera->SetCamTarget(Zemmin2->GetPos());
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
		
		DEVICE->EndScene();
		DEVICE->Present(NULL, NULL, NULL, NULL);
	}
}

