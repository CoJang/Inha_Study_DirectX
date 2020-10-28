#include "stdafx.h"
#include "cFontManager.h"


cFontManager::cFontManager()
{
}


cFontManager::~cFontManager()
{
}

LPD3DXFONT cFontManager::GetFont(eFontType e)
{
	if(m_mapFont.find(e) != m_mapFont.end())
	{
		return m_mapFont[e];
	}

	D3DXFONT_DESC FD;
	ZeroMemory(&FD, sizeof(D3DXFONT_DESC));

	if(e == E_DEFAULT)
	{
		FD.Width = 12;
		FD.Height = 25;
		FD.Weight = FW_BOLD;
		FD.Italic = false;
		FD.CharSet = DEFAULT_CHARSET;
		FD.OutputPrecision = OUT_DEFAULT_PRECIS;
		FD.PitchAndFamily = FF_DONTCARE;

		wcscpy_s(FD.FaceName, L"±¼¸²Ã¼");
	}
	else if(e == E_QUEST)
	{
		FD.Width = 12;
		FD.Height = 25;
		FD.Weight = FW_MEDIUM;
		FD.Italic = false;
		FD.CharSet = DEFAULT_CHARSET;
		FD.OutputPrecision = OUT_DEFAULT_PRECIS;
		FD.PitchAndFamily = FF_DONTCARE;

		AddFontResource(TEXT("font/umberto.ttf"));
		wcscpy_s(FD.FaceName, L"umberto");
	}
	
	D3DXCreateFontIndirect(g_pD3DDevice, &FD, &m_mapFont[e]);
	return m_mapFont[e];
}

void cFontManager::Destroy()
{
	for(auto it : m_mapFont)
	{
		SafeRelease(it.second);
	}
}
