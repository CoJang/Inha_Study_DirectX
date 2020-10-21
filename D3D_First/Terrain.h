#pragma once
#include "ObjectSrc/Objects.h"
class MtlTex;

class Terrain : public Objects_PNT
{
private:
	vector<float> HeightDatas;
	MtlTex mtltex;
public:
	Terrain();
	~Terrain();

	void LoadFromRawFile(char* Path);
	void CreateTerrain(int vertexNum, float cellsize);

	void Update(float delta) override;
	void Draw(float delta) override;
};

