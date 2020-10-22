#pragma once
#include "ObjectSrc/Objects.h"
class MtlTex;

class Terrain : public Objects_PNT
{
private:
	float** HeightMap;
	MtlTex mtltex;
	float CellSize;
	
// book addition
	unsigned int RowCell, ColCell;
	float Width;
	float Height;
public:
	Terrain();
	~Terrain();

	void LoadFromRawFile(char* Path);
	void CreateTerrain(float cellsize);
	float GetHeight(float x, float z);
	bool GetHeight(OUT D3DXVECTOR3 & pos);

	void Update(float delta) override;
	void Draw(float delta) override;

};

