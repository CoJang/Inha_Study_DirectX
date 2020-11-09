#include "framework.h"
#include "cGrid.h"
#include "SceneState.h"

SSLoad::SSLoad()
{
}

SSLoad::~SSLoad()
{
}

void SSLoad::Setup()
{
	D3DXCreateTextureFromFileExA(g_pDevice,
								"Asset/LoadingImage.png",
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
	D3DXCreateSprite(g_pDevice, &m_pSprite);
}

void SSLoad::Update()
{
}

void SSLoad::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(m_pTextureUI,
					&m_rRect,
					&D3DXVECTOR3(0, 0, 0),
					&D3DXVECTOR3(0, 0, 0),
					D3DXCOLOR(1, 1, 1, 1));

	m_pSprite->End();
}

SSGame::SSGame()
{
}

SSGame::~SSGame()
{
}

void SSGame::Setup()
{
	m_pGrid = new MyGrid;
	m_pGrid->Init(15, 1.0f);
}

void SSGame::Update()
{
}

void SSGame::Render()
{
	m_pGrid->Draw(0);
}

SSEnd::SSEnd()
{
}

SSEnd::~SSEnd()
{
}

void SSEnd::Setup()
{
	D3DXCreateTextureFromFileExA(g_pDevice,
								"Asset/GameOver.jpg",
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
	D3DXCreateSprite(g_pDevice, &m_pSprite);
}

void SSEnd::Update()
{
}

void SSEnd::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(m_pTextureUI,
					&m_rRect,
					&D3DXVECTOR3(0, 0, 0),
					&D3DXVECTOR3(0, 0, 0),
					D3DXCOLOR(1, 1, 1, 1));

	m_pSprite->End();
}
