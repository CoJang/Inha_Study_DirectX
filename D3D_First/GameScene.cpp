#include "stdafx.h"
#include "DeviceManager.h"
#include "MyGrid.h"
#include "BoxChar.h"
#include "MyCamera.h"
#include "GameScene.h"

GameScene::GameScene()
{
	m_pTexture = NULL;
}


GameScene::~GameScene()
{
	SafeDelete(Camera);
	SafeDelete(Grid);
	SafeDelete(Line);
	SafeDelete(Zemmin2);
	SafeRelease(m_pTexture);
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

	{
		D3DXCreateTextureFromFile(DEVICE, TEXT("metal_01-18.png"), &m_pTexture);
		
		PT_VERTEX v;
		v.p = D3DXVECTOR3(0, 0, 0);
		v.t = D3DXVECTOR2(0, 1);
		vec_Vertex.push_back(v);

		v.p = D3DXVECTOR3(0, 1, 0);
		v.t = D3DXVECTOR2(0, 0);
		vec_Vertex.push_back(v);

		v.p = D3DXVECTOR3(1, 1, 0);
		v.t = D3DXVECTOR2(1, 0);
		vec_Vertex.push_back(v);
	}
}

void GameScene::SetLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3 Dir(0.0f, -1.0f, -1.0f);
	D3DXVec3Normalize(&Dir, &Dir);

	stLight.Direction = Dir;
	DEVICE->SetLight(0, &stLight);
	DEVICE->LightEnable(0, true);
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

		//DrawTexture(delta);
		
		DEVICE->EndScene();
		DEVICE->Present(NULL, NULL, NULL, NULL);
	}
}

void GameScene::DrawTexture(float delta)
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	DEVICE->SetTransform(D3DTS_WORLD, &matWorld);
	DEVICE->SetTexture(0, m_pTexture);
	DEVICE->SetFVF(PT_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
							vec_Vertex.size() / 3,
							&vec_Vertex[0],
							sizeof(PT_VERTEX));

	DEVICE->SetTexture(0, NULL);
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
}

