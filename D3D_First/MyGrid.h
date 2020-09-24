#pragma once
#include "Objects.h"

class MyGrid : public Objects
{
public:
	MyGrid();
	~MyGrid();

	void Init();
	void Update(float delta);
	void Draw(float delta);
};

class AxisLine : public Objects
{
public:
	AxisLine();
	~AxisLine();

	void Init();
	void Update(float delta);
	void Draw(float delta);
};

