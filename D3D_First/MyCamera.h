#pragma once

class Box;

class MyCamera
{
private:
	float FOV;
	D3DXVECTOR3 CameraPos;
	D3DXVECTOR3 CameraTarget;
	D3DXVECTOR3 CameraUp;
	D3DXVECTOR3 CameraDirection;
	
	D3DXMATRIXA16 ViewMat;
	D3DXMATRIXA16 ProjMat;

	Box* frustum;
	vector<D3DXVECTOR3> vec_Vertices;
	vector<D3DXPLANE> ViewPlane;
public:
	MyCamera();
	~MyCamera();

	void Init();
	void Update(float delta);
	void Render(float delta);

	D3DXMATRIXA16 GetCameraView() { return ViewMat; }
	D3DXMATRIXA16 GetCameraProjection() { return ProjMat; }

	D3DXVECTOR3* GetCamPos() { return &CameraPos; }
	void SetCamPos(D3DXVECTOR3 pos) { CameraPos = pos; }
	D3DXVECTOR3* GetCamTarget() { return &CameraTarget; }
	void SetCamTarget(D3DXVECTOR3 target) { CameraTarget = target; }
	D3DXVECTOR3* GetCamUp() { return &CameraUp; }
	void SetCamUp(D3DXVECTOR3 up) { CameraUp = up; }
	float* GetCamFov() { return &FOV; }

	void SetCamDir(D3DXVECTOR3 dir) { CameraDirection = dir; }
	D3DXVECTOR3 GetCamDir() { return CameraDirection; }
	vector<D3DXPLANE> GetCamFrustumPlane() { return ViewPlane; }
};

