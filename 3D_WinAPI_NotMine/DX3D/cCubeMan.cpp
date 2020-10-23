#include "stdafx.h"

#include "cBody.h"
#include "cHead.h"
#include "cLeftArm.h"
#include "cRightArm.h"
#include "cLeftLeg.h"
#include "cRightLeg.h"

#include "cCubeMan.h"

cCubeMan::cCubeMan()
	:m_pRoot(NULL)
{
}

cCubeMan::~cCubeMan()
{
	if (m_pRoot)
		m_pRoot->Destroy();
}

void cCubeMan::Setup()
{
	cCharacter::Setup();

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);	//주변 반영
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);	//분산 반영
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);	//반사 반영
	//m_stMtl.Emissive = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);	//방출
	//m_stMtl.Power 에서 설정한 값은 반사효과가 얼마나 예리한지 제어한다

	cBody* pBody = new cBody;
	pBody->Setup();
	pBody->SetParentWorldTM(&m_matWorld);
	m_pRoot = pBody;

	cHead* pHead = new cHead;
	pHead->Setup();
	m_pRoot->Addchild(pHead);

	cLeftArm* pLArm = new cLeftArm;
	pLArm->Setup();
	pLArm->SetRotDeltaX(0.1f);
	m_pRoot->Addchild(pLArm);

	cRightArm* pRArm = new cRightArm;
	pRArm->Setup();
	pRArm->SetRotDeltaX(-0.1f);
	m_pRoot->Addchild(pRArm);

	cLeftLeg* pLLeg = new cLeftLeg;
	pLLeg->Setup();
	pLLeg->SetRotDeltaX(-0.1f);
	m_pRoot->Addchild(pLLeg);

	cRightLeg* pRLeg = new cRightLeg;
	pRLeg->Setup();
	pRLeg->SetRotDeltaX(0.1f);
	m_pRoot->Addchild(pRLeg);
}

void cCubeMan::Update(iMap* pMap)
{
	cCharacter::Update(pMap);
	if (m_pRoot)
		m_pRoot->Update();
}

void cCubeMan::Render()
{

	if (g_pD3DDevice) 
	{
		g_pD3DDevice->SetTexture(0, m_pTexture);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetMaterial(&m_stMtl);

		cCharacter::Render();

		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		if (m_pRoot)
			m_pRoot->Render();
		g_pD3DDevice->SetTexture(0, NULL);
	}
}