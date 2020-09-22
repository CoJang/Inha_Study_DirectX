#include "stdafx.h"
#include "MyCamera.h"
#include "MyCube.h"
#include "MyGrid.h"
#include "GameScene.h"


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
	delete Grid;
	delete Cube;
	delete Camera;
	
	SelectObject(FrontBuffer, OldImageBuffer);
	DeleteObject(ImageBuffer);
	DeleteDC(FrontBuffer);
}

void GameScene::InitGameScene(HWND hwnd)
{
	hWnd = hwnd;
	HDC hdc = GetDC(hWnd);
	FrontBuffer = CreateCompatibleDC(hdc);
	
	GetClientRect(hWnd, &rc);

	ImageBuffer = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
	OldImageBuffer = (HBITMAP)SelectObject(FrontBuffer, ImageBuffer);

	ReleaseDC(hWnd, hdc);

	Camera = new MyCamera;
	Camera->InitCamera(rc.right, rc.bottom);
	Camera->SetCameraPos({ 0, 10,-15 });

	Grid = new MyGrid;
	Grid->InitGrid();
	Cube = new MyCube;
	Cube->InitCube(0, 3, 0, 3);
}

void GameScene::Update()
{
	GetClientRect(hWnd, &rc);

	Cube->Update(Camera->GetVPVMat());
	Grid->Update();
	
	Camera->SetTarget(Cube->GetPos());
	Camera->Update(rc.right, rc.bottom);
}

void GameScene::Render(HDC hdc)
{
	PatBlt(FrontBuffer, rc.left, rc.top, rc.right, rc.bottom, WHITENESS);

	Cube->Render(FrontBuffer);
	Grid->Render(FrontBuffer, Camera->GetVPVMat());
		
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, FrontBuffer, 0, 0, SRCCOPY);
}

void GameScene::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	static bool IsClicked = false;
	
	switch (Msg)
	{
	case WM_LBUTTONDOWN:
		IsClicked = true;
		OldMousePos.x = LOWORD(lParam);
		OldMousePos.y = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		IsClicked = false;
		break;
	case WM_MOUSEMOVE:
		if(IsClicked)
		{
			MousePos.x = LOWORD(lParam);
			MousePos.y = HIWORD(lParam);
			MyVector3 MoveCamPos = Camera->GetCameraPos();
			MyMatrix RotateMat = MyMatrix::Identity(4);
			float Angle = 1.0f;
			POINT Gap = { abs(OldMousePos.x - MousePos.x), abs(OldMousePos.y - MousePos.y) };

			if(Gap.x > Gap.y)
			{
				if (OldMousePos.x > MousePos.x)
				{
					RotateMat = MyMatrix::RotationY(-Angle);
					MoveCamPos = MyVector3::TransformCoord(MoveCamPos, RotateMat);
					Camera->SetCameraPos(MoveCamPos);
				}
				else
				{
					RotateMat = MyMatrix::RotationY(Angle);
					MoveCamPos = MyVector3::TransformCoord(MoveCamPos, RotateMat);
					Camera->SetCameraPos(MoveCamPos);
				}
			}
			else
			{
				if (OldMousePos.y > MousePos.y)
				{
					RotateMat = MyMatrix::RotationX(Angle);
					MoveCamPos = MyVector3::TransformCoord(MoveCamPos, RotateMat);
					Camera->SetCameraPos(MoveCamPos);
				}
				else
				{
					RotateMat = MyMatrix::RotationX(-Angle);
					MoveCamPos = MyVector3::TransformCoord(MoveCamPos, RotateMat);
					Camera->SetCameraPos(MoveCamPos);
				}
			}
		}
		OldMousePos.x = LOWORD(lParam);
		OldMousePos.y = HIWORD(lParam);
		break;
	case WM_MOUSEWHEEL:
		{
			short Input = HIWORD(wParam);
			Input /= 120;
			MyVector3 MoveCamPos = Camera->GetCameraPos();
			MoveCamPos.y += Input;
			
			Camera->SetCameraPos(MoveCamPos);
		}
		break;
	default:
		break;
	}
}
