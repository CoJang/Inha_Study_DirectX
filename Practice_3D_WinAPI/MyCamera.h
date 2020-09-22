#pragma once
class MyCamera
{
private:
	MyVector3 CameraPos;
	MyVector3 CameraTarget;
	MyVector3 CameraUp;
	
	MyMatrix ViewMat;
	MyMatrix ProjMat;
	MyMatrix Viewport_Mat;
public:
	MyCamera();
	~MyCamera();

	void InitCamera(int winWidth, int winHeight);
	void Update(int winWidth, int winHeight);
	void Render();

	inline MyMatrix GetVPVMat() { return ViewMat * ProjMat * Viewport_Mat; }
	inline MyMatrix GetVPMat() { return ViewMat * ProjMat;	}

	inline MyVector3 GetCameraPos() { return CameraPos; }
	inline void SetCameraPos(MyVector3 pos) { CameraPos = pos; }
	inline void SetTarget(MyVector3 pos) { CameraTarget = pos; }
};

