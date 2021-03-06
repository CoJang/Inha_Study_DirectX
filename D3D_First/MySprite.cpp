#include "stdafx.h"
#include "cFont.h"
#include "MySprite.h"


MySprite::MySprite()
	:m_vPos(0, 0, 0)
	, m_vScale(1, 1, 1)
	, m_vAnchor(0, 0, 0)
	, m_fAngleY(0.0f)
	, m_fAngleZ(0.0f)
	, m_pSprite(NULL)
	, m_pTextureUI(NULL)
	, m_dColor(D3DCOLOR_ARGB(255, 255, 255, 255))
	, m_szName("Unknown")
	, m_pFont(NULL)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	SetRect(&m_rRect, 0, 0, 100, 100);
}


MySprite::~MySprite()
{
	Destroy();
}

void MySprite::Destroy()
{
	SafeRelease(m_pSprite);

	for (auto Child : m_vecChild)
		Child->Destroy();
}

void MySprite::AddChild(MySprite* child)
{
	m_vecChild.push_back(child);
}

RECT MySprite::GetDrawArea()
{
	RECT CurrentArea;
	SetRect(&CurrentArea, matWorld._41 - m_vAnchor.x,
						 matWorld._42 - m_vAnchor.y,
						 matWorld._41 + m_stImageInfo.Width - m_vAnchor.x,
						 matWorld._42 + m_stImageInfo.Height - m_vAnchor.y);

	return CurrentArea;
}

void MySprite::ChangeSprite(char* szFullPath)
{
	if (!g_pUIManager->GetTexture(szFullPath))
	{
		LoadTexture(szFullPath);
	}

	m_pTextureUI = g_pUIManager->GetTexture(szFullPath);
	m_stImageInfo = g_pUIManager->GetImageInfo(szFullPath);
}

void MySprite::SetText(char* text)
{
	if (m_pFont) 
		m_pFont->SetText(text);
}

void MySprite::SetText(string & text)
{
	if (m_pFont) 
		m_pFont->SetText(text);
}

void MySprite::SetUp(char* szFullPath, char* szUIName)
{
	if(g_pUIManager->GetSprite(szUIName))
	{
		memcpy(this, g_pUIManager->GetSprite(szUIName), sizeof(MySprite));
		return;
	}
	
	D3DXCreateSprite(DEVICE, &m_pSprite);

	if(g_pUIManager->GetTexture(szFullPath))
	{
		m_pTextureUI = g_pUIManager->GetTexture(szFullPath);
		m_stImageInfo = g_pUIManager->GetImageInfo(szFullPath);
		SetRect(&m_rRect, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);

		m_szName = szUIName;
		g_pUIManager->AddSprite(m_szName, this);
		Update(NULL);
		return;
	}
	
	LoadTexture(szFullPath);

	m_szName = szUIName;
	g_pUIManager->AddSprite(m_szName, this);
	Update(NULL);
}

void MySprite::LoadTexture(char* szFullPath)
{
	D3DXCreateTextureFromFileExA(DEVICE,
								szFullPath,
								D3DX_DEFAULT_NONPOW2,
								D3DX_DEFAULT_NONPOW2,
								D3DX_DEFAULT,
								0,
								D3DFMT_UNKNOWN,
								D3DPOOL_MANAGED,
								D3DX_FILTER_NONE,
								D3DX_DEFAULT,
								0,
								&m_stImageInfo,
								NULL,
								&m_pTextureUI);
	
	SetRect(&m_rRect, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);
	g_pUIManager->AddTexture(szFullPath, m_pTextureUI);
	g_pUIManager->AddImageInfo(szFullPath, m_stImageInfo);
}

void MySprite::Update(D3DXMATRIXA16* pmatParent)
{
	D3DXMATRIXA16 matYR, matZR;
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, 0);
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationY(&matYR, m_fAngleY);
	D3DXMatrixRotationZ(&matZR, m_fAngleZ);
	
	matR = matYR * matZR;
	matWorld = matS * matR * matT;
	
	if(pmatParent)
	{
		matWorld *= *pmatParent;
	}

	if (m_pFont)
		m_pFont->SetDrawArea(GetDrawArea());

	for (auto Child : m_vecChild)
		Child->Update(&matWorld);
}

void MySprite::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(m_pTextureUI,
					&m_rRect,
					&m_vAnchor,
					&D3DXVECTOR3(0, 0, 0),
					m_dColor);

	m_pSprite->End();
	
	if (m_pFont)
		m_pFont->Render();

	for (auto Child : m_vecChild)
		Child->Render();
}


