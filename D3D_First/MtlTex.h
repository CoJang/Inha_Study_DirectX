#pragma once
#include "ObjData.h"

class MtlTex : public ObjData
{
private:
	Synthesize_pass_by_Ref(D3DMATERIAL9, Mlt, Material);
	Synthesize_Add_Ref(LPDIRECT3DTEXTURE9, Texture, Texture);
public:
	MtlTex();
	~MtlTex();
};

