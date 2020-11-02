#pragma once
#include "framework.h"

// point & color
struct PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

// point & normal & texture
struct PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2	t;

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2	t;

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};