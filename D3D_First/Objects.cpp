#include "stdafx.h"
#include "Objects.h"


Objects::Objects()
{
	D3DXMatrixIdentity(&ScaleMat);
	D3DXMatrixIdentity(&RotateMat);
	D3DXMatrixIdentity(&TransMat);
	D3DXMatrixIdentity(&WorldMat);
}


Objects::~Objects()
{
}
