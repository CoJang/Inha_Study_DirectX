#include "framework.h"
#include "cGrid.h"
#include "SceneState.h"

#include "Box.h"

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
	D3DLIGHT9 m_Light;
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
	m_Light.Type = _D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL;
	m_Light.Ambient = D3DXCOLOR(0.7F, 0.7F, 0.7F, 1.0F);
	m_Light.Diffuse = D3DXCOLOR(0.7F, 0.7F, 0.7F, 1.0F);
	m_Light.Specular = D3DXCOLOR(0.7F, 0.7F, 0.7F, 1.0F);
	m_Light.Falloff = 1.0f;
	D3DXVECTOR3 vDir(10.0f, -2.0f, 20.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	m_Light.Direction = vDir;
	m_Light.Position = D3DXVECTOR3(500.00, 500.00, -500.00);

	g_pDevice->SetLight(0, &m_Light);
	g_pDevice->LightEnable(0, true);
	
	m_pGrid = new MyGrid;
	m_pGrid->Init(15, 1.0f);

	m_pBox = new cBox;
	m_pBox->Setup("Asset", "box.obj");
	m_pBox->Update();
}

void SSGame::Update()
{
}

void SSGame::Render()
{
	//m_pGrid->Draw(0);
	m_pBox->Render();
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
