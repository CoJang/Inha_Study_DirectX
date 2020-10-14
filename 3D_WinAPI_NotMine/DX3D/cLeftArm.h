#pragma once
#include "cCubeNode.h"

class cLeftArm :
	public cCubeNode
{
public:
	cLeftArm();
	~cLeftArm();
	void Setup() override;
};
