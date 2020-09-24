#pragma once
#include "Objects.h"

class Box : public Objects
{
private:
	D3DXVECTOR3 position;
	D3DXVECTOR3 posVertex;
	D3DXVECTOR3 dir;
	float		velocity;
	float		angle;
public:
	Box();
	~Box();

	void Init();
	void Update(float delta);
	void Draw(float delta);

	inline D3DXVECTOR3 GetPos() { return position; }
};

