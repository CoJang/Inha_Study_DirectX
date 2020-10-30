#pragma once

#define g_pSkinnedMeshManager cSkinnedMeshMananger::GetInstance()

class cSkinnedMesh;

class cSkinnedMeshMananger
{
private:
	map<string, cSkinnedMesh*> m_mapSkinnedMesh;
public:
	Singletone(cSkinnedMeshMananger);

	cSkinnedMesh* GetSkinnedMesh(char* szFolder, char* szFileName);

	void Destroy();
};

