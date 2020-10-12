#pragma once

class Group;

class objUnit
{
protected:
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 RotateAngle;
	
	vector<Group*> vecGroup;

	D3DXMATRIXA16 ScaleMat;
	D3DXMATRIXA16 RotateMat;
	D3DXMATRIXA16 TransMat;
	D3DXMATRIXA16 WorldMat;
public:
	objUnit();
	~objUnit();

	virtual void Init(char* folder, char* file);
	virtual void Update(float delta);
	virtual void Render(float delta);


	void SetScale(float x, float y, float z) { Scale = D3DXVECTOR3(x, y, z); }
	void SetScale(D3DXVECTOR3 scale) { Scale = scale; }
	void RePositionVertice();

	inline void SetPos(D3DXVECTOR3 pos) { Position = pos; }
	inline void SetAngleX(float x) { RotateAngle.x = x; }
	inline void SetAngleY(float y) { RotateAngle.y = y; }
	inline void SetAngleZ(float z) { RotateAngle.z = z; }
	inline void SetAngle(float x, float y, float z) { RotateAngle = D3DXVECTOR3(x, y, z); }
	inline void SetAngle(D3DXVECTOR3 angle) { RotateAngle = angle; }

	inline D3DXVECTOR3 GetPos() { return Position; }
	inline D3DXVECTOR3 GetAngle() { return RotateAngle; }
	inline float GetAngleX() { return RotateAngle.x; }
	inline float GetAngleY() { return RotateAngle.y; }
	inline float GetAngleZ() { return RotateAngle.z; }

	inline vector<Group*>& GetGroups() { return vecGroup; }
};

