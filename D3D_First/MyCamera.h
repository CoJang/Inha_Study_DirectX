#pragma once

class MyCamera
{
private:
	float FOV;
	D3DXVECTOR3 CameraPos;
	D3DXVECTOR3 CameraTarget;
	D3DXVECTOR3 CameraUp;
	
	D3DXMATRIXA16 ViewMat;
	D3DXMATRIXA16 ProjMat;
public:
	MyCamera();
	~MyCamera();

	void Init();
	void Update(float delta);

	inline D3DXMATRIXA16 GetCameraView() { return ViewMat; }
	inline D3DXMATRIXA16 GetCameraProjection() { return ProjMat; }

	inline D3DXVECTOR3* GetCamPos() { return &CameraPos; }
	inline void SetCamPos(D3DXVECTOR3 pos) { CameraPos = pos; }
	inline D3DXVECTOR3* GetCamTarget() { return &CameraTarget; }
	inline void SetCamTarget(D3DXVECTOR3 target) { CameraTarget = target; }
	inline D3DXVECTOR3* GetCamUp() { return &CameraUp; }
	inline void SetCamUp(D3DXVECTOR3 up) { CameraUp = up; }
	inline float* GetCamFov() { return &FOV; }
};

