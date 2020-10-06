#pragma once
#include "Objects.h"

class MyGrid : public Objects_PNT
{
private:
	D3DMATERIAL9 material;
	std::vector<PC_VERTEX> vec_pc_vertices;
public:
	MyGrid();
	~MyGrid();

	void Init(int lineNum, float cellsize);
	void Update(float delta);
	void Draw(float delta);
};

class Pyramid : public Objects
{
public:
	Pyramid();
	~Pyramid();

	void Init(D3DCOLOR color, D3DXMATRIXA16 & rotatemat);
	void Update(float delta);
	void Draw(float delta);
};

class AxisLine : public Objects
{
private:
	std::vector<Pyramid> vec_GizmoVector;
public:
	AxisLine();
	~AxisLine();

	void Init();
	void Update(float delta);
	void Draw(float delta);
};

