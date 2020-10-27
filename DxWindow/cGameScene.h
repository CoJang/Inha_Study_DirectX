#pragma once

class cGameScene
{
private:
	
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

