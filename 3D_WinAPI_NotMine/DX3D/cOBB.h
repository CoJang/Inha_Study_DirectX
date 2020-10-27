#pragma once

class cSkinnedMesh;

class cOBB
{
public:
	cOBB();
	~cOBB();

private:	
	D3DXVECTOR3 m_vOriCenter;
	D3DXVECTOR3 m_vOriAxisDir[3];

	D3DXVECTOR3 m_vCenterPos;
	D3DXVECTOR3 m_vAxisDir[3];
	float		m_fAxisLen[3];

	float		m_fAxisHalfLen[3];

	D3DXMATRIXA16 m_matWorldTM;

public:
	void SetUp(cSkinnedMesh* pSkinnedMesh);
	void Update(D3DXMATRIXA16* pmatWorld);
	static bool IsCollision(cOBB* pOBB1, cOBB* pOBB2);
	void OBBBOX_Render(D3DCOLOR c);
};

