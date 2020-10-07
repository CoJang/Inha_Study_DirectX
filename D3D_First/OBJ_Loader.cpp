#include "stdafx.h"
#include <istream>
#include <fstream>
#include "OBJ_Loader.h"

int ReadData(vector<PNT_VERTEX> & containor, D3DMATERIAL9 & material, const char * srcFile)
{
	FILE* SrcFile = fopen(srcFile, "rb");

	string MaterialPath = srcFile;
	vector<D3DXVECTOR3> vertices;
	vector<D3DXVECTOR2> UVs;
	vector<D3DXVECTOR3> normals;

	if (SrcFile == NULL)
	{
		printf("ERROR! SrcFile OpenFailed!\n");
		return 0;
	}

	char buff[256] = {0};
	float x(0), y(0), z(0);

	while(fscanf_s(SrcFile, "%s %f %f %f \n", &buff, sizeof(buff), &x, &y, &z) != EOF)
	{
		if (strcmp(buff, "usemtl") == 0) break;
		if (strcmp(buff, "mtllib") == 0)
		{
			fscanf_s(SrcFile, "%s\n", &buff, sizeof(buff));

			string ObjFileName = strrchr(MaterialPath.c_str(), '/');
			string Path(MaterialPath.c_str(), MaterialPath.size() - ObjFileName.size());
			Path += buff;
			MaterialPath = Path;
		}
		
		if(buff[0] == 'v')
		{
			switch(buff[1])
			{
			case '\0':
				printf("%s %f %f %f \n", buff, x, y, z);
				vertices.push_back(D3DXVECTOR3(x, y, z));
				break;
			case 't':
				printf("%s %f %f %f \n", buff, x, y, z);
				UVs.push_back(D3DXVECTOR2(x, y));
				break;
			case 'n':
				printf("%s %f %f %f \n", buff, x, y, z);
				normals.push_back(D3DXVECTOR3(x, y, z));
				break;
			}
			
			x = 0; y = 0; z = 0;
			ZeroMemory(&buff, sizeof(buff));
		}
	}

	cout << "while break!" << endl;

	int index[9] = {0};
	PNT_VERTEX v;
	
	while (fscanf_s(SrcFile, "%s %d/%d/%d %d/%d/%d %d/%d/%d\n", &buff, sizeof(buff), 
		&index[0], &index[1], &index[2],
		&index[3], &index[4], &index[5],
		&index[6], &index[7], &index[8]) != EOF)
	{
		if (buff[0] == 'f' && buff[1] == '\0')
		{
			for(int i = 0; i < 9; i += 3)
			{
				v.p = vertices[index[i] - 1];
				v.t = UVs[index[i + 1] - 1];
				v.n = normals[index[i + 2] - 1];
				containor.push_back(v);
			}
		}
	}

	fclose(SrcFile);
	
	LoadMaterial(material, MaterialPath.c_str());
	

	return 0;
}

int LoadMaterial(D3DMATERIAL9& material, const char* srcFile)
{
	return 0;
}

