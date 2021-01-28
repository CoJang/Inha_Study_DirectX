#pragma once
#include "ObjObject.h"

class cBox : public cObjObject
{
public:
	cBox();
	~cBox();

	void Setup(const char* folder, const char* file) override;
	void Render() override;
	void RenderShadow();
};

