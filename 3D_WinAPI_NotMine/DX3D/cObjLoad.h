#pragma once
class cMtlTex;
class cGroup;

class cObjLoad
{
private:
	std::map<std::string, cMtlTex*> m_mapMtlTex;

public:
	cObjLoad();
	~cObjLoad();

	void Load(OUT std::vector<cGroup*>&vecGroup, IN char* szFolder, IN char* szFile);
	void LoadMtlLib(char* szFolder, char* szFile);

	void LoadSurface(OUT vector<D3DXVECTOR3>& vecSurface, IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16 * pmat = NULL);
	//맵을 그리지 않고 처리해야할게 있어서


	LPD3DXMESH LoadMesh(OUT vector<cMtlTex*>&vecMtlTex, IN char* szFolder, IN char* szFile);

};

