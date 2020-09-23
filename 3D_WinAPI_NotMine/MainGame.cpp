#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
	: BitmapImage(NULL)
	, CameraPos(0, 0, -5)
	, LookAt(0, 0, 0)
	, CameraUp(0, 1, 0)
{
}


MainGame::~MainGame()
{
	SelectObject(FrontBuffer, OldBitmapImage);
	DeleteObject(BitmapImage);
	DeleteDC(FrontBuffer);
}

void MainGame::InitMainGame()
{
	HDC hdc = GetDC(g_hwnd);
	FrontBuffer = CreateCompatibleDC(hdc);

	RECT rc;
	GetClientRect(g_hwnd, &rc);

	BitmapImage = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
	OldBitmapImage = (HBITMAP)SelectObject(FrontBuffer, BitmapImage);
	ReleaseDC(g_hwnd, hdc);
	
#pragma region [Vertex Init]
//박스 위치
	vec_Vertex.push_back(MyVector3(-1.0f, -1.0f, 1.0f));
	vec_Vertex.push_back(MyVector3(-1.0f, 1.0f, 1.0f));
	vec_Vertex.push_back(MyVector3(1.0f, 1.0f, 1.0f));
	vec_Vertex.push_back(MyVector3(1.0f, -1.0f, 1.0f));

	vec_Vertex.push_back(MyVector3(-1.0f, -1.0f, -1.0f));
	vec_Vertex.push_back(MyVector3(-1.0f, 1.0f, -1.0f));
	vec_Vertex.push_back(MyVector3(1.0f, 1.0f, -1.0f));
	vec_Vertex.push_back(MyVector3(1.0f, -1.0f, -1.0f));
	
// front
	vec_Index.push_back(0);
	vec_Index.push_back(1);
	vec_Index.push_back(2);

	vec_Index.push_back(0);
	vec_Index.push_back(2);
	vec_Index.push_back(3);
// back [ 바깥에서 보았을 때 시계방향 ]
	vec_Index.push_back(4);
	vec_Index.push_back(6);
	vec_Index.push_back(5);

	vec_Index.push_back(4);
	vec_Index.push_back(7);
	vec_Index.push_back(6);
// left
	vec_Index.push_back(4);
	vec_Index.push_back(5);
	vec_Index.push_back(1);

	vec_Index.push_back(4);
	vec_Index.push_back(1);
	vec_Index.push_back(0);
// right
	vec_Index.push_back(3);
	vec_Index.push_back(2);
	vec_Index.push_back(6);

	vec_Index.push_back(3);
	vec_Index.push_back(6);
	vec_Index.push_back(7);
// top
	vec_Index.push_back(1);
	vec_Index.push_back(5);
	vec_Index.push_back(6);

	vec_Index.push_back(1);
	vec_Index.push_back(6);
	vec_Index.push_back(2);
// bottom
	vec_Index.push_back(4);
	vec_Index.push_back(0);
	vec_Index.push_back(3);

	vec_Index.push_back(4);
	vec_Index.push_back(3);
	vec_Index.push_back(7);
#pragma endregion [Vertex Init]

	WorldMat = MyMatrix::Identity(4);
	ViewMat = MyMatrix::Identity(4);
	ProjMat = MyMatrix::Identity(4);
	ViewportMat = MyMatrix::Identity(4);
}

bool MainGame::IsBackFace(MyVector3& v1, MyVector3& v2, MyVector3& v3)
{
	MyVector3 v12 = v2 - v1;
	MyVector3 v13 = v3 - v1;
	MyVector3 NormalVector = MyVector3::Cross(v12, v13);

	// 이미 Projection 변환까지 이루어져있다면, z+ 방향이 곧 바라보는 방향이다.
	if (MyVector3::Dot(NormalVector, MyVector3(0, 0, 1)) <= 0.f)
		return true;
	else
		return false;
	
}

void MainGame::Update()
{
	RECT rc;
	GetClientRect(g_hwnd, &rc);
	CameraPos = MyVector3(0, 5, -5);
	LookAt = MyVector3(0, 0, 0);
	CameraUp = MyVector3(0, 1, 0);

	ViewMat = MyMatrix::View(CameraPos, LookAt, CameraUp);
	ProjMat = MyMatrix::Projection(90, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	ViewportMat = MyMatrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);
}

void MainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hwnd, &rc);

	// 흰색 배경으로 초기화
	PatBlt(FrontBuffer, rc.left, rc.top, rc.right, rc.bottom, WHITENESS);

	MyMatrix WVP_Mat = WorldMat * ViewMat * ProjMat;

	for(int i = 0; i < vec_Index.size(); i += 3)
	{
		MyVector3 v1 = vec_Vertex[vec_Index[i + 0]];
		MyVector3 v2 = vec_Vertex[vec_Index[i + 1]];
		MyVector3 v3 = vec_Vertex[vec_Index[i + 2]];

		v1 = MyVector3::TransformCoord(v1, WVP_Mat);
		v2 = MyVector3::TransformCoord(v2, WVP_Mat);
		v3 = MyVector3::TransformCoord(v3, WVP_Mat);

		if (IsBackFace(v1, v2, v3)) continue;

		v1 = MyVector3::TransformCoord(v1, ViewportMat);
		v2 = MyVector3::TransformCoord(v2, ViewportMat);
		v3 = MyVector3::TransformCoord(v3, ViewportMat);

		MoveToEx(FrontBuffer, v1.x, v1.y, NULL);
		LineTo(FrontBuffer, v2.x, v2.y);
		LineTo(FrontBuffer, v3.x, v3.y);
		LineTo(FrontBuffer, v1.x, v1.y);
	}
	
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, FrontBuffer, 0, 0, SRCCOPY);
}

void MainGame::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch(Msg)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_MOUSEHWHEEL:
		break;
	default:
		break;
	}
}
