#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cSkinnedMeshMananger.h"


cSkinnedMeshMananger::cSkinnedMeshMananger()
{
}


cSkinnedMeshMananger::~cSkinnedMeshMananger()
{
}

cSkinnedMesh* cSkinnedMeshMananger::GetSkinnedMesh(char* szFolder, char* szFileName)
{
	string sFullPath(szFolder);
	sFullPath += string("/") + string(szFileName);

	if(m_mapSkinnedMesh.find(sFullPath) == m_mapSkinnedMesh.end())
	{
		cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh();
		pSkinnedMesh->Load(szFolder, szFileName);
		m_mapSkinnedMesh[sFullPath] = pSkinnedMesh;
	}
	return m_mapSkinnedMesh[sFullPath];
}

void cSkinnedMeshMananger::Destroy()
{
	for(auto it : m_mapSkinnedMesh)
	{
		it.second->Destroy();
		SafeDelete(it.second);
	}
}
