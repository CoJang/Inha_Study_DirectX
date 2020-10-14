#pragma once
#include "Objects.h"

class MyGrid : public Objects_PNT
{
private:
	D3DMATERIAL9 material;
	std::vector<PC_VERTEX> vec_pc_vertices;
public:
	MyGrid() = default;
	~MyGrid() = default;

	void Init(int lineNum, float cellsize);
	void Update(float delta) {};
	void Draw(float delta);
};

class Pyramid : public Objects_PC
{
public:
	Pyramid() = default;
	~Pyramid() = default;

	void Init(D3DCOLOR color, D3DXMATRIXA16 & rotatemat);
	void Update(float delta) {};
	void Draw(float delta);
};

class AxisLine : public Objects_PC
{
private:
	std::vector<Pyramid> vec_GizmoVector;
public:
	AxisLine() = default;
	~AxisLine() = default;

	void Init();
	void Update(float delta) {};
	void Draw(float delta);
};

class BezierCurve : public Objects_PC
{
	std::vector<PC_VERTEX> vec_Straight;
public:
	BezierCurve() = default;
	~BezierCurve() = default;

	void Init();
	void Update(float delta) {};
	void Draw(float delta);

	inline vector<PC_VERTEX> & GetVertexList() { return vec_Vertexs; }
};

