#pragma once
#include "cCharacter.h"
class cCubeNode;

class cCubeMan :
	public cCharacter
{
public:
	cCubeMan();
	//~cCubeMan();
protected :
	cCubeNode* m_pRoot;
	D3DMATERIAL9 m_stMtl;
	LPDIRECT3DTEXTURE9 m_pTexture;

public :
	virtual ~cCubeMan();

	void Setup() override;
	void Update(iMap* pMap) override;
	void Render() override;
};
