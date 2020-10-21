#include "stdafx.h"
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
	 CameraPos = D3DXVECTOR3(0, 10, 15.0f);
	 CameraTarget = D3DXVECTOR3(0, 0, 0);
	 CameraUp = D3DXVECTOR3(0, 1, 0);
	 CameraDirection = CameraTarget - CameraPos;
	 D3DXVec3Normalize(&CameraDirection, &CameraDirection);
	
	 RECT rc;
	 GetClientRect(g_hwnd, &rc);
	 D3DXMatrixPerspectiveFovLH(&ProjMat, FOV, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	 DEVICE->SetTransform(D3DTS_PROJECTION, &ProjMat);
}

void MyCamera::Update(float delta)
{
	CameraDirection = CameraTarget - CameraPos;
	D3DXVec3Normalize(&CameraDirection, &CameraDirection);
	
	D3DXMatrixLookAtLH(&ViewMat, &CameraPos, &CameraTarget, &CameraUp);
	DEVICE->SetTransform(D3DTS_VIEW, &ViewMat);
}
