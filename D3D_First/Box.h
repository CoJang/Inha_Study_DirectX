#pragma once
#include "Objects.h"

class Box : public Objects
{
private:
	D3DXVECTOR3 position;
	D3DXVECTOR3 MovePivot;

	int RotateFlag;
	float MaxAngle;
	float Angle;
	int AnimDirection;
public:
	Box();
	~Box();

	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DCOLOR color);
	void Update(float delta);
	void Update(float delta, D3DXMATRIXA16 & worldmat);
	void Draw(float delta);

	inline D3DXVECTOR3 & GetPos() { return position; }
	inline void SetPos(D3DXVECTOR3 & pos) { position = pos; }
	inline void SetPivot(D3DXVECTOR3 pivot) { MovePivot = pivot; }
	inline void SetAngle(float angle, char axis) { Angle = angle; RotateFlag = axis; }
	inline void SetMaxAngle(float angle) { MaxAngle = angle; }
	inline void SetAnimDir(int dir) { AnimDirection = dir; }
	
	inline D3DXMATRIXA16 & GetWorldMat() { return WorldMat; }
};

