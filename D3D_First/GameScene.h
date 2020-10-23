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
class MySphere;
class Terrain;

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
	MySphere* sphere;
	Terrain* TR;
	SkyBox* Sky;
	
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
	Ray CalcPickingRay(POINT MPos);
	bool IsRayHitInSphere(Ray & ray, MySphere & sphere);
	void GridRayHitProcess(Ray & ray);
	bool IsMeshSphereCulled(MySphere & mesh);
};

class MySphere
{
private:
	LPD3DXMESH Mesh;
	D3DMATERIAL9 Material;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Scale;
	float Radius;
	LPDIRECT3DTEXTURE9* texture;

	bool IsCulled;
public:
	MySphere();
	~MySphere();

	void Update(float delta);
	void Render(float delta);

	void LoadTexture(char* Path);
	void SetMaterial(D3DMATERIAL9 mtl) { Material = mtl; }
	void SetScale(float x, float y, float z) { Scale = D3DXVECTOR3(x, y, z); }
	void SetMaterialColor(D3DXCOLOR color);
	void SetPosition(D3DXVECTOR3 pos) { Position = pos; }
	D3DXVECTOR3 GetPosition() { return Position; }
	float GetRadius() { return Radius; }
	bool GetState() { return IsCulled; }
	void SetState(bool state) { IsCulled = state; }
};

