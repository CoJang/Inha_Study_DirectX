#include "framework.h"
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
	g_pDevice->SetTransform(D3DTS_VIEW, &ViewMat);
	
	D3DXMatrixPerspectiveFovLH(&ProjMat, FOV, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	g_pDevice->SetTransform(D3DTS_PROJECTION, &ProjMat);

	D3DVIEWPORT9 viewport;
	g_pDevice->GetViewport(&viewport);
}

void MyCamera::Update(float delta)
{
	CameraDirection = CameraTarget - CameraPos;
	D3DXVec3Normalize(&CameraDirection, &CameraDirection);
	
	D3DXMatrixLookAtLH(&ViewMat, &CameraPos, &CameraTarget, &CameraUp);
	g_pDevice->SetTransform(D3DTS_VIEW, &ViewMat);
}

void MyCamera::UpdateFrustum()
{

}

void MyCamera::Render(float delta)
{
}
