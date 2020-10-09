#pragma once
#include "../ObjectSrc/Box.h"

class MyLight
{
protected:
	DWORD ID;
	D3DLIGHT9 LightSrc;
	
	D3DXCOLOR Ambient;
	D3DXCOLOR Diffuse;
	D3DXCOLOR Specular;

	bool IsLightOn;
public:
	MyLight();
	virtual ~MyLight() = default;

	virtual void LightUpdate(float delta) {};

	inline bool GetLightState() { return IsLightOn; }
	inline void SetLightState(bool state) { IsLightOn = state; }
	inline void SetDiffuseColor(D3DXCOLOR color) { Diffuse = color; }
	inline void SetAmbientColor(D3DXCOLOR color) { Ambient = color; }
	inline void SetSpecularColor(D3DXCOLOR color) { Specular = color; }
};

class DirLight : public MyLight
{
private:
	D3DXVECTOR3 LightSrcDir;

public:
	DirLight(DWORD index);
	~DirLight() = default;

	void LightUpdate(float delta) override;
	
	inline void SetDirection(D3DXVECTOR3 dir) { LightSrcDir = dir; }
	inline D3DXVECTOR3 GetDirection() { return LightSrcDir; }
};

class SpotLight : public MyLight
{
private:
	D3DXVECTOR3 LightSrcDir;
	D3DXVECTOR3 LightSrcPos;
	float Range;

	Box Gizmo;
public:
	SpotLight(DWORD index);
	~SpotLight() = default;

	void LightUpdate(float delta) override;
	void DrawGizmo(float delta);

	inline D3DXVECTOR3 GetDirection() { return LightSrcDir; }
	inline void SetDirection(D3DXVECTOR3 dir) { LightSrcDir = dir; }
	
	inline D3DXVECTOR3 GetPosition() { return LightSrcPos; }
	inline void SetPosition(D3DXVECTOR3 pos) { LightSrcPos = pos; }

	inline float GetRange() { return Range; }
	inline void SetRange(float range) { Range = range; }
};

class DotLight : public MyLight
{
private:
	D3DXVECTOR3 LightSrcPos;
	float Range;

	float Attenuation0;
	float Attenuation1;
	float Attenuation2;

	Box Gizmo;
public:
	DotLight(DWORD index);
	~DotLight() = default;

	void LightUpdate(float delta);
	void DrawGizmo(float delta);

	inline D3DXVECTOR3 GetPosition() { return LightSrcPos; }
	inline void SetPosition(D3DXVECTOR3 pos) { LightSrcPos = pos; }

	inline float GetRange() { return Range; }
	inline void SetRange(float range) { Range = range; }
};