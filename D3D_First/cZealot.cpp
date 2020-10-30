#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cZealot.h"


cZealot::cZealot()
	: m_pSkinnedMesh(NULL)
{
}


cZealot::~cZealot()
{
	SafeDelete(m_pSkinnedMesh);
}

void cZealot::Setup()
{
	m_pSkinnedMesh = new cSkinnedMesh("Zealot", "zealot.X");
	m_pSkinnedMesh->SetRandomTrackPosition();
}

void cZealot::Update()
{
}

void cZealot::Render(D3DCOLOR c)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIsIdentity(&matWorld);
	D3DXMatrixScaling(&matWorld, 3, 3, 3);
	m_pSkinnedMesh->SetTransform(&matWorld);

	m_pSkinnedMesh->UpdateAndRender();
}
