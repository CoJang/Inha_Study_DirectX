#pragma once
#include "cCubeNode.h"

class cRightArm :
	public cCubeNode
{
public:
	cRightArm();
	~cRightArm();
	void Setup() override;
};
