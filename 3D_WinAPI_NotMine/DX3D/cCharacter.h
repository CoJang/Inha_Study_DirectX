#pragma once
class cCharacter : public cObject
{
protected:
	float m_fRotY;
	D3DXVECTOR3 m_vDirection;
	D3DXVECTOR3 m_vPosition;
	D3DXMATRIXA16 m_matWorld;

	LPDIRECT3DTEXTURE9 m_pTexture;	//텍스쳐를 관리할 텍스쳐 객체

	iMap* m_pMap;

public:
	cCharacter();
	virtual ~cCharacter(void);
	virtual void Setup();
	virtual void Update(iMap* pMap);
	virtual void Render();
	virtual D3DXVECTOR3& GetPosition();

	virtual D3DXMATRIXA16* GetTransform()
	{
		return &m_matWorld;
	}
};

