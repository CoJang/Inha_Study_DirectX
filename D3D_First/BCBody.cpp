#include "stdafx.h"
#include "BCBody.h"

BCBody::BCBody()
	:ParentWorldMat(NULL)
{
}

BCBody::~BCBody()
{
}

void BCBody::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXCOLOR color)
{
	Box::Init(pos, scale, color);

	// 012 023
	vec_Vertexs[0].t = D3DXVECTOR2(20 / 64.0f, 32 / 64.0f);
	vec_Vertexs[1].t = D3DXVECTOR2(20 / 64.0f, 20 / 64.0f);
	vec_Vertexs[2].t = D3DXVECTOR2(28 / 64.0f, 20 / 64.0f);

	vec_Vertexs[3].t = D3DXVECTOR2(20 / 64.0f, 32 / 64.0f);
	vec_Vertexs[4].t = D3DXVECTOR2(28 / 64.0f, 20 / 64.0f);
	vec_Vertexs[5].t = D3DXVECTOR2(28 / 64.0f, 32 / 64.0f);

	// 465 476
	vec_Vertexs[6].t = D3DXVECTOR2(40 / 64.0f, 32 / 64.0f);
	vec_Vertexs[7].t = D3DXVECTOR2(32 / 64.0f, 20 / 64.0f);
	vec_Vertexs[8].t = D3DXVECTOR2(40 / 64.0f, 20 / 64.0f);

	vec_Vertexs[9].t = D3DXVECTOR2(40 / 64.0f, 32 / 64.0f);
	vec_Vertexs[10].t = D3DXVECTOR2(32 / 64.0f, 32 / 64.0f);
	vec_Vertexs[11].t = D3DXVECTOR2(32 / 64.0f, 20 / 64.0f);

	// 451 410
	vec_Vertexs[12].t = D3DXVECTOR2(16 / 64.0f, 32 / 64.0f);
	vec_Vertexs[13].t = D3DXVECTOR2(16 / 64.0f, 20 / 64.0f);
	vec_Vertexs[14].t = D3DXVECTOR2(20 / 64.0f, 20 / 64.0f);

	vec_Vertexs[15].t = D3DXVECTOR2(16 / 64.0f, 32 / 64.0f);
	vec_Vertexs[16].t = D3DXVECTOR2(20 / 64.0f, 20 / 64.0f);
	vec_Vertexs[17].t = D3DXVECTOR2(20 / 64.0f, 32 / 64.0f);

	// 326 367
	vec_Vertexs[18].t = D3DXVECTOR2(28 / 64.0f, 32 / 64.0f);
	vec_Vertexs[19].t = D3DXVECTOR2(28 / 64.0f, 20 / 64.0f);
	vec_Vertexs[20].t = D3DXVECTOR2(32 / 64.0f, 20 / 64.0f);

	vec_Vertexs[21].t = D3DXVECTOR2(28 / 64.0f, 32 / 64.0f);
	vec_Vertexs[22].t = D3DXVECTOR2(32 / 64.0f, 20 / 64.0f);
	vec_Vertexs[23].t = D3DXVECTOR2(32 / 64.0f, 32 / 64.0f);

	// 156 162 [UP]
	vec_Vertexs[24].t = D3DXVECTOR2(20 / 64.0f, 20 / 64.0f);
	vec_Vertexs[25].t = D3DXVECTOR2(20 / 64.0f, 16 / 64.0f);
	vec_Vertexs[26].t = D3DXVECTOR2(28 / 64.0f, 16 / 64.0f);

	vec_Vertexs[27].t = D3DXVECTOR2(20 / 64.0f, 20 / 64.0f);
	vec_Vertexs[28].t = D3DXVECTOR2(28 / 64.0f, 16 / 64.0f);
	vec_Vertexs[29].t = D3DXVECTOR2(28 / 64.0f, 20 / 64.0f);

	// 403 437 [BOTTOM]
	vec_Vertexs[30].t = D3DXVECTOR2(28 / 64.0f, 20 / 64.0f);
	vec_Vertexs[31].t = D3DXVECTOR2(28 / 64.0f, 16 / 64.0f);
	vec_Vertexs[32].t = D3DXVECTOR2(36 / 64.0f, 16 / 64.0f);

	vec_Vertexs[33].t = D3DXVECTOR2(28 / 64.0f, 20 / 64.0f);
	vec_Vertexs[34].t = D3DXVECTOR2(36 / 64.0f, 16 / 64.0f);
	vec_Vertexs[35].t = D3DXVECTOR2(36 / 64.0f, 20 / 64.0f);
}

void BCBody::Update(float delta)
{
	Box::Update(delta);
}

void BCBody::Draw(float delta)
{
	Box::Draw(delta);
}
