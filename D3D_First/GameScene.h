#pragma once

class MyGrid;
class AxisLine;
class BoxChar;
class MyCamera;

class GameScene
{
public:
	GameScene();
	~GameScene();
	
private:
	MyCamera* Camera;
	BoxChar* Zemmin2;
	MyGrid* Grid;
	AxisLine* Line;

	LPDIRECT3DTEXTURE9 m_pTexture;
	std::vector<PT_VERTEX> vec_Vertex;
	

	D3DXVECTOR3* CamPos;
	D3DXVECTOR3* CamTarget;
	float* CamFov;
public:
	void WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	
	void InitGameScene();
	void SetLight();
	void Update(float delta);
	void Render(float delta);

	void DrawTexture(float delta);
};

