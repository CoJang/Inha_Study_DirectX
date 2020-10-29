#include "stdafx.h"
#include "cFont.h"

cFont::cFont()
	:m_dColor(D3DCOLOR_ARGB(255, 255, 255, 255))
	,m_dFormat(DT_LEFT | DT_TOP | DT_NOCLIP)
	,m_pFont(NULL)
{
	SetRect(&m_rRect, 0, 0, 100, 100);
}

cFont::~cFont()
{
	SafeRelease(m_pFont);
}

void cFont::Setup(string text, FontType type)
{
	m_sText = text;
	m_pFont = g_pUIManager->GetFont(type);
}

void cFont::Update()
{
}

void cFont::Render()
{
	m_pFont->DrawTextA(NULL,
				m_sText.c_str(),
				m_sText.length(),
					&m_rRect,
					m_dFormat,
					m_dColor);
}

void cFont::ChangeFont(FontType type)
{
	m_pFont = g_pUIManager->GetFont(type);
}
