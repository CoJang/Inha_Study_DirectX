#pragma once
#include "cCubePNT.h"
class cCubeNode :
    public cCubePNT
{
protected:
	D3DXVECTOR3 m_vLocalPos;
	D3DXMATRIXA16 m_matLocalTM;
	D3DXMATRIXA16 m_matWorldTM;
	std::vector<cCubeNode*> m_vecChild;

	Synthesize(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
	float m_fRotX;
	Synthesize(float, m_fRotDeltaX, RotDeltaX);


public:
	cCubeNode();
	virtual ~cCubeNode(void);

	virtual void Addchild(cCubeNode* pChild);
	virtual void Destroy();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;


};