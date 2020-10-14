#include "stdafx.h"
#include "cLeftArm.h"


cLeftArm::cLeftArm()
{
}


cLeftArm::~cLeftArm()
{
}

void cLeftArm::Setup()
{
	cCubeNode::Setup();
	{
		m_vecVertex[0].t.x = static_cast<float>(44) / 64;
		m_vecVertex[0].t.y = static_cast<float>(32) / 32;
		m_vecVertex[1].t.x = static_cast<float>(44) / 64;
		m_vecVertex[1].t.y = static_cast<float>(20) / 32;
		m_vecVertex[2].t.x = static_cast<float>(48) / 64;
		m_vecVertex[2].t.y = static_cast<float>(20) / 32;

		m_vecVertex[3].t.x = static_cast<float>(44) / 64;
		m_vecVertex[3].t.y = static_cast<float>(32) / 32;
		m_vecVertex[4].t.x = static_cast<float>(48) / 64;
		m_vecVertex[4].t.y = static_cast<float>(20) / 32;
		m_vecVertex[5].t.x = static_cast<float>(48) / 64;
		m_vecVertex[5].t.y = static_cast<float>(32) / 32;

		m_vecVertex[6].t.x = static_cast<float>(56) / 64;
		m_vecVertex[6].t.y = static_cast<float>(32) / 32;
		m_vecVertex[7].t.x = static_cast<float>(52) / 64;
		m_vecVertex[7].t.y = static_cast<float>(20) / 32;
		m_vecVertex[8].t.x = static_cast<float>(56) / 64;
		m_vecVertex[8].t.y = static_cast<float>(20) / 32;

		m_vecVertex[9].t.x = static_cast<float>(56) / 64;
		m_vecVertex[9].t.y = static_cast<float>(32) / 32;
		m_vecVertex[10].t.x = static_cast<float>(52) / 64;
		m_vecVertex[10].t.y = static_cast<float>(32) / 32;
		m_vecVertex[11].t.x = static_cast<float>(52) / 64;
		m_vecVertex[11].t.y = static_cast<float>(20) / 32;

		m_vecVertex[12].t.x = static_cast<float>(40) / 64;
		m_vecVertex[12].t.y = static_cast<float>(32) / 32;
		m_vecVertex[13].t.x = static_cast<float>(40) / 64;
		m_vecVertex[13].t.y = static_cast<float>(20) / 32;
		m_vecVertex[14].t.x = static_cast<float>(44) / 64;
		m_vecVertex[14].t.y = static_cast<float>(20) / 32;

		m_vecVertex[15].t.x = static_cast<float>(40) / 64;
		m_vecVertex[15].t.y = static_cast<float>(32) / 32;
		m_vecVertex[16].t.x = static_cast<float>(44) / 64;
		m_vecVertex[16].t.y = static_cast<float>(20) / 32;
		m_vecVertex[17].t.x = static_cast<float>(44) / 64;
		m_vecVertex[17].t.y = static_cast<float>(32) / 32;

		m_vecVertex[18].t.x = static_cast<float>(48) / 64;
		m_vecVertex[18].t.y = static_cast<float>(32) / 32;
		m_vecVertex[19].t.x = static_cast<float>(48) / 64;
		m_vecVertex[19].t.y = static_cast<float>(20) / 32;
		m_vecVertex[20].t.x = static_cast<float>(52) / 64;
		m_vecVertex[20].t.y = static_cast<float>(20) / 32;

		m_vecVertex[21].t.x = static_cast<float>(48) / 64;
		m_vecVertex[21].t.y = static_cast<float>(32) / 32;
		m_vecVertex[22].t.x = static_cast<float>(52) / 64;
		m_vecVertex[22].t.y = static_cast<float>(20) / 32;
		m_vecVertex[23].t.x = static_cast<float>(52) / 64;
		m_vecVertex[23].t.y = static_cast<float>(32) / 32;

		m_vecVertex[24].t.x = static_cast<float>(44) / 64;
		m_vecVertex[24].t.y = static_cast<float>(20) / 32;
		m_vecVertex[25].t.x = static_cast<float>(44) / 64;
		m_vecVertex[25].t.y = static_cast<float>(16) / 32;
		m_vecVertex[26].t.x = static_cast<float>(48) / 64;
		m_vecVertex[26].t.y = static_cast<float>(16) / 32;

		m_vecVertex[27].t.x = static_cast<float>(44) / 64;
		m_vecVertex[27].t.y = static_cast<float>(20) / 32;
		m_vecVertex[28].t.x = static_cast<float>(48) / 64;
		m_vecVertex[28].t.y = static_cast<float>(16) / 32;
		m_vecVertex[29].t.x = static_cast<float>(48) / 64;
		m_vecVertex[29].t.y = static_cast<float>(20) / 32;

		m_vecVertex[30].t.x = static_cast<float>(48) / 64;
		m_vecVertex[30].t.y = static_cast<float>(16) / 32;
		m_vecVertex[31].t.x = static_cast<float>(48) / 64;
		m_vecVertex[31].t.y = static_cast<float>(20) / 32;
		m_vecVertex[32].t.x = static_cast<float>(52) / 64;
		m_vecVertex[32].t.y = static_cast<float>(20) / 32;

		m_vecVertex[33].t.x = static_cast<float>(48) / 64;
		m_vecVertex[33].t.y = static_cast<float>(16) / 32;
		m_vecVertex[34].t.x = static_cast<float>(52) / 64;
		m_vecVertex[34].t.y = static_cast<float>(20) / 32;
		m_vecVertex[35].t.x = static_cast<float>(52) / 64;
		m_vecVertex[35].t.y = static_cast<float>(16) / 32;
	}

	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.2f, 0.6f, 0.2f);
	D3DXMatrixTranslation(&matT, -0.3f, -0.3f, 0.0f);
	mat = matS * matT;
	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat);
	}

	m_vLocalPos.y = 0.3f;
}
