#pragma once
#include "ObjData.h"
#include "MtlTex.h"

class Group : public ObjData
{
private:
	Synthesize_pass_by_Ref(std::vector<PNT_VERTEX>, vec_Vertex, Vertex);
	Synthesize_Add_Ref(MtlTex*, mtlTex, Mat);

public:
	Group();
	~Group();

	void Render(float delta);
};


