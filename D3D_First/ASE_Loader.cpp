#include "stdafx.h"
#include "ObjectFrame.h"
#include "ObjectSrc/MtlTex.h"
#include "Asciitok.h"
#include "ASE_Loader.h"

#define IsEqual(str1, str2) PS.IsEqual(str1, str2)
#define GetToken() PS.GetToken()
#define GetFloat() PS.GetFloat()
#define GetInteger() PS.GetInteger()

ASE_Loader::ASE_Loader()
{
}

ASE_Loader::~ASE_Loader()
{
}

ObjectFrame* ASE_Loader::Load(char* FullPath)
{
	PS.FileOpen(FullPath);

	ObjectFrame* Root = nullptr;

	while (char* token = GetToken())
	{
		if (IsEqual(token, ID_SCENE))
		{
			ProcessScene();
		}
		else if (IsEqual(token, ID_MATERIAL_LIST))
		{
			ProcessMATERIAL_LIST();
		}
		else if (IsEqual(token, ID_GEOMETRY))
		{
			ObjectFrame* frame = ProcessGEOBJECT();
			if (Root == nullptr)
			{
				Root = frame;
				Set_SceneFrame(Root);
			}
		}
	}
	
	PS.FileClose();

	for each (auto p in m_vecMtlTex)
	{
		SafeRelease(p);
	}

	Root->CalcOriginLocalTM(nullptr);

	return Root;
}

void ASE_Loader::ProcessMATERIAL_LIST()
{
	int Level = 0;

	do
	{
		char* token = GetToken();

		if (IsEqual(token, "{")) Level++;
		else if (IsEqual(token, "}")) Level--;

		else if (IsEqual(token, ID_MATERIAL_COUNT))
		{
			for each (auto p in m_vecMtlTex)
			{
				SafeRelease(p);
			}
			m_vecMtlTex.resize(GetInteger());
		}
		else if (IsEqual(token, ID_MATERIAL))
		{
			int nIndex = GetInteger();
			m_vecMtlTex[nIndex] = new MtlTex;
			ProcessMATERIAL(m_vecMtlTex[nIndex]);
		}

	} while (Level > 0);
	
}

void ASE_Loader::ProcessMATERIAL(MtlTex* pMtltex)
{
	D3DMATERIAL9 stMtl;
	ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));
	
	int Level = 0;

	do
	{
		char* token = GetToken();

		if (IsEqual(token, "{")) Level++;
		else if (IsEqual(token, "}")) Level--;

		else if (IsEqual(token, ID_AMBIENT))
		{
			stMtl.Ambient.r = GetFloat();
			stMtl.Ambient.g = GetFloat();
			stMtl.Ambient.b = GetFloat();
			stMtl.Ambient.a = 1.0f;
		}
		else if (IsEqual(token, ID_DIFFUSE))
		{
			stMtl.Diffuse.r = GetFloat();
			stMtl.Diffuse.g = GetFloat();
			stMtl.Diffuse.b = GetFloat();
			stMtl.Diffuse.a = 1.0f;
		}
		else if (IsEqual(token, ID_SPECULAR))
		{
			stMtl.Specular.r = GetFloat();
			stMtl.Specular.g = GetFloat();
			stMtl.Specular.b = GetFloat();
			stMtl.Specular.a = 1.0f;
		}
		else if (IsEqual(token, ID_MAP_DIFFUSE))
		{
			ProcessMAP_DIFFUSE(pMtltex);
		}

	} while (Level > 0);

	pMtltex->SetMaterial(stMtl);
}

void ASE_Loader::ProcessMAP_DIFFUSE(MtlTex* pMtltex)
{
	int Level = 0;

	do
	{
		char* token = GetToken();

		if (IsEqual(token, "{")) Level++;
		else if (IsEqual(token, "}")) Level--;

		else if (IsEqual(token, ID_BITMAP))
		{
			token = GetToken();
			pMtltex->SetTexture(TEXTUREMANAGER->GetTexture(token));
		}

	} while (Level > 0);
}

ObjectFrame* ASE_Loader::ProcessGEOBJECT()
{
	ObjectFrame* frame = new ObjectFrame;
	int Level = 0;

	do
	{
		char* token = GetToken();

		if (IsEqual(token, "{")) Level++;
		else if (IsEqual(token, "}")) Level--;

		else if (IsEqual(token, ID_NODE_NAME))
		{
			m_mapFrame[GetToken()] = frame;
		}
		else if (IsEqual(token, ID_NODE_PARENT))
		{
			m_mapFrame[GetToken()]->AddChild(frame);
		}
		else if (IsEqual(token, ID_NODE_TM))
		{
			ProcessNODE_TM(frame);
		}
		else if (IsEqual(token, ID_MESH))
		{
			ProcessMESH(frame);
		}
		else if (IsEqual(token, ID_TM_ANIMATION))
		{
			ProcessTM_ANIMATION(frame);
		}
		else if (IsEqual(token, ID_MATERIAL_REF))
		{
			int nMtlIndex = GetInteger();
			frame->SetMtlTex(m_vecMtlTex[nMtlIndex]);
		}

	} while (Level > 0);

	return frame;
}

void ASE_Loader::ProcessMESH(ObjectFrame* frame)
{
	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;
	vector<PNT_VERTEX> vecVertex;
	
	int Level = 0;

	do
	{
		char* token = GetToken();

		if (IsEqual(token, "{")) Level++;
		else if (IsEqual(token, "}")) Level--;

		else if (IsEqual(token, ID_MESH_NUMVERTEX))
		{
			vecV.resize(GetInteger());
		}
		else if (IsEqual(token, ID_MESH_NUMFACES))
		{
			vecVertex.resize(GetInteger() * 3);
		}
		else if (IsEqual(token, ID_MESH_VERTEX_LIST))
		{
			ProcessMESH_VERTEX_LIST(vecV);
		}
		else if (IsEqual(token, ID_MESH_FACE_LIST))
		{
			ProcessMESH_FACE_LIST(vecVertex, vecV);
		}
		else if (IsEqual(token, ID_MESH_NUMTVERTEX))
		{
			vecVT.resize(GetInteger());
		}
		else if (IsEqual(token, ID_MESH_TVERTLIST))
		{
			ProcessMESH_TVERTLIST(vecVT);
		}
		else if (IsEqual(token, ID_MESH_TFACELIST))
		{
			ProcessMESH_TFACELIST(vecVertex, vecVT);
		}
		else if (IsEqual(token, ID_MESH_NORMALS))
		{
			ProcessMESH_NOMRALS(vecVertex);
		}

	} while (Level > 0);

	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixInverse(&matInvWorld, nullptr, &frame->GetWorldTM());
	for (int i = 0; i < vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInvWorld);

		D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n, &matInvWorld);
		frame->SetVertex(vecVertex);
	}
}

void ASE_Loader::ProcessMESH_VERTEX_LIST(vector<D3DXVECTOR3>& vecV)
{
	int Level = 0;

	do
	{
		char* token = GetToken();

		if (IsEqual(token, "{")) Level++;
		else if (IsEqual(token, "}")) Level--;

		else if (IsEqual(token, ID_MESH_VERTEX))
		{
			int nIndex = GetInteger();
			vecV[nIndex].x = GetFloat();
			vecV[nIndex].z = GetFloat();
			vecV[nIndex].y = GetFloat();
		}

	} while (Level > 0);
}

void ASE_Loader::ProcessMESH_FACE_LIST(vector<PNT_VERTEX>& vecVertex, vector<D3DXVECTOR3>& vecV)
{
	int Level = 0;

	do
	{
		char* token = GetToken();

		if (IsEqual(token, "{")) Level++;
		else if (IsEqual(token, "}")) Level--;

		else if (IsEqual(token, ID_MESH_FACE))
		{
			int nFaceIndex = GetInteger();
			GetToken();
			vecVertex[nFaceIndex * 3 + 0].p = vecV[GetInteger()];
			GetToken();
			vecVertex[nFaceIndex * 3 + 2].p = vecV[GetInteger()];
			GetToken();
			vecVertex[nFaceIndex * 3 + 1].p = vecV[GetInteger()];
		}

	} while (Level > 0);
}

void ASE_Loader::ProcessMESH_TVERTLIST(vector<D3DXVECTOR2>& vecVT)
{
	int Level = 0;

	do
	{
		char* token = GetToken();

		if (IsEqual(token, "{")) Level++;
		else if (IsEqual(token, "}")) Level--;

		else if (IsEqual(token, ID_MESH_TVERT))
		{
			int nIndex = GetInteger();
			vecVT[nIndex].x = GetFloat();
			vecVT[nIndex].y = 1.0f - GetFloat();
		}
		
	} while (Level > 0);
	
}

void ASE_Loader::ProcessMESH_TFACELIST(vector<PNT_VERTEX>& vecVertex, vector<D3DXVECTOR2>& vecVT)
{
	int Level = 0;

	do
	{
		char* token = GetToken();

		if (IsEqual(token, "{")) Level++;
		else if (IsEqual(token, "}")) Level--;

		else if (IsEqual(token, ID_MESH_TFACE))
		{
			int nFaceIndex = GetInteger();
			vecVertex[nFaceIndex * 3 + 0].t = vecVT[GetInteger()];
			vecVertex[nFaceIndex * 3 + 2].t = vecVT[GetInteger()];
			vecVertex[nFaceIndex * 3 + 1].t = vecVT[GetInteger()];
		}

	} while (Level > 0);
}

void ASE_Loader::ProcessMESH_NOMRALS(vector<PNT_VERTEX>& vecVertex)
{
	int nFaceIndex = 0;
	int aModIndex[3] = { 0, 2, 1 };
	int nModCount = 0;

	int Level = 0;

	do
	{
		char* token = GetToken();

		if (IsEqual(token, "{")) Level++;
		else if (IsEqual(token, "}")) Level--;

		else if (IsEqual(token, ID_MESH_FACENORMAL))
		{
			nFaceIndex = GetInteger();
			nModCount = 0;
		}
		else if (IsEqual(token, ID_MESH_VERTEXNORMAL))
		{
			GetToken();
			D3DXVECTOR3 n;
			n.x = GetFloat();
			n.z = GetFloat();
			n.y = GetFloat();
			vecVertex[nFaceIndex * 3 + aModIndex[nModCount++]].n = n;
		}

	} while (Level > 0);
}

void ASE_Loader::ProcessNODE_TM(ObjectFrame* frame)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	
	int Level = 0;

	do
	{
		char* token = GetToken();

		if (IsEqual(token, "{")) Level++;
		else if (IsEqual(token, "}")) Level--;

		else if (IsEqual(token, ID_TM_ROW0))
		{
			matWorld._11 = GetFloat();
			matWorld._13 = GetFloat();
			matWorld._12 = GetFloat();
			matWorld._14 = 0.0f;
		}
		else if (IsEqual(token, ID_TM_ROW1))
		{
			matWorld._31 = GetFloat();
			matWorld._33 = GetFloat();
			matWorld._32 = GetFloat();
			matWorld._34 = 0.0f;
		}
		else if (IsEqual(token, ID_TM_ROW2))
		{
			matWorld._21 = GetFloat();
			matWorld._23 = GetFloat();
			matWorld._22 = GetFloat();
			matWorld._24 = 0.0f;
		}
		else if (IsEqual(token, ID_TM_ROW3))
		{
			matWorld._41 = GetFloat();
			matWorld._43 = GetFloat();
			matWorld._42 = GetFloat();
			matWorld._44 = 1.0f;
		}

	} while (Level > 0);

	frame->SetWorldTM(matWorld);
}

void ASE_Loader::ProcessScene()
{
	int Level = 0;

	do
	{
		char* token = GetToken();

		if (IsEqual(token, "{")) Level++;
		else if (IsEqual(token, "}")) Level--;

		else if (IsEqual(token, ID_FIRSTFRAME))
		{
			m_dwFirstFrame = GetInteger();
		}
		else if (IsEqual(token, ID_LASTFRAME))
		{
			m_dwLastFrame = GetInteger();
		}
		else if (IsEqual(token, ID_FRAMESPEED))
		{
			m_dwFrameSpeed = GetInteger();
		}
		else if (IsEqual(token, ID_TICKSPERFRAME))
		{
			m_dwTicksPerFrame = GetInteger();
		}

	} while (Level > 0);
}

void ASE_Loader::Set_SceneFrame(ObjectFrame* pRoot)
{
	pRoot->m_dwFirstFrame = m_dwFirstFrame;
	pRoot->m_dwLastFrame = m_dwLastFrame;
	pRoot->m_dwFrameSpeed = m_dwFrameSpeed;
	pRoot->m_dwTicksPerFrame = m_dwTicksPerFrame;
}

void ASE_Loader::ProcessTM_ANIMATION(ObjectFrame* pFrame)
{
	int Level = 0;

	do
	{
		char* token = GetToken();

		if (IsEqual(token, "{")) Level++;
		else if (IsEqual(token, "}")) Level--;

		else if (IsEqual(token, ID_POS_TRACK))
		{
			ProcessCONTROL_POS_TRACK(pFrame);
		}
		else if (IsEqual(token, ID_ROT_TRACK))
		{
			ProcessCONTROL_ROT_TRACK(pFrame);
		}

	} while (Level > 0);
}

void ASE_Loader::ProcessCONTROL_POS_TRACK(ObjectFrame* pFrame)
{
	vector<ST_POS_SAMPLE> vecPosTrack;

	int nLevel = 0;
	do
	{
		char* token = GetToken();
		if (IsEqual(token, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(token, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(token, ID_POS_SAMPLE))
		{
			ST_POS_SAMPLE s;
			s.n = GetInteger();
			s.v.x = GetFloat();
			s.v.z = GetFloat();
			s.v.y = GetFloat();
			vecPosTrack.push_back(s);
		}
	} while (nLevel > 0);

	pFrame->SetPosTrack(vecPosTrack);
}

void ASE_Loader::ProcessCONTROL_ROT_TRACK(ObjectFrame* pFrame)
{
	vector<ST_ROT_SAMPLE> vecRotTrack;
	int nLevel = 0;
	do
	{
		char* token = GetToken();
		if (IsEqual(token, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(token, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(token, ID_ROT_SAMPLE))
		{
			ST_ROT_SAMPLE s;
			s.n = GetInteger();
			s.q.x = GetFloat();
			s.q.z = GetFloat();
			s.q.y = GetFloat();
			s.q.w = GetFloat();

			//쿼터니온으로 바꿔주려면 변환식이 들어가야한다.
			s.q.x *= sinf(s.q.w / 2.f);
			s.q.y *= sinf(s.q.w / 2.f);
			s.q.z *= sinf(s.q.w / 2.f);
			s.q.w = cosf(s.q.w / 2.f);

			if (!vecRotTrack.empty())
			{
				s.q = vecRotTrack.back().q * s.q;	//회전값 누적
			}
			vecRotTrack.push_back(s);
		}
	} while (nLevel > 0);

	pFrame->SetRotTrack(vecRotTrack);
}
