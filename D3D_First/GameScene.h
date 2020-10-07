#pragma once

class MyGrid;
class AxisLine;
class BoxChar;
class MyCamera;
class BezierCurve;

#include "MyLight.h"

class GameScene
{
public:
	GameScene();
	~GameScene();
	
private:
// temp
	vector<PNT_VERTEX> loadeddata;
	D3DMATERIAL9 loadedmaterial;
	LPDIRECT3DTEXTURE9 loadedtexture;
	BezierCurve* bc;
	
// giomatric objects
	MyGrid* Grid;
	AxisLine* Line;
	
// charactors
	BoxChar* Zemmin2;
	BoxChar* Bot_Zemmin2;

// cam
	MyCamera* Camera;
	D3DXVECTOR3* CamPos;
	D3DXVECTOR3* CamTarget;
	float* CamFov;
	
// light
	DirLight Sun;
	SpotLight FlashLight;
	DotLight Torch;
public:
	void WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	
	void InitGameScene();
	void SetLight();
	void Update(float delta);
	void Render(float delta);
};

