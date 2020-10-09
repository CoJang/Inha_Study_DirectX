#include "stdafx.h"
#include "BCRightArm.h"

BCRightArm::BCRightArm()
	:ParentWorldMat(NULL)
{
}

BCRightArm::~BCRightArm()
{
}

void BCRightArm::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXCOLOR color)
{
	Box::Init(pos, scale, color);

	float TEXTURESIZE = 64.0f;

	float left = 40.f / TEXTURESIZE;
	float top = 16.f / TEXTURESIZE;

	float width = 4.f / TEXTURESIZE;
	float deep = 4.f / TEXTURESIZE;
	float high = 12.f / TEXTURESIZE;

	//앞
	vec_Vertexs[0].t.x = left + deep;					vec_Vertexs[0].t.y = top + deep + high;
	vec_Vertexs[1].t.x = left + deep;					vec_Vertexs[1].t.y = top + deep;
	vec_Vertexs[2].t.x = left + deep + width;			vec_Vertexs[2].t.y = top + deep;

	vec_Vertexs[3].t.x = left + deep;					vec_Vertexs[3].t.y = top + deep + high;
	vec_Vertexs[4].t.x = left + deep + width;			vec_Vertexs[4].t.y = top + deep;
	vec_Vertexs[5].t.x = left + deep + width;			vec_Vertexs[5].t.y = top + deep + high;
	//뒤
	vec_Vertexs[6].t.x = left + 2 * deep + 2 * width;	vec_Vertexs[6].t.y = top + deep + high;
	vec_Vertexs[7].t.x = left + 2 * deep + width;		vec_Vertexs[7].t.y = top + deep;
	vec_Vertexs[8].t.x = left + 2 * deep + 2 * width;	vec_Vertexs[8].t.y = top + deep;

	vec_Vertexs[9].t.x = left + 2 * deep + 2 * width;   vec_Vertexs[9].t.y = top + deep + high;
	vec_Vertexs[10].t.x = left + 2 * deep + width;		vec_Vertexs[10].t.y = top + deep + high;
	vec_Vertexs[11].t.x = left + 2 * deep + width;		vec_Vertexs[11].t.y = top + deep;
	//왼
	vec_Vertexs[12].t.x = left;							vec_Vertexs[12].t.y = top + deep + high;
	vec_Vertexs[13].t.x = left;							vec_Vertexs[13].t.y = top + deep;
	vec_Vertexs[14].t.x = left + deep;					vec_Vertexs[14].t.y = top + deep;

	vec_Vertexs[15].t.x = left;							vec_Vertexs[15].t.y = top + deep + high;
	vec_Vertexs[16].t.x = left + deep;					vec_Vertexs[16].t.y = top + deep;
	vec_Vertexs[17].t.x = left + deep;					vec_Vertexs[17].t.y = top + deep + high;
	//오
	vec_Vertexs[18].t.x = left + deep + width;			vec_Vertexs[18].t.y = top + deep + high;
	vec_Vertexs[19].t.x = left + deep + width;			vec_Vertexs[19].t.y = top + deep;
	vec_Vertexs[20].t.x = left + 2 * deep + width;		vec_Vertexs[20].t.y = top + deep;

	vec_Vertexs[21].t.x = left + deep + width;			vec_Vertexs[21].t.y = top + deep + high;
	vec_Vertexs[22].t.x = left + 2 * deep + width;		vec_Vertexs[22].t.y = top + deep;
	vec_Vertexs[23].t.x = left + 2 * deep + width;		vec_Vertexs[23].t.y = top + deep + high;
	//위
	vec_Vertexs[24].t.x = left + deep;					vec_Vertexs[24].t.y = top + deep;
	vec_Vertexs[25].t.x = left + deep;					vec_Vertexs[25].t.y = top;
	vec_Vertexs[26].t.x = left + deep + width;			vec_Vertexs[26].t.y = top;

	vec_Vertexs[27].t.x = left + deep;					vec_Vertexs[27].t.y = top + deep;
	vec_Vertexs[28].t.x = left + deep + width;			vec_Vertexs[28].t.y = top;
	vec_Vertexs[29].t.x = left + deep + width;			vec_Vertexs[29].t.y = top + deep;
	//아래
	vec_Vertexs[30].t.x = left + deep + 2 * width;		vec_Vertexs[30].t.y = top;
	vec_Vertexs[31].t.x = left + deep + 2 * width;		vec_Vertexs[31].t.y = top + deep;
	vec_Vertexs[32].t.x = left + deep + width;			vec_Vertexs[32].t.y = top + deep;

	vec_Vertexs[33].t.x = left + deep + width;			vec_Vertexs[33].t.y = top;
	vec_Vertexs[34].t.x = left + deep + 2 * width;		vec_Vertexs[34].t.y = top + deep;
	vec_Vertexs[35].t.x = left + deep + 2 * width;		vec_Vertexs[35].t.y = top;
}

void BCRightArm::Update(float delta)
{
	Box::Update(delta);

	if (ParentWorldMat)
	{
		WorldMat *= *ParentWorldMat;
	}
}

void BCRightArm::Draw(float delta)
{
	Box::Draw(delta);
}
