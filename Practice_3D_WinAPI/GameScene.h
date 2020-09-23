#pragma once

class MyCamera;
class MyCube;
class MyGrid;

class GameScene
{
private:
	MyCamera* Camera;
	MyCube* Cube;
	MyGrid* Grid;

	HBITMAP ImageBuffer;
	HBITMAP OldImageBuffer;
	
	HDC FrontBuffer;
	HWND hWnd;

	RECT rc;
	POINT MousePos;
	POINT OldMousePos;

	MyVector3* CamPos;
	MyVector3* CamTarget;
	MyVector3* CamUp;
public:
	GameScene();
	~GameScene();

	void InitGameScene(HWND hwnd);
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
};

