#pragma once

// 공격 012 아이들4
class cSkinnedMesh
{
protected:
	LPD3DXFRAME m_pRoot;
	LPD3DXANIMATIONCONTROLLER m_pAnimController;

	bool m_isAnimBlend;
	float m_fBlendTime;
	float m_fPassedBlendTime;
	
	DWORD m_dAnimStartTime;
public:
	cSkinnedMesh();
	~cSkinnedMesh();

	void Setup(char* szFolder, char* szFile);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Render(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);

};

