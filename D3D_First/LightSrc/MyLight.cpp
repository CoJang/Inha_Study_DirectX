#include "stdafx.h"
#include "MyLight.h"

MyLight::MyLight()
	:IsLightOn(true)
, Diffuse(0.7f, 0.7f, 0.7f, 1.0f)
, Ambient(0.7f, 0.7f, 0.7f, 1.0f)
, Specular(0.7f, 0.7f, 0.7f, 1.0f)
{
	ZeroMemory(&LightSrc, sizeof(D3DLIGHT9));
}

DirLight::DirLight(DWORD index)
{
	ID = index;
	LightSrc.Type = D3DLIGHT_DIRECTIONAL;
	LightSrc.Ambient = Ambient;
	LightSrc.Diffuse = Diffuse;
	LightSrc.Specular = Specular;

	D3DXVec3Normalize(&LightSrcDir, &LightSrcDir);

	LightSrc.Direction = LightSrcDir;
	DEVICE->SetLight(ID, &LightSrc);
	DEVICE->LightEnable(ID, IsLightOn);
}

void DirLight::LightUpdate(float delta)
{
	LightSrc.Ambient = Ambient;
	LightSrc.Diffuse = Diffuse;
	LightSrc.Specular = Specular;

	D3DXVec3Normalize(&LightSrcDir, &LightSrcDir);

	LightSrc.Direction = LightSrcDir;
	DEVICE->SetLight(ID, &LightSrc);
	DEVICE->LightEnable(ID, IsLightOn);
}

SpotLight::SpotLight(DWORD index)
	:Range(5.0f)
	, LightSrcPos(0, 1, 0)
	, LightSrcDir(0, 1, 0)
{
	ID = index;
	LightSrc.Type = D3DLIGHT_SPOT;
	LightSrc.Position = LightSrcPos;
	LightSrc.Ambient = Ambient;
	LightSrc.Diffuse = Diffuse;
	LightSrc.Specular = Specular;
	LightSrc.Range = Range;

	LightSrc.Attenuation2 = 0.05f;
	LightSrc.Phi = PI / 2;
	LightSrc.Theta = PI / 4;

	D3DXVec3Normalize(&LightSrcDir, &LightSrcDir);

	LightSrc.Direction = LightSrcDir;
	DEVICE->SetLight(ID, &LightSrc);
	DEVICE->LightEnable(ID, IsLightOn);

	Gizmo.Init(LightSrcPos, D3DXVECTOR3(0.3f, 0.3f, 0.3f), D3DXCOLOR(1, 1, 1, 1));
}

void SpotLight::LightUpdate(float delta)
{
	LightSrc.Position = LightSrcPos;
	LightSrc.Ambient = Ambient;
	LightSrc.Diffuse = Diffuse;
	LightSrc.Specular = Specular;
	LightSrc.Range = Range;

	D3DXVec3Normalize(&LightSrcDir, &LightSrcDir);
	LightSrc.Direction = LightSrcDir;

	DEVICE->SetLight(ID, &LightSrc);
	DEVICE->LightEnable(ID, IsLightOn);

	Gizmo.SetPos(LightSrcPos);
}

void SpotLight::DrawGizmo(float delta)
{
	Gizmo.Update(delta);
	Gizmo.Draw(delta);
}

DotLight::DotLight(DWORD index)
	:Range(1.0f)
	,LightSrcPos(0, 0, 0)
	, Attenuation0(0.1f)
	, Attenuation1(0.1f)
	, Attenuation2(0.15f)
{
	ID = index;
	LightSrc.Type = D3DLIGHT_POINT;
	LightSrc.Position = LightSrcPos;
	LightSrc.Ambient = Ambient;
	LightSrc.Diffuse = Diffuse;
	LightSrc.Specular = Specular;
	LightSrc.Range = Range;
	LightSrc.Attenuation0 = Attenuation0;
	LightSrc.Attenuation1 = Attenuation1;
	LightSrc.Attenuation2 = Attenuation2;

	DEVICE->SetLight(ID, &LightSrc);
	DEVICE->LightEnable(ID, IsLightOn);

	Gizmo.Init(LightSrcPos, D3DXVECTOR3(0.3f, 0.3f, 0.3f), D3DXCOLOR(1, 1, 1, 1));
}

void DotLight::LightUpdate(float delta)
{
	LightSrc.Position = LightSrcPos;
	LightSrc.Ambient = Ambient;
	LightSrc.Diffuse = Diffuse;
	LightSrc.Specular = Specular;
	LightSrc.Range = Range;
	LightSrc.Attenuation0 = Attenuation0;
	LightSrc.Attenuation1 = Attenuation1;
	LightSrc.Attenuation2 = Attenuation2;

	DEVICE->SetLight(ID, &LightSrc);
	DEVICE->LightEnable(ID, IsLightOn);

	Gizmo.SetPos(LightSrcPos);
}

void DotLight::DrawGizmo(float delta)
{
	Gizmo.Update(delta);
	Gizmo.Draw(delta);
}
