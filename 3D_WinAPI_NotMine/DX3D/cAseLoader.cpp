#include "stdafx.h"
#include "cAseLoader.h"


#include "stdafx.h"
#include "cAseLoader.h"
#include "Asciitok.h"
#include "cMtlTex.h"
#include "cFrame.h"

cAseLoader::cAseLoader()
	: m_fp(nullptr)
{
}


cAseLoader::~cAseLoader()
{
}

cFrame* cAseLoader::Load(char* szFullPath)
{
	cFrame* pRoot = nullptr;

	fopen_s(&m_fp, szFullPath, "r");

	while (char* szToken = GetToken())
	{
		if (IsEqual(szToken, ID_SCENE))
		{
			//ProcessScene();
		}
		else if (IsEqual(szToken, ID_MATERIAL_LIST))
		{
			ProcessMATERIAL_LIST();
		}
		else if (IsEqual(szToken, ID_GEOMETRY))
		{
			cFrame* pFrame = ProcessGEOBJECT();
			if (pRoot == nullptr)
			{
				pRoot = pFrame;
				Set_SceneFrame(pRoot);
			}
		}
	} //<<:while()
	fclose(m_fp);

	for each (auto p in m_vecMtlTex)
	{
		SafeRelease(p);
	}

	pRoot->CalcOriginLocalTM(nullptr);

	return pRoot;
}

char* cAseLoader::GetToken()
{
	int nReadCnt = 0; //읽은 갯수
	bool isQuote = false;

	while (true)
	{
		char c = fgetc(m_fp);
		if (feof(m_fp))break;

		if (c == '\"')
		{
			if (isQuote) break;
			isQuote = true;
			continue;
		}

		if (!isQuote && IsWhite(c))
		{
			if (nReadCnt == 0)
				continue;
			break;
		}
		//그사이에 있는내용들은 토근에
		m_szToken[nReadCnt++] = c;
	} //<<:while()
	if (nReadCnt == 0)
		return nullptr;
	//맨뒤에다가 널문자를 넣어주고
	m_szToken[nReadCnt] = '\0';
	//애를 넘겨준다 .
	return m_szToken;
}

int cAseLoader::GetInteger()
{
	return atoi(GetToken());
}

float cAseLoader::GetFloat()
{
	return static_cast<float>(atof(GetToken()));
}

bool cAseLoader::IsWhite(char c)
{
	return c == 33; //33위로가면 어떻게되냐 ? 나중에 알아서 확인해바
}

bool cAseLoader::IsEqual(char* str1, char* str2)
{
	return strcmp(str1, str2) == 0; //같다고하면 같은거잖아
}

void cAseLoader::SkipBlock()
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
	}
	while (nLevel > 0);
}

void cAseLoader::ProcessMATERIAL_LIST()
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MATERIAL_COUNT))
		{
			for each (auto p in m_vecMtlTex)
			{
				SafeRelease(p);
			}
			m_vecMtlTex.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MATERIAL))
		{
			int nIndex = GetInteger();
			m_vecMtlTex[nIndex] = new cMtlTex;
			ProcessMATERIAL(m_vecMtlTex[nIndex]);
		}
	}
	while (nLevel > 0);
}

void cAseLoader::ProcessMATERIAL(cMtlTex* pMtltex)
{
	D3DMATERIAL9 stMtl;
	ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_AMBIENT))
		{
			stMtl.Ambient.r = GetFloat();
			stMtl.Ambient.g = GetFloat();
			stMtl.Ambient.b = GetFloat();
			stMtl.Ambient.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_DIFFUSE))
		{
			stMtl.Diffuse.r = GetFloat();
			stMtl.Diffuse.g = GetFloat();
			stMtl.Diffuse.b = GetFloat();
			stMtl.Diffuse.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_SPECULAR))
		{
			stMtl.Specular.r = GetFloat();
			stMtl.Specular.g = GetFloat();
			stMtl.Specular.b = GetFloat();
			stMtl.Specular.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_MAP_DIFFUSE))
		{
			ProcessMAP_DIFFUSE(pMtltex);
		}
	}
	while (nLevel > 0);

	pMtltex->SetMaterial(stMtl);
}

void cAseLoader::ProcessMAP_DIFFUSE(cMtlTex* pMtltex)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_BITMAP))
		{
			szToken = GetToken();
			pMtltex->SetTexture(g_pTextureManager->GetTexture(szToken));
		}
	}
	while (nLevel > 0);
}

cFrame* cAseLoader::ProcessGEOBJECT()
{
	cFrame* pFrame = new cFrame;

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_NODE_NAME))
		{
			m_mapFrame[GetToken()] = pFrame;
		}
		else if (IsEqual(szToken, ID_NODE_PARENT))
		{
			m_mapFrame[GetToken()]->AddChild(pFrame);
		}
		else if (IsEqual(szToken, ID_NODE_TM))
		{
			ProcessNODE_TM(pFrame);
		}
		else if (IsEqual(szToken, ID_MESH))
		{
			ProcessMESH(pFrame);
		}
		else if (IsEqual(szToken, ID_TM_ANIMATION))
		{
			// skip
		}
		else if (IsEqual(szToken, ID_MATERIAL_REF))
		{
			int nMtlIndex = GetInteger();
			pFrame->SetMtlTex(m_vecMtlTex[nMtlIndex]);
		}
	}
	while (nLevel > 0);

	return pFrame;
}

void cAseLoader::ProcessMESH(OUT cFrame* pFrame)
{
	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;
	vector<ST_PNT_VERTEX> vecVertex;

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_NUMVERTEX))
		{
			vecV.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MESH_NUMFACES))
		{
			vecVertex.resize(GetInteger() * 3);
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX_LIST))
		{
			ProcessMESH_VERTEX_LIST(vecV);
		}
		else if (IsEqual(szToken, ID_MESH_FACE_LIST))
		{
			ProcessMESH_FACE_LIST(vecVertex, vecV);
		}
		else if (IsEqual(szToken, ID_MESH_NUMTVERTEX))
		{
			vecVT.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MESH_TVERTLIST))
		{
			ProcessMESH_TVERTLIST(vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_TFACELIST))
		{
			ProcessMESH_TFACELIST(vecVertex, vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_NORMALS))
		{
			ProcessMESH_NOMRALS(vecVertex);
		}
	}
	while (nLevel > 0);

	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixInverse(&matInvWorld, nullptr, &pFrame->GetWorldTM());
	for (int i = 0; i < vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInvWorld);

		D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n, &matInvWorld);
		pFrame->SetVertex(vecVertex);
	}
}

void cAseLoader::ProcessMESH_VERTEX_LIST(vector<D3DXVECTOR3>& vecV)
{
	int nLevel = 0;
	do
	{
		char * szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX))
		{
			int nIndex = GetInteger();
			vecV[nIndex].x = GetFloat();
			vecV[nIndex].z = GetFloat();
			vecV[nIndex].y = GetFloat();
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMESH_FACE_LIST(vector<ST_PNT_VERTEX>& vecVertex, vector<D3DXVECTOR3>& vecV)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX))
		{
			int nFaceIndex = GetInteger();
		}
		else if (IsEqual(szToken, ID_MESH_FACE))
		{
			int nFaceIndex = GetInteger();
			GetToken();
			vecVertex[nFaceIndex * 3 + 0].p = vecV[GetInteger()];
			GetToken();
			vecVertex[nFaceIndex * 3 + 2].p = vecV[GetInteger()];
			GetToken();
			vecVertex[nFaceIndex * 3 + 1].p = vecV[GetInteger()];
		}
	}
	while (nLevel > 0);
}

void cAseLoader::ProcessMESH_TVERTLIST(vector<D3DXVECTOR2>& vecVT)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_TVERT))
		{
			int nIndex = GetInteger();
			vecVT[nIndex].x = GetFloat();
			vecVT[nIndex].y = 1.0f - GetFloat();
		}
	}
	while (nLevel > 0);
}

void cAseLoader::ProcessMESH_TFACELIST(vector<ST_PNT_VERTEX>& vecVertex, vector<D3DXVECTOR2>& vecVT)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_TFACE))
		{
			int nFaceIndex = GetInteger();
			vecVertex[nFaceIndex * 3 + 0].t = vecVT[GetInteger()];
			vecVertex[nFaceIndex * 3 + 2].t = vecVT[GetInteger()];
			vecVertex[nFaceIndex * 3 + 1].t = vecVT[GetInteger()];
		}
	}
	while (nLevel > 0);
}

void cAseLoader::ProcessMESH_NOMRALS(vector<ST_PNT_VERTEX>& vecVertex)
{
	int nFaceIndex = 0;
	int aModIndex[3] = {0, 2, 1};
	int nModCount = 0;

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_FACENORMAL))
		{
			nFaceIndex = GetInteger();
			nModCount = 0;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEXNORMAL))
		{
			GetToken();
			D3DXVECTOR3 n;
			n.x = GetFloat();
			n.z = GetFloat();
			n.y = GetFloat();
			vecVertex[nFaceIndex * 3 + aModIndex[nModCount++]].n = n;
		}
	}
	while (nLevel > 0);
}

void cAseLoader::ProcessNODE_TM(cFrame* pFrame)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_TM_ROW0))
		{
			matWorld._11 = GetFloat();
			matWorld._13 = GetFloat();
			matWorld._12 = GetFloat();
			matWorld._14 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW1))
		{
			matWorld._31 = GetFloat();
			matWorld._33 = GetFloat();
			matWorld._32 = GetFloat();
			matWorld._34 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW2))
		{
			matWorld._21 = GetFloat();
			matWorld._23 = GetFloat();
			matWorld._22 = GetFloat();
			matWorld._24 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW3))
		{
			matWorld._41 = GetFloat();
			matWorld._43 = GetFloat();
			matWorld._42 = GetFloat();
			matWorld._44 = 1.0f;
		}
	}
	while (nLevel > 0);

	pFrame->SetWorldTM(matWorld);
}

void cAseLoader::ProcessScene()
{
}

void cAseLoader::Set_SceneFrame(cFrame* pRoot)
{
}
