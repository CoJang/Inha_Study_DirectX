#include "stdafx.h"
#include "ObjectSrc/MtlTex.h"
#include "Terrain.h"


Terrain::Terrain()
{
}


Terrain::~Terrain()
{
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

	while(true)
	{
		if (feof(SrcFile)) break;
		BYTE height = (BYTE)fgetc(SrcFile);
		HeightDatas.push_back(height / 10.0f);
	}
	
	fclose(SrcFile);
}

void Terrain::CreateTerrain(int vertexNum, float cellsize)
{
	if (HeightDatas.empty()) return;
	
	float Height = 0;
	float HeightMap[257][257] = { 0 };
	
	for (int i = 0; i < 257; i++)
		for (int j = 0; j < 257; j++)
			HeightMap[i][j] = HeightDatas[j + (i * 257)];
	
	PNT_VERTEX v0, v1, v2, v3;
	v0.n = D3DXVECTOR3(0, 1, 0);
	v1.n = D3DXVECTOR3(0, 1, 0);
	v2.n = D3DXVECTOR3(0, 1, 0);
	v3.n = D3DXVECTOR3(0, 1, 0);
	// vertexNum 256
	for(int z = 0; z < vertexNum; z++)
	{
		for(int x = 0; x < vertexNum; x++)
		{
			v0.p = D3DXVECTOR3(x * cellsize, HeightMap[z][x], z * cellsize);
			v0.t = D3DXVECTOR2(x / (float)vertexNum, z / (float)vertexNum);
			
			v1.p = D3DXVECTOR3(x * cellsize + cellsize, HeightMap[z][x + 1], z * cellsize);
			v1.t = D3DXVECTOR2((x + 1) / (float)vertexNum, z / (float)vertexNum);
			
			v2.p = D3DXVECTOR3(x * cellsize + cellsize, HeightMap[z + 1][x + 1], z * cellsize + cellsize);
			v2.t = D3DXVECTOR2((x + 1) / (float)vertexNum, (z + 1) / (float)vertexNum);
			
			v3.p = D3DXVECTOR3(x * cellsize, HeightMap[z + 1][x], z * cellsize + cellsize);
			v3.t = D3DXVECTOR2(x / (float)vertexNum, (z + 1) / (float)vertexNum);
			
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

void Terrain::Update(float delta)
{
	
}

void Terrain::Draw(float delta)
{
	//DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	//DEVICE->SetRenderState(D3DRS_CULLMODE, false);

	D3DXMATRIXA16 WorldMat;
	D3DXMatrixIdentity(&WorldMat);
	D3DXMatrixTranslation(&WorldMat, -125, -15, -125);

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
