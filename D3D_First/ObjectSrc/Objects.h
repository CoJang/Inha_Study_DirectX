#pragma once

class Objects_PC
{
protected:
	std::vector<PC_VERTEX> vec_Vertexs;

	D3DXMATRIXA16 ScaleMat;
	D3DXMATRIXA16 RotateMat;
	D3DXMATRIXA16 TransMat;
	D3DXMATRIXA16 WorldMat;
public:
	Objects_PC();
	virtual ~Objects_PC();

	virtual	void Init() {}
	virtual void Update(float delta) = 0;
	virtual void Draw(float delta) = 0;
};

class Objects_PNT
{
protected:
	std::vector<PNT_VERTEX> vec_Vertexs;
public:
	Objects_PNT();
	virtual ~Objects_PNT();

	virtual	void Init() {}
	virtual void Update(float delta) = 0;
	virtual void Draw(float delta);
};