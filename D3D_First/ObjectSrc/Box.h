#pragma once
#include "../ObjectNode.h"

class Box : public ObjectNode
{
protected:
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 MovePivot;
	D3DXVECTOR3 RotateAngle;
	D3DMATERIAL9 material;

	int RotateFlag;
	float MaxAngle;
	int AnimDirection;
public:
	Box();
	~Box();

	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXCOLOR color);
	void Update(float delta);
	void Update(float delta, D3DXMATRIXA16 & worldmat);
	void Draw(float delta);

	inline D3DXVECTOR3 & GetPos() { return Position; }
	inline void SetPos(D3DXVECTOR3 & pos) { Position = pos; }
	inline void SetPivot(D3DXVECTOR3 pivot) { MovePivot = pivot; }
	inline void SetMaxAngle(float angle) { MaxAngle = angle; }
	inline void SetAnimDir(int dir) { AnimDirection = dir; }
	
	inline void SetAngleX(float x) { RotateAngle.x = x; }
	inline void SetAngleY(float y) { RotateAngle.y = y; }
	inline void SetAngleZ(float z) { RotateAngle.z = z; }
	inline void SetAngle(float x, float y, float z) { RotateAngle = D3DXVECTOR3(x, y, z); }
	inline void SetAngle(D3DXVECTOR3 angle) { RotateAngle = angle; }

	inline D3DXVECTOR3 GetAngle() { return RotateAngle; }
	inline float GetAngleX() { return RotateAngle.x; }
	inline float GetAngleY() { return RotateAngle.y; }
	inline float GetAngleZ() { return RotateAngle.z; }
	
	inline D3DXMATRIXA16 & GetWorldMat() { return WorldMat; }
};