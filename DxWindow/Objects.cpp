#include "framework.h"
#include "VertexStruct.h"
#include "Objects.h"


Objects_PC::Objects_PC()
{
	D3DXMatrixIdentity(&ScaleMat);
	D3DXMatrixIdentity(&RotateMat);
	D3DXMatrixIdentity(&TransMat);
	D3DXMatrixIdentity(&WorldMat);
}


Objects_PC::~Objects_PC()
{
}

Objects_PNT::Objects_PNT()
{
}


Objects_PNT::~Objects_PNT()
{
}

void Objects_PNT::Draw(float delta)
{
	D3DXMATRIXA16 WMat;
	D3DXMatrixIdentity(&WMat);
	g_pDevice->SetTransform(D3DTS_WORLD, &WMat);
	g_pDevice->SetFVF(PNT_VERTEX::FVF);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
							vec_Vertexs.size() / 3,
							&vec_Vertexs[0],
							sizeof(PNT_VERTEX));
}
