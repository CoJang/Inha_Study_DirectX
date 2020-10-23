#pragma once

class cPyramid;

class cGrid
{
private:
	vector<ST_PC_VERTEX> m_vecVertex;
	vector<cPyramid*> m_vecPyramid;

	D3DMATERIAL9 m_matrial;


public:
	cGrid();
	~cGrid();

	void Setup(int nNumHarfTile = 15, float fInterval = 1.0f);
	void Render();

};

