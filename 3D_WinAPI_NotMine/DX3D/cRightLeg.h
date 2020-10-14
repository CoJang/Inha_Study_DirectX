#pragma once
#include "cCubeNode.h"

class cRightLeg :
	public cCubeNode
{
public:
	cRightLeg();
	~cRightLeg();
	void Setup() override;
};
