#pragma once

class Objects
{
protected:
	std::vector<PC_VERTEX> vec_Vertexs;

	D3DXMATRIXA16 ScaleMat;
	D3DXMATRIXA16 RotateMat;
	D3DXMATRIXA16 TransMat;
	D3DXMATRIXA16 WorldMat;
public:
	Objects();
	virtual ~Objects();

	virtual	void Init() = 0;
	virtual void Update(float delta) = 0;
	virtual void Draw(float delta) = 0;
};

