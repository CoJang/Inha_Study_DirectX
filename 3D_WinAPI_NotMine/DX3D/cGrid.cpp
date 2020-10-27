#include "stdafx.h"
#include "cGrid.h"
#include "cPyramid.h"


cGrid::cGrid()
{
}


cGrid::~cGrid()
{
	for each(auto p in m_vecPyramid)
	{
		SafeDelete(p);
	}

	m_vecPyramid.clear();
}

void cGrid::Setup(int nNumHarfTile, float fInterval)
{

	float fMax = nNumHarfTile * fInterval;
	float fMin = -fMax;
	ST_PC_VERTEX v;
	
	for (int i = 1; i <= nNumHarfTile; ++i) 
	{
		if (i % 5 == 0)
			v.c = D3DCOLOR_XRGB(255, 255, 255);
		else
			v.c = D3DCOLOR_XRGB(128, 128, 128);

		/*
		//가로
		v.p = D3DXVECTOR3(fMin, 0, i*fInterval);
		m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i*fInterval);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i*fInterval);
		m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i*fInterval);
		m_vecVertex.push_back(v);

		//세로
		v.p = D3DXVECTOR3(i*fInterval, 0, fMin);
		m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(i*fInterval, 0, fMax);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i*fInterval, 0, fMin);
		m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i*fInterval, 0, fMax);
		m_vecVertex.push_back(v);
		*/
		
	}

	for (int j = -15; j < 15; j++) 
	{
		for (int i = -15; i < 15; i++)
		{
			v.c = D3DCOLOR_XRGB(128, 128, 128);
			v.p = D3DXVECTOR3(j+1, 0, i);
			v.n = D3DXVECTOR3(0, 1, 0);
			m_vecVertex.push_back(v);

			v.p = D3DXVECTOR3(j, 0, i); 
			v.n = D3DXVECTOR3(0, 1, 0);
			m_vecVertex.push_back(v);

			v.p = D3DXVECTOR3(j, 0, i + 1); 
			v.n = D3DXVECTOR3(0, 1, 0);
			m_vecVertex.push_back(v);

			v.p = D3DXVECTOR3(j+1, 0, i);
			v.n = D3DXVECTOR3(0, 1, 0); 
			m_vecVertex.push_back(v);

			v.p = D3DXVECTOR3(j, 0, i + 1);
			v.n = D3DXVECTOR3(0, 1, 0); 
			m_vecVertex.push_back(v);

			v.p = D3DXVECTOR3(j+1, 0, i + 1);
			v.n = D3DXVECTOR3(0, 1, 0);
			m_vecVertex.push_back(v);

			
		}
	}

	/*
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(fMin, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, fMin, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, fMax, 0); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0, 0, fMin); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax); m_vecVertex.push_back(v);
	*/


	

	
	cPyramid* pPyramid = NULL;
	D3DXMATRIXA16 matR;

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(255, 0, 0), matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	pPyramid->Setup(D3DCOLOR_XRGB(0, 255, 0), matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(0, 0, 255), matR);
	m_vecPyramid.push_back(pPyramid);
	

	ZeroMemory(&m_matrial, sizeof(D3DMATERIAL9));
	m_matrial.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.5f, 1.0f);
	m_matrial.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.5f, 1.0f);
	m_matrial.Specular = D3DXCOLOR(0.0f, 0.0f, 0.5f, 1.0f);
}

void cGrid::Render()
{
	g_pD3DDevice->SetMaterial(&m_matrial);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecVertex.size() / 2, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
	
	for each (auto p in m_vecPyramid)
		p->Render();
	
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

}