#include "stdafx.h"
#include "MySprite.h"
#include "UIManager.h"


UIManager::UIManager()
	:m_ptMousePos({ 0, 0 })
	,m_ptOldMousePos({ 0, 0 })
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
		if(PtInRect(&(it.second->GetDrawArea()), m_ptMousePos))
		{
			cout << m_ptMousePos.x << ' ' << m_ptMousePos.y << endl;
			it.second->OnMouseHover();
			IsReact = true;
		}
	}

	return IsReact;
}

LPDIRECT3DTEXTURE9 UIManager::GetTexture(char* path)
{
	if (m_mapTexture.find(path) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileA(DEVICE, path, &m_mapTexture[path]);
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
}
