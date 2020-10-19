#pragma once
#include "ObjectSrc/MtlTex.h"

class ObjectFrame : public ObjData
{
private:
	Synthesize_pass_by_Ref(vector<PNT_VERTEX>, m_vecVertex, Vertex);
	Synthesize_pass_by_Ref(D3DXMATRIXA16, LocalTM, LocalTM);
	Synthesize_pass_by_Ref(D3DXMATRIXA16, WorldTM, WorldTM);

	Synthesize_Add_Ref(MtlTex*, m_pMtlTex, MtlTex);
	vector<ObjectFrame*> m_vecChild;

	Synthesize_pass_by_Ref(vector<ST_POS_SAMPLE>, m_vecPosTrack, PosTrack);
	Synthesize_pass_by_Ref(vector<ST_ROT_SAMPLE>, m_vecRotTrack, RotTrack);

	int m_nNumTri;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
public:
	ObjectFrame();
	~ObjectFrame();
	
	void Update(int KeyFrame, D3DXMATRIXA16* pmatParent);
	void Render();
	void AddChild(ObjectFrame* pChild);
	void Destroy();
	void CalcOriginLocalTM(D3DXMATRIXA16* pmatParent);

	void CalcLocalT(IN int nKeyFrame, OUT D3DXMATRIXA16& matT);
	void CalcLocalR(IN int nKeyFrame, OUT D3DXMATRIXA16& matR);

	DWORD m_dwFirstFrame;
	DWORD m_dwLastFrame;
	DWORD m_dwFrameSpeed;
	DWORD m_dwTicksPerFrame;

	int GetKeyFrame();
	void BuildVB(vector<PNT_VERTEX>& vecVertex);
};

