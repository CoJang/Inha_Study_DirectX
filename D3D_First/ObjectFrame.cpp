#include "stdafx.h"
#include "ObjectFrame.h"

ObjectFrame::ObjectFrame()
	:m_pMtlTex(nullptr)
{
	D3DXMatrixIdentity(&LocalTM);
	D3DXMatrixIdentity(&WorldTM);
}

ObjectFrame::~ObjectFrame()
{
	SafeRelease(m_pMtlTex);
}

void ObjectFrame::Update(int KeyFrame, D3DXMATRIXA16* pmatParent)
{
	WorldTM = LocalTM;
	if (pmatParent)
	{
		WorldTM *= (*pmatParent);
	}
	
	for each (auto c in m_vecChild)
	{
		c->Update(KeyFrame, &WorldTM);
	}
}

void ObjectFrame::Render()
{
	if (m_pMtlTex)
	{
		DEVICE->SetTransform(D3DTS_WORLD, &WorldTM);
		DEVICE->SetTexture(0, m_pMtlTex->GetTexture());
		DEVICE->SetMaterial(&m_pMtlTex->GetMaterial());

		DEVICE->SetFVF(PNT_VERTEX::FVF);
		DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
								m_vecVertex.size() / 3,
								&m_vecVertex[0], sizeof(PNT_VERTEX));
	}
	
	for each (auto c in m_vecChild)
	{
		c->Render();
	}
}

void ObjectFrame::AddChild(ObjectFrame* pChild)
{
	m_vecChild.push_back(pChild);
}

void ObjectFrame::Destroy()
{
	for each (auto c in m_vecChild)
		c->Destroy();

	this->Release();
}

void ObjectFrame::CalcOriginLocalTM(D3DXMATRIXA16* pmatParent)
{
	LocalTM = WorldTM;
	if (pmatParent)
	{
		D3DXMATRIXA16 matInvParent;
		D3DXMatrixInverse(&matInvParent, nullptr, pmatParent);
		LocalTM = WorldTM * matInvParent;
	}
	for each (auto c in m_vecChild)
		c->CalcOriginLocalTM(&WorldTM);
}
