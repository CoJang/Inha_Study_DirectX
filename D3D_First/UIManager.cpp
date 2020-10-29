#include "stdafx.h"
#include "MySprite.h"
#include "UIManager.h"


UIManager::UIManager()
	:m_ptMousePos({ 0, 0 })
	,m_ptOldMousePos({ 0, 0 })
	,m_stMouseState(MS_NORMAL)
{
}


UIManager::~UIManager()
{
}

bool UIManager::Update()
{
	bool IsReact = false;
	for (auto it : m_mapSprite)
	{
		if (PtInRect(&(it.second->GetDrawArea()), m_ptMousePos) && m_stMouseState == MS_NORMAL)
		{
			it.second->OnMouseHover();
		}
		if(PtInRect(&(it.second->GetDrawArea()), m_ptMousePos) && m_stMouseState == MS_DRAG)
		{
			it.second->OnMouseDrag();
			IsReact = true;
		}
		if (PtInRect(&(it.second->GetDrawArea()), m_ptMousePos) && m_stMouseState == MS_LCLICK)
		{
			it.second->OnMouseClick();
			IsReact = true;
		}
		
		if(!PtInRect(&(it.second->GetDrawArea()), m_ptMousePos) && !IsReact)
		{
			it.second->OnMouseLeave();
		}
	}

	return IsReact;
}

void UIManager::AddImageInfo(char* path, D3DXIMAGE_INFO info)
{
	if (m_mapImageInfo.find(path) == m_mapImageInfo.end())
		m_mapImageInfo[path] = info;
}

void UIManager::AddImageInfo(string& path, D3DXIMAGE_INFO info)
{
	return AddImageInfo((char*)path.c_str(), info);
}

D3DXIMAGE_INFO UIManager::GetImageInfo(char* path)
{
	if (m_mapImageInfo.find(path) == m_mapImageInfo.end())
	{
		return D3DXIMAGE_INFO();
	}

	return m_mapImageInfo[path];
}

D3DXIMAGE_INFO UIManager::GetImageInfo(string& path)
{
	return GetImageInfo((char*)path.c_str());
}

void UIManager::AddTexture(char* path, LPDIRECT3DTEXTURE9 texture)
{
	if (m_mapTexture.find(path) == m_mapTexture.end())
		m_mapTexture[path] = texture;
}

void UIManager::AddTexture(string& path, LPDIRECT3DTEXTURE9 texture)
{
	return AddTexture((char*)path.c_str(), texture);
}

LPDIRECT3DTEXTURE9 UIManager::GetTexture(char* path)
{
	if (m_mapTexture.find(path) == m_mapTexture.end())
	{
		return NULL;
	}

	return m_mapTexture[path];
}

LPDIRECT3DTEXTURE9 UIManager::GetTexture(string& path)
{
	return GetTexture((char*)path.c_str());
}

void UIManager::AddSprite(char* Name, MySprite* sprite)
{
	if(m_mapSprite.find(Name) == m_mapSprite.end())
		m_mapSprite[Name] = sprite;
}

void UIManager::AddSprite(string& Name, MySprite* sprite)
{
	return AddSprite((char*)Name.c_str(), sprite);
}

MySprite* UIManager::GetSprite(char* Name)
{
	if (m_mapSprite.find(Name) == m_mapSprite.end())
	{
		return NULL;
	}

	return m_mapSprite[Name];
}

MySprite* UIManager::GetSprite(string & Name)
{
	return GetSprite((char*)Name.c_str());
}

LPD3DXFONT UIManager::GetFont(FontType type)
{
	if (m_mapFont.find(type) != m_mapFont.end())
	{
		return m_mapFont[type];
	}

	D3DXFONT_DESC FD;
	ZeroMemory(&FD, sizeof(D3DXFONT_DESC));

	if (type == FONT_DEFAULT)
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
	else if (type == FONT_WARNING)
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

	D3DXCreateFontIndirect(DEVICE, &FD, &m_mapFont[type]);
	return m_mapFont[type];
}

void UIManager::Destroy()
{
	for (auto it : m_mapTexture)
	{
		SafeRelease(it.second);
	}

	m_mapTexture.clear();

	for (auto it : m_mapSprite)
	{
		it.second->Destroy();
	}

	m_mapSprite.clear();

	for (auto it : m_mapFont)
	{
		SafeRelease(it.second);
	}

	m_mapFont.clear();

	
}
