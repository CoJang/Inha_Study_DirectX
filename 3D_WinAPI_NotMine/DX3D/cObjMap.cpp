#include "stdafx.h"
#include "cObjMap.h"
#include "cObjLoad.h"


cObjMap::cObjMap(IN char * szFolder, IN char * szFile, IN D3DXMATRIXA16 * pmat)
{
	Load(szFolder, szFile, pmat);//생성하면서 파일을 로드
}

cObjMap::~cObjMap()
{
}

void cObjMap::Load(IN char * szFolder, IN char * szFile, IN D3DXMATRIXA16 * pmat)
{
	cObjLoad l;
	l.LoadSurface(m_vecSurface, szFolder, szFile, pmat);//m_vecSurface를 가지고 높이를 구하면 된다
}

bool cObjMap::GetHeight(IN float x, OUT float & y, IN float z)
{
	float RayY = 1000;
	D3DXVECTOR3 vRayPos(x, RayY, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);

	for (size_t i = 0; i < m_vecSurface.size(); i +=3) 
	{

		float u, v, f;
		if (D3DXIntersectTri(&m_vecSurface[i + 0], &m_vecSurface[i + 1], &m_vecSurface[i + 2], &vRayPos, &vRayDir, &u, &v, &f)) 
		{
			y = RayY - f;
			
			return true;
		}

	}

	return false;
}
