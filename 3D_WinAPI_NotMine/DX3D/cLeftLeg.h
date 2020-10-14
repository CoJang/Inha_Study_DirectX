#pragma once
#include "cCubeNode.h"

class cLeftLeg :
	public cCubeNode
{
public:
	cLeftLeg();
	~cLeftLeg();
	void Setup() override;
};
