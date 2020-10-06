#include "stdafx.h"
#include "MyLight.h"

MyLight::MyLight()
	:IsLightOn(true)
, Diffuse(0.7f, 0.7f, 0.7f, 1.0f)
, Ambient(0.7f, 0.7f, 0.7f, 1.0f)
, Specular(0.7f, 0.7f, 0.7f, 1.0f)
{
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
{
	ID = index;
	LightSrc.Type = D3DLIGHT_SPOT;
	LightSrc.Position = LightSrcPos;
	LightSrc.Ambient = Ambient;
	LightSrc.Diffuse = Diffuse;
	LightSrc.Specular = Specular;

	D3DXVec3Normalize(&LightSrcDir, &LightSrcDir);

	LightSrc.Direction = LightSrcDir;
	DEVICE->SetLight(ID, &LightSrc);
	DEVICE->LightEnable(ID, IsLightOn);
}

void SpotLight::LightUpdate(float delta)
{
	LightSrc.Position = LightSrcPos;
	LightSrc.Ambient = Ambient;
	LightSrc.Diffuse = Diffuse;
	LightSrc.Specular = Specular;

	D3DXVec3Normalize(&LightSrcDir, &LightSrcDir);

	LightSrc.Direction = LightSrcDir;
	DEVICE->SetLight(ID, &LightSrc);
	DEVICE->LightEnable(ID, IsLightOn);
}

DotLight::DotLight(DWORD index)
	:Range(1.0f)
	,LightSrcPos(0, 0, 0)
	, Attenuation1(0.01f)
	, Attenuation2(0.05f)
{
	ID = index;
	LightSrc.Type = D3DLIGHT_POINT;
	LightSrc.Position = LightSrcPos;
	LightSrc.Ambient = Ambient;
	LightSrc.Diffuse = Diffuse;
	LightSrc.Specular = Specular;
	LightSrc.Range = Range;
	LightSrc.Attenuation1 = Attenuation1;
	LightSrc.Attenuation2 = Attenuation2;

	DEVICE->SetLight(ID, &LightSrc);
	DEVICE->LightEnable(ID, IsLightOn);
}

void DotLight::LightUpdate(float delta)
{
	LightSrc.Position = LightSrcPos;
	LightSrc.Ambient = Ambient;
	LightSrc.Diffuse = Diffuse;
	LightSrc.Specular = Specular;
	LightSrc.Range = Range;
	LightSrc.Attenuation1 = Attenuation1;
	LightSrc.Attenuation2 = Attenuation2;

	DEVICE->SetLight(ID, &LightSrc);
	DEVICE->LightEnable(ID, IsLightOn);
}
