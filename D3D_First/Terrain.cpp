#include "stdafx.h"
#include "ObjectSrc/MtlTex.h"
#include "Terrain.h"


Terrain::Terrain()
	:CellSize(0)
	, RowCell(0)
	, ColCell(0)
	, Width(0)
	, Height(0)
{
	
}


Terrain::~Terrain()
{
	delete[] HeightMap;
}

void Terrain::LoadFromRawFile(char* Path)
{
	FILE* SrcFile;
	fopen_s(&SrcFile, Path, "rb");
	
	if(SrcFile == NULL)
	{
		cout << "LoadFromRawFile " << Path << " Failed!" << endl;
		return;
	}

	vector<float> HeightDatas;
	
	while(true)
	{
		if (feof(SrcFile)) break;
		unsigned int height = (unsigned)fgetc(SrcFile);
		HeightDatas.push_back(height / 10.0f);
	}
	fclose(SrcFile);

	RowCell = sqrt(HeightDatas.size());
	ColCell = HeightDatas.size() / RowCell;

	if(RowCell != ColCell)
	{
		if(HeightDatas.size() == 640 * 480)
		{
			RowCell = 640; ColCell = 480;
		}
		else if (HeightDatas.size() == 176 * 144)
		{
			RowCell = 176; ColCell = 144;
		}
		else if (HeightDatas.size() == 176 * 216)
		{
			RowCell = 176; ColCell = 216;
		}
		else if (HeightDatas.size() == 1920 * 1080)
		{
			RowCell = 1920; ColCell = 1080;
		}
		else if (HeightDatas.size() == 2560 * 1440)
		{
			RowCell = 2560; ColCell = 1440;
		}
		else
		{
			cout << "RAW Image Size Not Supported" << endl;
			RowCell = 0; ColCell = 0;
		}
			
	}
	
	HeightMap = new float* [ColCell];

	for (int i = 0; i < ColCell; i++)
	{
		HeightMap[i] = new float[RowCell];

		for (int j = 0; j < RowCell; j++)
		{
			HeightMap[i][j] = HeightDatas[j + (i * RowCell)];
		}
	}

	CreateTerrain(1.0f);
}

void Terrain::CreateTerrain(float cellsize)
{
	CellSize = cellsize;
	Width = RowCell * CellSize;
	Height = ColCell * CellSize;
	
	PNT_VERTEX v0, v1, v2, v3;
	v0.n = D3DXVECTOR3(0, 1, 0);
	v1.n = D3DXVECTOR3(0, 1, 0);
	v2.n = D3DXVECTOR3(0, 1, 0);
	v3.n = D3DXVECTOR3(0, 1, 0);

	float RowIdx = RowCell - 1.0f;
	float ColIdx = ColCell - 1.0f;
	
	// vertexNum 256
	for(int z = 0; z < ColIdx; z++)
	{
		for(int x = 0; x < RowIdx; x++)
		{
			v0.p = D3DXVECTOR3(x * cellsize, HeightMap[z][x], z * cellsize);
			v0.t = D3DXVECTOR2(x / RowIdx, z / ColIdx);
			
			v1.p = D3DXVECTOR3(x * cellsize + cellsize, HeightMap[z][x + 1], z * cellsize);
			v1.t = D3DXVECTOR2((x + 1) / RowIdx, z / ColIdx);
			
			v2.p = D3DXVECTOR3(x * cellsize + cellsize, HeightMap[z + 1][x + 1], z * cellsize + cellsize);
			v2.t = D3DXVECTOR2((x + 1) / RowIdx, (z + 1) / ColIdx);
			
			v3.p = D3DXVECTOR3(x * cellsize, HeightMap[z + 1][x], z * cellsize + cellsize);
			v3.t = D3DXVECTOR2(x / RowIdx, (z + 1) / ColIdx);
			
			vec_Vertexs.push_back(v0);
			vec_Vertexs.push_back(v2);
			vec_Vertexs.push_back(v3);
			
			vec_Vertexs.push_back(v0);
			vec_Vertexs.push_back(v1);
			vec_Vertexs.push_back(v2);
		}
	}	

	D3DMATERIAL9 Mtl;
	ZeroMemory(&Mtl, sizeof(D3DMATERIAL9));
	Mtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	Mtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	Mtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	Mtl.Power = 2.0f;

	mtltex.SetMaterial(Mtl);
	LPDIRECT3DTEXTURE9 texture;
	D3DXCreateTextureFromFileA(DEVICE, "Data/terrain.jpg", &texture);
	mtltex.SetTexture(texture);
}

float Terrain::GetHeight(float x, float z)
{
	float _x = Width / 2.0f + x;
	float _z = Height / 2.0f - z;

	_x /= CellSize;
	_z /= CellSize;

	// floorf = 내림
	int col = floorf(_x);
	int row = floorf(_z);

	float A = HeightMap[row][col];
	float B = HeightMap[row][col + 1];
	float C = HeightMap[row + 1][col];
	float D = HeightMap[row + 1][col + 1];

	float dx = _x - col;
	float dz = _z - row;
	float MapHeight = 0;

	if(dz > 1.0f - dx)
	{
		float uy = B - A; // A -> B
		float vy = C - A; // A -> C

		MapHeight = A + Lerp(0.0f, uy, dx) + Lerp(0.0f, vy, dz);
	}
	else // 아래쪽 삼각형 DCB
	{
		float uy = C - D; // D -> C
		float vy = B - D; // D -> B

		MapHeight = D + Lerp(0.0f, uy, 1.0f - dx) + Lerp(0.0f, vy, 1.0f - dz);
	}
	
	return MapHeight;
}

bool Terrain::GetHeight(OUT D3DXVECTOR3& pos)
{
	//if (pos.x < 0.f || pos.z < 0.f || pos.x >= RowCell || pos.z >= ColCell)
	//{
	//	return false;
	//}

	//int nX = pos.x;
	//int nZ = pos.z;

	//float fDeltaX = pos.x - nX;
	//float fDeltaZ = pos.z - nZ;

	//int _0 = (nZ + 0) * RowCell + nX + 0;
	//int _1 = (nZ + 1) * RowCell + nX + 0;
	//int _2 = (nZ + 1) * RowCell + nX + 1;
	//int _3 = (nZ + 0) * RowCell + nX + 1;

	//if (fDeltaX + fDeltaZ < 1.0f) //왼쪽 아래에 있다
	//{
	//	D3DXVECTOR3 v01 = vec_Vertexs[_1] - vec_Vertexs[_0];
	//	D3DXVECTOR3 v03 = vec_Vertexs[_3] - vec_Vertexs[_0];

	//	pos.y = vec_Vertexs[_0].y + (v01 * fDeltaZ + v03 * fDeltaX).y;

	//}
	//else
	//{
	//	fDeltaX = 1.0f - fDeltaX;
	//	fDeltaZ = 1.0f - fDeltaZ;
	//	D3DXVECTOR3 v21 = vec_Vertexs[_1] - vec_Vertexs[_2];
	//	D3DXVECTOR3 v23 = vec_Vertexs[_3] - vec_Vertexs[_2];
	//	pos.y = vec_Vertexs[_2].y + (v21 * fDeltaX + v23 * fDeltaZ).y;
	//}

	//return true;
}

void Terrain::Update(float delta)
{
	
}

void Terrain::Draw(float delta)
{
	//DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	//DEVICE->SetRenderState(D3DRS_CULLMODE, false);

	D3DXMATRIXA16 WorldMat;
	D3DXMatrixIdentity(&WorldMat);
	D3DXMatrixTranslation(&WorldMat, -126.0f, 0, -126.0f);

	DEVICE->SetTexture(0, mtltex.GetTexture());
	DEVICE->SetMaterial(&mtltex.GetMaterial());
	DEVICE->SetTransform(D3DTS_WORLD, &WorldMat);
	DEVICE->SetFVF(PNT_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
							vec_Vertexs.size() / 3,
							&vec_Vertexs[0],
							sizeof(PNT_VERTEX));
	
	DEVICE->SetTexture(0, NULL);

	//DEVICE->SetRenderState(D3DRS_LIGHTING, true);
}