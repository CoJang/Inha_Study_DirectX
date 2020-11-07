#include "framework.h"
#include "MyCamera.h"
#include "Scene.h"


cScene::cScene()
{
	m_pCamera = new MyCamera;
	m_sceneState = new SSLoad;
}


cScene::~cScene()
{
	delete m_pCamera;
}

void cScene::Setup()
{
	m_pCamera->Init();
	m_sceneState->Setup();
}

void cScene::Update()
{
	m_pCamera->Update(0);
	m_sceneState->Update();
}

void cScene::Render()
{
	if (g_pDevice)
	{
		g_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		g_pDevice->BeginScene();

		m_sceneState->Render();

		g_pDevice->EndScene();
		g_pDevice->Present(NULL, NULL, NULL, NULL);
	}
}

void cScene::SetSceneState(ISceneState* scenestate)
{
	if(scenestate)
	{
		m_sceneState = scenestate;
	}
}
