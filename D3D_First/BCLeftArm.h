#pragma once
#include "Box.h"

class BCLeftArm : public Box
{
private:
	D3DXMATRIXA16* ParentWorldMat;
public:
	BCLeftArm();
	~BCLeftArm();

	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXCOLOR color);
	void Update(float delta);
	void Draw(float delta);

	inline void SetParentWorldMatrix(D3DXMATRIXA16* parentWM) { ParentWorldMat = parentWM;}
};

