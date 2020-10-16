#include "stdafx.h"
#include "cMtlTex.h"


cMtlTex::cMtlTex()
	: m_pTexture(nullptr)
	, m_nAttrID(0)
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
}


cMtlTex::~cMtlTex()
{
	SafeRelease(m_pTexture);
}
