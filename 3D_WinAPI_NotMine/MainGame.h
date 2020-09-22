#pragma once
class MainGame
{
private:
	HDC FrontBuffer;

	HBITMAP BitmapImage;
	HBITMAP OldBitmapImage;

	std::vector<MyVector3> vec_Vertex;
	std::vector<DWORD> vec_Index;

	MyMatrix WorldMat;
	MyMatrix ViewMat;
	MyMatrix ProjMat;
	MyMatrix ViewportMat;

	MyVector3 CameraPos;
	MyVector3 LookAt;
	MyVector3 CameraUp;
public:
	MainGame();
	~MainGame();

	void InitMainGame();
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
};

