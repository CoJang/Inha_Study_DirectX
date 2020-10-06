#include "stdafx.h"
#include "DeviceManager.h"
#include "MyGrid.h"
#include "BoxChar.h"
#include "MyCamera.h"

#include "GameScene.h"

GameScene::GameScene()
	:Sun(0)
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
		D3DXCreateTextureFromFile(DEVICE, TEXT("texture/metal_01-18.png"), &m_pTexture);
		
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
	Sun.SetAmbientColor(D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f));
	Sun.SetDiffuseColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	Sun.SetSpecularColor(D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f));
}

void GameScene::Update(float delta)
{
	Sun.LightUpdate(delta);
	
	Camera->Update(delta);
	Grid->Update(delta);
	Line->Update(delta);
	Zemmin2->InputCheck(delta);
	Zemmin2->Update(delta);
	Camera->SetCamTarget(Zemmin2->GetPos());


	if (GetKeyState(VK_ADD) & 0x8000)
	{
		D3DXVECTOR3 dir = Sun.GetDirection();
		Sun.SetDirection(D3DXVECTOR3(dir.x, dir.y + 5.0f * delta, dir.z));
		cout << dir.y << endl;
	}

	if (GetKeyState(VK_SUBTRACT) & 0x8000)
	{
		D3DXVECTOR3 dir = Sun.GetDirection();
		Sun.SetDirection(D3DXVECTOR3(dir.x, dir.y - 5.0f * delta, dir.z));
		cout << dir.y << endl;
	}

	
	static float SunTimer = 0;
	static float moveDir = -1.0f;
	SunTimer += delta;
	
	if(SunTimer > 1.0f)
	{
		D3DXVECTOR3 dir = Sun.GetDirection();

		D3DXMATRIXA16 RotMat;
		D3DXMatrixIdentity(&RotMat);
		D3DXMatrixRotationZ(&RotMat, 0.5f);
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

		DrawTexture(delta);
		
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

