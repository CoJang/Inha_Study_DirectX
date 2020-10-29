#pragma once

class MySprite
{
protected:
	string m_szName;
	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_stImageInfo;
	LPDIRECT3DTEXTURE9 m_pTextureUI;

	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vAnchor;
	D3DXVECTOR3 m_vScale;
	float m_fAngleY;
	float m_fAngleZ;

	D3DCOLOR m_dColor;
	RECT m_rRect;

	vector<MySprite*> m_vecChild;
public:
	MySprite();
	virtual ~MySprite();

	virtual void SetUp(char* szFullPath, char* szUIName);
	virtual void Update(D3DXMATRIXA16* pmatParent);
	virtual void Render();
	virtual void Destroy();

	virtual void AddChild(MySprite* child);
	virtual D3DXIMAGE_INFO GetImageInfo() { return m_stImageInfo; }
	
	virtual void SetScale(float x, float y, float z) { m_vScale = D3DXVECTOR3(x, y, z); }
	virtual void SetScale(D3DXVECTOR3 scale) { m_vScale = scale; }
	virtual D3DXVECTOR3 GetScale() { return m_vScale; }
	
	virtual void SetPos(float x, float y, float z) { m_vPos = D3DXVECTOR3(x, y, 0); }
	virtual void SetPos(D3DXVECTOR3 pos) { m_vPos = pos; }
	virtual D3DXVECTOR3 GetPos() { return m_vPos; }

	virtual void SetAnchor(float x, float y, float z) { m_vAnchor = D3DXVECTOR3(x, y, 0); }
	virtual void SetAnchor(D3DXVECTOR3 anchor) { m_vAnchor = anchor; }
	virtual D3DXVECTOR3 GetSetAnchor() { return m_vAnchor; }
	
	virtual void SetAngleY(float y) { m_fAngleY = y; }
	virtual void SetAngleZ(float z) { m_fAngleZ = z; }
	virtual void SetAngleYZ(float y, float z) { m_fAngleY = y; m_fAngleZ = z; }
	
	virtual float GetAngleY() { return m_fAngleY; }
	virtual float GetAngleZ() { return m_fAngleZ; }
	virtual void  GetAngleYZ(OUT float &y, OUT float &z) { y = m_fAngleY; z = m_fAngleZ; }

	virtual RECT GetDrawArea();
	virtual void SetColor(D3DCOLOR color) { m_dColor = color; }
	virtual void SetDrawArea(int left, int top, int right, int bottom)
	{
		SetRect(&m_rRect, left, top, right, bottom);
	}

	virtual void OnMouseHover();
	virtual void OnMouseClick();
	virtual void OnMouseLeave();
	virtual void OnMouseDrag();

	virtual void ChangeSprite(char* szFullPath);
};

