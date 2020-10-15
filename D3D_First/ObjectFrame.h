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

public:
	ObjectFrame();
	~ObjectFrame();
	
	void Update(int KeyFrame, D3DXMATRIXA16* pmatParent);
	void Render();
	void AddChild(ObjectFrame* pChild);
	void Destroy();
	void CalcOriginLocalTM(D3DXMATRIXA16* pmatParent);
};

