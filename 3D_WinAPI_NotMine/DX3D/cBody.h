#pragma once
#include "cCubeNode.h"

class cBody :
	public cCubeNode
{
public:
	cBody();
	~cBody();

	void Setup() override;
};
