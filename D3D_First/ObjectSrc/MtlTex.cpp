#include "stdafx.h"
#include "MtlTex.h"


MtlTex::MtlTex()
	:Texture(NULL)
{
	ZeroMemory(&Mlt, sizeof(D3DMATERIAL9));
}


MtlTex::~MtlTex()
{
	SafeRelease(Texture);
}
