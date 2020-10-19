#pragma once
#include "Parser.h"
class MtlTex;
class ObjectFrame;

class ASE_Loader
{
private:
	Parser PS;
	vector<MtlTex*> m_vecMtlTex;
	map<string, ObjectFrame*> m_mapFrame;

	//프레임 계산용 변수
	DWORD m_dwFirstFrame;
	DWORD m_dwLastFrame;
	DWORD m_dwFrameSpeed;
	DWORD m_dwTicksPerFrame;
	
public:
	ASE_Loader();
	~ASE_Loader();

	ObjectFrame* Load(IN char* szFullPath);
	
	void ProcessMATERIAL_LIST();
	void ProcessMATERIAL(OUT MtlTex* pMtltex);
	void ProcessMAP_DIFFUSE(OUT MtlTex* pMtltex);
	ObjectFrame* ProcessGEOBJECT();
	void ProcessMESH(OUT ObjectFrame* pFrame);
	void ProcessMESH_VERTEX_LIST(OUT vector<D3DXVECTOR3>& vecV);
	void ProcessMESH_FACE_LIST(OUT vector<PNT_VERTEX>& vecVertex, IN vector<D3DXVECTOR3>& vecV);
	void ProcessMESH_TVERTLIST(OUT vector<D3DXVECTOR2>& vecVT);
	void ProcessMESH_TFACELIST(OUT vector<PNT_VERTEX>& vecVertex, IN vector<D3DXVECTOR2>& vecVT);
	void ProcessMESH_NOMRALS(OUT vector<PNT_VERTEX>& vecVertex);
	void ProcessNODE_TM(OUT ObjectFrame* pFrame);
	void ProcessScene();
	void Set_SceneFrame(OUT ObjectFrame* pRoot);

	//애니메이션 관련 >>
	void ProcessTM_ANIMATION(OUT ObjectFrame* pFrame);
	void ProcessCONTROL_POS_TRACK(OUT ObjectFrame* pFrame);
	void ProcessCONTROL_ROT_TRACK(OUT ObjectFrame* pFrame);
};