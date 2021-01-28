#pragma once

class MyGrid;
class MyCamera;
class cBox;

class cGameScene
{
private:
	MyGrid* m_pGrid;
	MyCamera* m_pCamera;
	cBox* m_pBox;
public:
// Basic Func
	cGameScene();
	~cGameScene();

	void InitGameScene();
	void WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	void Update(float delta);
	void Render(float delta);
//
};

