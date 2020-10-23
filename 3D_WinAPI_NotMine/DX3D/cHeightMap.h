#pragma once
#include "iMap.h"
class cHeightMap :
	public iMap
{
private:
	LPD3DXMESH m_pMesh;
	vector<D3DXVECTOR3> m_vecVertex;
	D3DMATERIAL9 m_stMtl;
	LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nTileN;


public:
	cHeightMap();
	virtual ~cHeightMap();

	void Setup(char* szFolder, char* szRaw, char* szTex, DWORD dwBytesPerPixel = 1);	//1바이트여서 1 //3바이트인경우 있다 그땐 3
	virtual void Render() override;
	virtual bool GetHeight(IN float x, OUT float&y, IN float z) override;
	void Destroy();

};

