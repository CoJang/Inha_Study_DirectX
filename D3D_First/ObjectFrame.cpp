#include "stdafx.h"
#include "ObjectFrame.h"

ObjectFrame::ObjectFrame()
	: m_pMtlTex(nullptr)
	, m_pVB(nullptr)
	, m_nNumTri(0)
{
	D3DXMatrixIdentity(&LocalTM);
	D3DXMatrixIdentity(&WorldTM);
}

ObjectFrame::~ObjectFrame()
{
	SafeRelease(m_pMtlTex);
	SafeRelease(m_pVB);
}

void ObjectFrame::Update(int KeyFrame, D3DXMATRIXA16* pmatParent)
{
	D3DXMATRIXA16 matR, matT;
	CalcLocalR(KeyFrame, matR);
	CalcLocalT(KeyFrame, matT);
	LocalTM = matR * matT;
	
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
		DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3,	&m_vecVertex[0], sizeof(PNT_VERTEX));
		//DEVICE->SetStreamSource(0, m_pVB, 0, sizeof(PNT_VERTEX));
		//DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nNumTri);//m_nNumTri 삼각형을 몇개를 그릴 것이냐로 넣는다
	}
	
	for each (auto c in m_vecChild)
	{
		c->Render();
	}
	
	DEVICE->SetTexture(0, NULL);
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

void ObjectFrame::CalcLocalT(int nKeyFrame, D3DXMATRIXA16& matT)
{
	D3DXMatrixIdentity(&matT);
	if (m_vecPosTrack.empty())
	{
		matT._41 = LocalTM._41;//3행에 있는 것들이 위치값이다
		matT._42 = LocalTM._42;
		matT._43 = LocalTM._43;
		return;
	}

	if (nKeyFrame <= m_vecPosTrack.front().n)
	{
		matT._41 = m_vecPosTrack.front().v.x;
		matT._42 = m_vecPosTrack.front().v.y;
		matT._43 = m_vecPosTrack.front().v.z;
		return;
	}

	if (nKeyFrame >= m_vecPosTrack.back().n)
	{
		matT._41 = m_vecPosTrack.back().v.x;
		matT._42 = m_vecPosTrack.back().v.y;
		matT._43 = m_vecPosTrack.back().v.z;
		return;
	}

	int nNextIndex = 0;
	for (size_t i = 0; i < m_vecPosTrack.size(); ++i)
	{
		if (nKeyFrame < m_vecPosTrack[i].n)
		{
			nNextIndex = i;
			break;
		}
	}
	//위치는 선형으로 해도 된다.
	//회전은 선형으로 하면 안된다. ex> 다리를 보면 사이에 다리가 짧아진다.

	int nPrevIndex = nNextIndex - 1;

	float t = (nKeyFrame - m_vecPosTrack[nPrevIndex].n) / (float)(m_vecPosTrack[nNextIndex].n - m_vecPosTrack[nPrevIndex].n);

	D3DXVECTOR3 v;
	D3DXVec3Lerp(&v, &m_vecPosTrack[nPrevIndex].v, &m_vecPosTrack[nNextIndex].v, t);

	matT._41 = v.x;
	matT._42 = v.y;
	matT._43 = v.z;
}

void ObjectFrame::CalcLocalR(int nKeyFrame, D3DXMATRIXA16& matR)
{
	D3DXMatrixIdentity(&matR);
	if (m_vecRotTrack.empty())
	{
		matR = LocalTM;
		matR._41 = 0.0f;
		matR._42 = 0.0f;
		matR._43 = 0.0f;
		return;
	}

	if (nKeyFrame <= m_vecRotTrack.front().n)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.front().q);
		return;
	}
	if (nKeyFrame >= m_vecRotTrack.back().n)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.back().q);
		return;
	}

	int nNextIndex = 0;
	for (size_t i = 0; i < m_vecRotTrack.size(); ++i)
	{
		if (nKeyFrame < m_vecRotTrack[i].n)
		{
			nNextIndex = i;
			break;
		}
	}
	int nPrevIndex = nNextIndex - 1;

	float t = (nKeyFrame - m_vecRotTrack[nPrevIndex].n) / (float)(m_vecRotTrack[nNextIndex].n - m_vecRotTrack[nPrevIndex].n);

	D3DXQUATERNION q;
	D3DXQuaternionSlerp(&q, &m_vecRotTrack[nPrevIndex].q, &m_vecRotTrack[nNextIndex].q, t);	//구형보간
	D3DXMatrixRotationQuaternion(&matR, &q);
}

int ObjectFrame::GetKeyFrame()
{
	int first = m_dwFirstFrame * m_dwTicksPerFrame;
	int last = m_dwLastFrame * m_dwTicksPerFrame;

	return GetTickCount() % (last - first) + first;
}

void ObjectFrame::BuildVB(vector<PNT_VERTEX>& vecVertex)
{
	m_nNumTri = vecVertex.size() / 3;
	DEVICE->CreateVertexBuffer(vecVertex.size() * sizeof(PNT_VERTEX), 0, PNT_VERTEX::FVF, D3DPOOL_MANAGED, &m_pVB, NULL);
	PNT_VERTEX* pV = NULL;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);	//락을 건다
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(PNT_VERTEX));	//연속된 데이터라는 증거가 있어야 카피 가능
	m_pVB->Unlock();
}
