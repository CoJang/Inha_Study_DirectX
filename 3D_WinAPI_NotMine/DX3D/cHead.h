#pragma once
#include "cCubeNode.h"

class cHead :
	public cCubeNode
{
public:
	cHead();
	~cHead();
	void Setup() override;
};
