#include "stdafx.h"
#include "cUIPanel.h"


cUIPanel::cUIPanel()
{
}


cUIPanel::~cUIPanel()
{
}

void cUIPanel::SetUp(char* szFullPath, char* szUIName)
{
	MySprite::SetUp(szFullPath, szUIName);

	MySprite* ConfirmBT = new MySprite;
	ConfirmBT->SetUp("UI/btn-med-up.png", "OK");
	ConfirmBT->SetAnchor(ConfirmBT->GetImageInfo().Width * 0.5f, 0, 0);
	ConfirmBT->SetPos(m_stImageInfo.Width * 0.5f, m_stImageInfo.Height * 0.6f, 0);
	AddChild(ConfirmBT);

	MySprite* CancleBT = new MySprite;
	CancleBT->SetUp("UI/btn-med-up.png", "NO");
	CancleBT->SetAnchor(ConfirmBT->GetImageInfo().Width * 0.5f, 0, 0);
	CancleBT->SetPos(m_stImageInfo.Width * 0.5f, m_stImageInfo.Height * 0.72f, 0);
	AddChild(CancleBT);
}

void cUIPanel::Update(D3DXMATRIXA16* pmatParent)
{
	MySprite::Update(pmatParent);
}

void cUIPanel::OnMouseClick()
{
}

void cUIPanel::OnMouseHover()
{
	int DistanceX = g_pUIManager->m_ptOldMousePos.x - g_pUIManager->m_ptMousePos.x;
	int DistanceY = g_pUIManager->m_ptOldMousePos.y - g_pUIManager->m_ptMousePos.y;
	
	m_vPos.x -= DistanceX;
	m_vPos.y -= DistanceY;

	//printf("Distance (%d, %d)\n", DistanceX, DistanceY);
}

void cUIPanel::OnMouseLeave()
{
}
