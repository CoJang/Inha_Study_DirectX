#include "stdafx.h"
#include "MyCamera.h"


MyCamera::MyCamera()
	: CameraPos(0, 10, -5)
	, CameraTarget(0, 0, 0)
	, CameraUp(0, 1, 0)
{
	ViewMat = MyMatrix::Identity(4);
	ProjMat = MyMatrix::Identity(4);
	Viewport_Mat = MyMatrix::Identity(4);
}


MyCamera::~MyCamera()
{
}

void MyCamera::InitCamera(int winWidth, int winHeight)
{
	ViewMat = MyMatrix::View(CameraPos, CameraTarget, CameraUp);
	ProjMat = MyMatrix::Projection(90, winWidth / (float)winHeight, 1, 1000);
	Viewport_Mat = MyMatrix::Viewport(0, 0, winWidth, winHeight, 0, 1);
}

void MyCamera::Update(int winWidth, int winHeight)
{
	ViewMat = MyMatrix::View(CameraPos, CameraTarget, CameraUp);
	ProjMat = MyMatrix::Projection(90, winWidth / (float)winHeight, 1, 1000);
	Viewport_Mat = MyMatrix::Viewport(0, 0, winWidth, winHeight, 0, 1);
}

void MyCamera::Render()
{
	
}
