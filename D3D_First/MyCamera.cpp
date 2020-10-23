#include "stdafx.h"
#include "ObjectSrc/Box.h"
#include "MyCamera.h"


MyCamera::MyCamera()
	:FOV(45.0f)
{
}


MyCamera::~MyCamera()
{
}

void MyCamera::Init()
{
	CameraPos = D3DXVECTOR3(0, 10, -15.0f);
	CameraTarget = D3DXVECTOR3(0, 0, 0);
	CameraUp = D3DXVECTOR3(0, 1, 0);
	CameraDirection = CameraTarget - CameraPos;
	D3DXVec3Normalize(&CameraDirection, &CameraDirection);
	
	RECT rc;
	GetClientRect(g_hwnd, &rc);
	D3DXMatrixLookAtLH(&ViewMat, &CameraPos, &CameraTarget, &CameraUp);
	DEVICE->SetTransform(D3DTS_VIEW, &ViewMat);
	
	D3DXMatrixPerspectiveFovLH(&ProjMat, FOV, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &ProjMat);

	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);
	
	frustum = new Box;
	frustum->Init(CameraPos, D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1,1,1,1));
	auto v = frustum->GetVertice();
	vec_Vertices.resize(v.size());
	ViewPlane.resize(6);
	
	for(int i = 0; i < v.size(); i++)
	{
		D3DXVec3Unproject(&vec_Vertices[i], &v[i].p, NULL, &ProjMat, &ViewMat, NULL);
	}
	
	for(int i = 0; i < v.size(); i += 6)
	{
		D3DXPlaneFromPoints(&ViewPlane[i / 6], &vec_Vertices[i], &vec_Vertices[i + 1], &vec_Vertices[i + 2]);
	}
}

void MyCamera::Update(float delta)
{
	CameraDirection = CameraTarget - CameraPos;
	D3DXVec3Normalize(&CameraDirection, &CameraDirection);
	
	D3DXMatrixLookAtLH(&ViewMat, &CameraPos, &CameraTarget, &CameraUp);
	DEVICE->SetTransform(D3DTS_VIEW, &ViewMat);

	auto v = frustum->GetVertice();
	for (int i = 0; i < v.size(); i++)
	{
		D3DXVec3Unproject(&vec_Vertices[i], &v[i].p, NULL, &ProjMat, &ViewMat, NULL);
	}

	for (int i = 0; i < v.size(); i += 6)
	{
		D3DXPlaneFromPoints(&ViewPlane[i / 6], &vec_Vertices[i], &vec_Vertices[i + 1], &vec_Vertices[i + 2]);
	}
}

void MyCamera::Render(float delta)
{
	frustum->Draw(delta);
}
