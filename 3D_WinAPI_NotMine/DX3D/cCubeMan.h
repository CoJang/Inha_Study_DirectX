#pragma once
#include "cCharacter.h"
class cCubeNode;

class cCubeMan :
    public cCharacter
{
protected:
    cCubeNode* m_pRoot;
    D3DMATERIAL9 m_stMtl;

public:
    cCubeMan();
    virtual ~cCubeMan();

    virtual void Setup() override;
    virtual void Update(iMap* pMap) override;
    virtual void Render() override;



};

