#pragma once
#include "LightSrc/MyLight.h"
//#include "ObjectSrc/Group.h"

class MyGrid;
class AxisLine;
class BoxChar;
class BoxCharBot;
class MyCamera;
class BezierCurve;

class Group;
class objUnit;
class ObjectFrame;

class GameScene
{
public:
	GameScene();
	~GameScene();
	
private:
// temp
	BezierCurve* bc;
	objUnit* objMap;
	objUnit* map_surface;
	D3DXVECTOR3 OldCharPos;
	ObjectFrame* RootFrame;
	
// giomatric objects
	MyGrid* Grid;
	AxisLine* Line;
	
// charactors
	BoxChar* Zemmin2;
	BoxCharBot* Bot_Zemmin2;

// cam
	MyCamera* Camera;
	D3DXVECTOR3* CamPos;
	D3DXVECTOR3* CamTarget;
	D3DXVECTOR3 CamPivot;
	float* CamFov;
	
// light
	DirLight Sun;
	SpotLight FlashLight;
	DotLight Torch;
public:
	void WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	
	void InitGameScene();
	void SetLight();
	void InputCheck(float delta);
	void Update(float delta);
	void Render(float delta);

	float MapCheck(D3DXVECTOR3& charpos, vector<Group*>& terrain);
};

