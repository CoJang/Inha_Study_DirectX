#pragma once

class MyGrid;
class AxisLine;
class Box;
class MyCamera;

class GameScene
{
public:
	GameScene();
	~GameScene();
	
private:
	MyCamera* Camera;
	Box* MovingBox;
	MyGrid* Grid;
	AxisLine* Line;

	D3DXVECTOR3* CamPos;
	D3DXVECTOR3* CamTarget;
	float* CamFov;
public:
	void WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	
	void InitGameScene();
	void Update(float delta);
	void Render(float delta);
};

