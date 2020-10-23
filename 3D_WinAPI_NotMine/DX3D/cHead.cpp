#include "stdafx.h"
#include "cHead.h"

cHead::cHead()
{
}

cHead::~cHead()
{
}

void cHead::Setup()
{
	cCubeNode::Setup();
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);
	mat = matS * matT;
	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat);
	}

	m_vLocalPos.y = 0.5f;



	float left = 0.0f / 64.0f;
	float top = 0.0f / 64.0f;

	float width = 8.0f / 64.0f;
	float deep = 8.0f / 64.0f;
	float high = 8.0f / 64.0f;

	//앞
	m_vecVertex[0].t.x = left + deep;					m_vecVertex[0].t.y = top + deep + high;
	m_vecVertex[1].t.x = left + deep;					m_vecVertex[1].t.y = top + deep;
	m_vecVertex[2].t.x = left + deep + width;			m_vecVertex[2].t.y = top + deep;

	m_vecVertex[3].t.x = left + deep;					m_vecVertex[3].t.y = top + deep + high;
	m_vecVertex[4].t.x = left + deep + width;			m_vecVertex[4].t.y = top + deep;
	m_vecVertex[5].t.x = left + deep + width;			m_vecVertex[5].t.y = top + deep + high;
	//뒤
	m_vecVertex[6].t.x = left + 2 * deep + 2 * width;	m_vecVertex[6].t.y = top + deep + high;
	m_vecVertex[7].t.x = left + 2 * deep + width;		m_vecVertex[7].t.y = top + deep;
	m_vecVertex[8].t.x = left + 2 * deep + 2 * width;	m_vecVertex[8].t.y = top + deep;

	m_vecVertex[9].t.x = left + 2 * deep + 2 * width;   m_vecVertex[9].t.y = top + deep + high;
	m_vecVertex[10].t.x = left + 2 * deep + width;		m_vecVertex[10].t.y = top + deep + high;
	m_vecVertex[11].t.x = left + 2 * deep + width;		m_vecVertex[11].t.y = top + deep;
	//왼
	m_vecVertex[12].t.x = left;							m_vecVertex[12].t.y = top + deep + high;
	m_vecVertex[13].t.x = left;							m_vecVertex[13].t.y = top + deep;
	m_vecVertex[14].t.x = left + deep;					m_vecVertex[14].t.y = top + deep;

	m_vecVertex[15].t.x = left;							m_vecVertex[15].t.y = top + deep + high;
	m_vecVertex[16].t.x = left + deep;					m_vecVertex[16].t.y = top + deep;
	m_vecVertex[17].t.x = left + deep;					m_vecVertex[17].t.y = top + deep + high;
	//오
	m_vecVertex[18].t.x = left + deep + width;			m_vecVertex[18].t.y = top + deep + high;
	m_vecVertex[19].t.x = left + deep + width;			m_vecVertex[19].t.y = top + deep;
	m_vecVertex[20].t.x = left + 2 * deep + width;		m_vecVertex[20].t.y = top + deep;

	m_vecVertex[21].t.x = left + deep + width;			m_vecVertex[21].t.y = top + deep + high;
	m_vecVertex[22].t.x = left + 2 * deep + width;		m_vecVertex[22].t.y = top + deep;
	m_vecVertex[23].t.x = left + 2 * deep + width;		m_vecVertex[23].t.y = top + deep + high;
	//위
	m_vecVertex[24].t.x = left + deep;					m_vecVertex[24].t.y = top + deep;
	m_vecVertex[25].t.x = left + deep;					m_vecVertex[25].t.y = top;
	m_vecVertex[26].t.x = left + deep + width;			m_vecVertex[26].t.y = top;

	m_vecVertex[27].t.x = left + deep;					m_vecVertex[27].t.y = top + deep;
	m_vecVertex[28].t.x = left + deep + width;			m_vecVertex[28].t.y = top;
	m_vecVertex[29].t.x = left + deep + width;			m_vecVertex[29].t.y = top + deep;
	//아래
	m_vecVertex[30].t.x = left + deep + 2 * width;		m_vecVertex[30].t.y = top;
	m_vecVertex[31].t.x = left + deep + 2 * width;		m_vecVertex[31].t.y = top + deep;
	m_vecVertex[32].t.x = left + deep + width;			m_vecVertex[32].t.y = top + deep;

	m_vecVertex[33].t.x = left + deep + width;			m_vecVertex[33].t.y = top;
	m_vecVertex[34].t.x = left + deep + 2 * width;		m_vecVertex[34].t.y = top + deep;
	m_vecVertex[35].t.x = left + deep + 2 * width;		m_vecVertex[35].t.y = top;

}
