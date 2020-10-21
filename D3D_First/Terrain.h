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

	void Update(float delta) override;
	void Draw(float delta) override;
	
	float GetHeightData(float row, float col);
	void SetHeightData(float row, float col, int height);
};

