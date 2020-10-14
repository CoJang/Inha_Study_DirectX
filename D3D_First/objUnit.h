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

	void Init(char* folder, char* file);
	void Update(float delta);
	void Render(float delta);

	void RePositionVertice();

	void SetScale(float x, float y, float z) { Scale = D3DXVECTOR3(x, y, z); }
	void SetScale(D3DXVECTOR3 scale) { Scale = scale; }

	void SetPos(D3DXVECTOR3 pos) { Position = pos; }
	void SetAngleX(float x) { RotateAngle.x = x; }
	void SetAngleY(float y) { RotateAngle.y = y; }
	void SetAngleZ(float z) { RotateAngle.z = z; }
	void SetAngle(float x, float y, float z) { RotateAngle = D3DXVECTOR3(x, y, z); }
	void SetAngle(D3DXVECTOR3 angle) { RotateAngle = angle; }

	D3DXVECTOR3 GetPos() { return Position; }
	D3DXVECTOR3 GetAngle() { return RotateAngle; }
	float GetAngleX() { return RotateAngle.x; }
	float GetAngleY() { return RotateAngle.y; }
	float GetAngleZ() { return RotateAngle.z; }

	vector<Group*>& GetGroups() { return vecGroup; }
};

