#include "framework.h"

#include "cGrid.h"
#include "MyCamera.h"


#include "cGameScene.h"

cGameScene::cGameScene()
	:m_pGrid(nullptr)
	,m_pCamera(nullptr)
{
}

cGameScene::~cGameScene()
{
}

void cGameScene::InitGameScene()
{
	m_pGrid = new MyGrid;
	m_pGrid->Init(10, 1.0f);

	m_pCamera = new MyCamera;
	m_pCamera->Init();
}

void cGameScene::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
}

void cGameScene::Update(float delta)
{
	m_pCamera->Update(delta);
}

void cGameScene::Render(float delta)
{
	if(g_pDevice)
	{
		g_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		g_pDevice->BeginScene();

		m_pGrid->Draw(delta);
		
		g_pDevice->EndScene();
		g_pDevice->Present(NULL, NULL, NULL, NULL);
	}
}
