#include "stdafx.h"
#include "cLight.h"
#include "cCubePC.h"


cLight::cLight()
	:directionalLight(0.0f, 0.0f, 0.0f)
	,vecDir(0.0f, 0.0f, 0.0f)
{
	pointLightRange = 0.0f;

	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	ZeroMemory(&dirLight, sizeof(D3DLIGHT9));
	ZeroMemory(&spotLight, sizeof(D3DLIGHT9));
	ZeroMemory(&pointLight, sizeof(D3DLIGHT9));

}

cLight::~cLight()
{
}

void cLight::Setup()
{
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.7F, 0.7F, 0.7F, 1.0F);
	stLight.Diffuse = D3DXCOLOR(0.7F, 0.7F, 0.7F, 1.0F);
	stLight.Specular = D3DXCOLOR(0.7F, 0.7F, 0.7F, 1.0F);

	D3DXVECTOR3 vDir(1.0f, 1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);

}

void cLight::Update()
{
	D3DXMATRIX tempMat;
	D3DXMatrixRotationZ(&tempMat, 0.005f);
	D3DXVec3TransformCoord(&directionalLight, &directionalLight, &tempMat);
	dirLight.Direction = directionalLight;
	g_pD3DDevice->SetLight(1, &dirLight);
	

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		vecDir.x += 0.01f;
		D3DXVec3Normalize(&vecDir, &vecDir);
		spotLight.Direction = vecDir;
		g_pD3DDevice->SetLight(2, &spotLight);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		vecDir.x -= 0.01f;
		D3DXVec3Normalize(&vecDir, &vecDir);
		spotLight.Direction = vecDir;
		g_pD3DDevice->SetLight(2, &spotLight);
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		vecDir.z -= 0.01f;
		D3DXVec3Normalize(&vecDir, &vecDir);
		spotLight.Direction = vecDir;
		g_pD3DDevice->SetLight(2, &spotLight);
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		vecDir.z += 0.01f;
		D3DXVec3Normalize(&vecDir, &vecDir);
		spotLight.Direction = vecDir;
		g_pD3DDevice->SetLight(2, &spotLight);
	}
	if (GetKeyState(VK_ADD) & 0x8000)
	{
		if (pointLightRange < 8.0f)
		{
			pointLightRange += 0.05f;
			pointLight.Range = pointLightRange;
			g_pD3DDevice->SetLight(3, &pointLight);
		}
	}
	if (GetKeyState(VK_SUBTRACT) & 0x8000)
	{
		if (pointLightRange > 1.2f)
		{
			pointLightRange -= 0.05f;
			pointLight.Range = pointLightRange;
			g_pD3DDevice->SetLight(3, &pointLight);
		}
	}


}

void cLight::Render()
{

}

void cLight::DirectionalLight()
{
	dirLight.Type = D3DLIGHT_DIRECTIONAL;

	dirLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	directionalLight.x = 0.0f;
	directionalLight.y = -100.0f;
	directionalLight.z = 0.0f;

	g_pD3DDevice->SetLight(1, &dirLight);
	g_pD3DDevice->LightEnable(1, TRUE);

}

void cLight::SpotLight()
{
	spotLight.Type = D3DLIGHT_SPOT;
	spotLight.Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	spotLight.Ambient = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	spotLight.Specular = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	spotLight.Attenuation0 = 0.0000001f;
	spotLight.Attenuation1 = 0.0000001f;
	spotLight.Attenuation2 = 0.01f;
	spotLight.Range = 15.0f;
	spotLight.Position.x = 0.0f;
	spotLight.Position.y = 11.0f;
	spotLight.Position.z = 0.0f;

	vecDir.x = 0.0f;
	vecDir.y = -1.0f;
	vecDir.z = 0.0f;

	D3DXVec3Normalize(&vecDir, &vecDir);
	spotLight.Direction = vecDir;
	spotLight.Falloff = 1.0f;
	spotLight.Phi = D3DX_PI / 4.0;
	spotLight.Theta = D3DX_PI / 12.0f;

	g_pD3DDevice->SetLight(2, &spotLight);
	g_pD3DDevice->LightEnable(2, TRUE);

}

void cLight::PointLight()
{
	pointLight.Type = D3DLIGHT_POINT;

	pointLight.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pointLight.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pointLight.Specular = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pointLight.Attenuation0 = 0.0000001f;

	pointLightRange = 2.0f;
	pointLight.Range = pointLightRange;

	pointLight.Position.x = 6;
	pointLight.Position.y = 1;
	pointLight.Position.z = 6;


	g_pD3DDevice->SetLight(3, &pointLight);
	g_pD3DDevice->LightEnable(3, TRUE);

}

/*
ST_PC_VERTEX v;

	float x = spotLight.Position.x;
	float y = spotLight.Position.y;
	float z = spotLight.Position.z;
	float r = 0.5f;

	//front
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-r, r, -r); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r, r, -r); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-r, -r, -r); m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(r, r, -r); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r, -r, -r); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-r, -r, -r); m_vecVertex.push_back(v);

	//back
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-r + x, -r + y, r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r + x, r + y, r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-r + x, r + y, r + z); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-r + x, -r + y, r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r + x, -r + y, r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r + x, r + y, r + z); m_vecVertex.push_back(v);

	//left
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-r + x, -r + y, r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-r + x, r + y, r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-r + x, r + y, -r + z); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-r + x, -r + y, r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-r + x, r + y, -r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-r + x, -r + y, -r + z); m_vecVertex.push_back(v);


	//right
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(r + x, -r + y, -r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r + x, r + y, -r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r + x, r + y, r + z); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(r + x, -r + y, -r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r + x, r + y, r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r + x, -r + y, r + z); m_vecVertex.push_back(v);

	//top
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-r + x, r + y, -r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-r + x, r + y, r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r + x, r + y, r + z); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-r + x, r + y, -r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r + x, r + y, r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r + x, r + y, -r + z); m_vecVertex.push_back(v);

	//bottom
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-r + x, -r + y, r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-r + x, -r + y, -r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r + x, -r + y, -r + z); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-r + x, -r + y, r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r + x, -r + y, -r + z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(r + x, -r + y, r + z); m_vecVertex.push_back(v);
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matR, matT;

	m_Direction = D3DXVECTOR3(x, y, z);
	D3DXVec3TransformNormal(&m_Direction, &m_Direction, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));

*/

