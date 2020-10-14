#include "stdafx.h"
#include "Group.h"

Group::Group()
	:mtlTex(NULL)
{
}

Group::~Group()
{
	SafeRelease(mtlTex);
}

void Group::Render(float delta)
{
	if(mtlTex)
	{
		DEVICE->SetTexture(0, mtlTex->GetTexture());
		DEVICE->SetMaterial(&mtlTex->GetMaterial());
	}

	DEVICE->SetFVF(PNT_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
							vec_Vertex.size() / 3,
							&vec_Vertex[0],
							sizeof(PNT_VERTEX));

	if (mtlTex)
	{
		DEVICE->SetTexture(0, NULL);
	}
}

