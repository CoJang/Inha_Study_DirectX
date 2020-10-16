#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cCamera.h"
#include "cCubePC.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cObjMap.h"	// << : 

#include "cAseLoader.h"
#include "cFrame.h"

cMainGame::cMainGame()
	: m_pCubePC(nullptr)
	  , m_pCamera(nullptr)
	  , m_pGrid(nullptr)
	  , m_pCubeMan(nullptr)
	  , m_pTexture(nullptr)
	  , m_pMap(nullptr)
	  , m_pRootFrame(nullptr)
	  ,m_pMeshTeapot(nullptr)
	  ,m_pMeshSphere(nullptr)
	  ,m_pObjMesh(nullptr)
	  ,m_pAseMesh(nullptr)
{
}


cMainGame::~cMainGame()
{
	SafeDelete(m_pCubePC);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pCubeMan);
	SafeDelete(m_pMap);
	SafeRelease(m_pTexture);
	SafeRelease(m_pMeshTeapot);
	SafeRelease(m_pMeshSphere);
	SafeRelease(m_pObjMesh);
	SafeRelease(m_pAseMesh);

	for each(auto p in m_vecObjMtlTex)
		SafeRelease(p);

	for each (auto p in m_vecGroup)
	{
		SafeRelease(p);
	}
	m_vecGroup.clear();

	m_pRootFrame->Destroy();
	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup_MeshObjects()
{
	D3DXCreateTeapot(g_pD3DDevice, &m_pMeshTeapot, NULL);
	D3DXCreateSphere(g_pD3DDevice, 5.0f, 10, 10, &m_pMeshSphere, NULL);

	ZeroMemory(&m_stMtlTeapot, sizeof(D3DMATERIAL9));
	m_stMtlTeapot.Ambient = D3DXCOLOR(0, 0.5f, 0.5f, 1);
	m_stMtlTeapot.Diffuse = D3DXCOLOR(0, 0.5f, 0.5f, 1);
	m_stMtlTeapot.Specular = D3DXCOLOR(0, 0.5f, 0.5f, 1);
	
	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.5f, 0, 0.5f, 1);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.5f, 0, 0.5f, 1);
	m_stMtlSphere.Specular = D3DXCOLOR(0.5f, 0, 0.5f, 1);

	cObjLoader l;
	m_pObjMesh = l.LoadMesh(m_vecObjMtlTex, "obj", "map.obj");

	cAseLoader aseloader;
	m_pAseMesh = aseloader.LoadMesh(m_vecAseMtlTex, "woman/woman_01_all.ASE");
}

void cMainGame::Mesh_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	g_pD3DDevice->SetTexture(0, NULL);
	//{
	//	D3DXMatrixIdentity(&matWorld);
	//	D3DXMatrixIdentity(&matS);
	//	D3DXMatrixIdentity(&matR);

	//	matWorld = matS * matR;
	//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//	g_pD3DDevice->SetMaterial(&m_stMtlTeapot);
	//	m_pMeshTeapot->DrawSubset(0);
	//}
	//{
	//	D3DXMatrixIdentity(&matWorld);
	//	D3DXMatrixIdentity(&matS);
	//	D3DXMatrixIdentity(&matR);

	//	matWorld = matS * matR;
	//	D3DXMatrixTranslation(&matWorld, 10, 0, 0);
	//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//	g_pD3DDevice->SetMaterial(&m_stMtlSphere);
	//	m_pMeshSphere->DrawSubset(0);
	//}
	{
		//D3DXMatrixIdentity(&matWorld);
		//D3DXMatrixIdentity(&matS);
		//D3DXMatrixIdentity(&matR);
		//D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
		//D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
		//matWorld = matS * matR;

		//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		//for(size_t i = 0; i < m_vecObjMtlTex.size(); ++i)
		//{
		//	g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());
		//	g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());
		//	m_pObjMesh->DrawSubset(i);
		//}
		
	}
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		matWorld = matS * matR;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		for(size_t i = 0; i < m_vecAseMtlTex.size(); ++i)
		{
			g_pD3DDevice->SetMaterial(&m_vecAseMtlTex[i]->GetMaterial());
			g_pD3DDevice->SetTexture(0, m_vecAseMtlTex[i]->GetTexture());
			m_pAseMesh->DrawSubset(i);
		}

		g_pD3DDevice->SetTexture(0, NULL);
	}
}

void cMainGame::Setup()
{
	m_pCubePC = new cCubePC;
	m_pCubePC->Setup();

	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeMan->GetPosition());
	// &m_pCubePC->GetPosition());

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	{
		
		//m_pRootFrame = l.Load("woman/woman_01_all.ASE");
		
	}

	Setup_Texture();
	Setup_Obj();
	Set_Light();

	Setup_MeshObjects();
}

void cMainGame::Update()
{
	//if (m_pCubePC)
	//	m_pCubePC->Update(); 

	if (m_pCubeMan)
		m_pCubeMan->Update(m_pMap);

	if (m_pCamera)
		m_pCamera->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, nullptr,
	                    D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
	                    D3DCOLOR_XRGB(47, 121, 112),
	                    1.0F, 0);

	g_pD3DDevice->BeginScene();
	if (m_pRootFrame)
		m_pRootFrame->Render();
	
	if (m_pGrid)
		m_pGrid->Render();

	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	Mesh_Render();
	
	//if (m_pCubePC)
	//	m_pCubePC->Render(); 
	//Obj_Render(); 

	//if (m_pCubeMan)
	//	m_pCubeMan->Render(); 

	//Draw_Texture();



	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cMainGame::Set_Light()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);
	stLight.Diffuse = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);
	stLight.Specular = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);

	D3DXVECTOR3 vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
}

void cMainGame::Setup_Texture()
{
	D3DXCreateTextureFromFile(g_pD3DDevice, _T("../image/수지.png"), &m_pTexture);
	ST_PT_VERTEX v;
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 2, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(2, 2, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(v);


	// : 왼쪽에 뒤집어 출력
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-2, 2, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(0, 2, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(v);
}

void cMainGame::Draw_Texture()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX));
	g_pD3DDevice->SetTexture(0, nullptr);
}

void cMainGame::Setup_Obj()
{
	cObjLoader l;
	l.Load(m_vecGroup, "obj", "map.obj");

	Load_Surface();
}

void cMainGame::Obj_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);

	matWorld = matS * matR;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	for each (auto p in m_vecGroup)
	{
		p->Render();
	}
}

void cMainGame::Load_Surface()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
	matWorld = matS * matR;
	m_pMap = new cObjMap("obj", "map_surface.obj", &matWorld);
}
