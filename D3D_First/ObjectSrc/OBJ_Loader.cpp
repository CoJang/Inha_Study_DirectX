#include "stdafx.h"
#include "Group.h"
#include "OBJ_Loader.h"

void Loader::LoadOBJ(std::vector<Group*>& vec_Group, char* folder, char* file)
{
	string Path = folder + string("/") + file;
	FILE* SrcFile;

	if (fopen_s(&SrcFile, Path.c_str(), "rb") != 0)
	{
		cout << file << " Open Failed!" << endl;
		return;
	}

	vector<D3DXVECTOR3> positions;
	vector<D3DXVECTOR3> normals;
	vector<D3DXVECTOR2> UVs;
	
	vector<PNT_VERTEX> vertices;
	string MtlName;
	
	while(!feof(SrcFile))
	{
		char buff[1024] = { 0 };
		fgets(buff, sizeof(buff), SrcFile);

		if(buff[0] == '#') continue;
		
		if(buff[0] == 'm')
		{
			// %*�� �ش� ������ ����(����)��.
			sscanf_s(buff, "%*s %s", buff, sizeof(buff));
			LoadMtlLib(folder, buff);
		}
		else if(buff[0] == 'g')
		{
			if(!vertices.empty())
			{
				Group* group = new Group;
				group->SetVertex(vertices);
				group->SetMat(mapMtlTex[MtlName]);
				vec_Group.push_back(group);
				vertices.clear();
			}
		}
		else if(buff[0] == 'v')
		{
			float x(0), y(0), z(0);
			switch(buff[1])
			{
			case ' ':
				sscanf_s(buff, "%*s %f %f %f", &x, &y, &z);
				positions.push_back(D3DXVECTOR3(x, y, z));
				break;
			case 't':
				sscanf_s(buff, "%*s %f %f %f", &x, &y, &z);
				UVs.push_back(D3DXVECTOR2(x, y));
				break;
			case 'n':
				sscanf_s(buff, "%*s %f %f %f", &x, &y, &z);
				normals.push_back(D3DXVECTOR3(x, y, z));
				break;
			}
		}
		else if(buff[0] == 'u')
		{
			sscanf_s(buff, "%*s %s", buff, sizeof(buff));
			MtlName = buff;
		}
		else if(buff[0] == 'f')
		{
			unsigned int Index[3][3];
			sscanf_s(buff, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
						&Index[0][0], &Index[0][1], &Index[0][2],
						&Index[1][0], &Index[1][1], &Index[1][2],
						&Index[2][0], &Index[2][1], &Index[2][2]);

			for(int i = 0; i < 3; i++)
			{
				PNT_VERTEX v;
				v.p = positions[Index[i][0] - 1];
				v.t = UVs[Index[i][1] - 1];
				v.n = normals[Index[i][2] - 1];
				vertices.push_back(v);
			}
		}
	}

	fclose(SrcFile);

	for(auto it : mapMtlTex)
	{
		SafeRelease(it.second);
	}
	mapMtlTex.clear();
}

void Loader::LoadMtlLib(char* folder, char* file)
{
	string Path = folder + string("/") + file;

	FILE* SrcFile;
		
	if (fopen_s(&SrcFile, Path.c_str(), "rb") != 0)
	{
		cout << file << " Open Failed!" << endl;
		return;
	}

	string MtlName;
	
	while(!feof(SrcFile))
	{
		char buff[1024];
		fgets(buff, sizeof(buff), SrcFile);

		if (buff[0] == '#') continue;

		if(buff[0] == 'n')
		{
			sscanf_s(buff, "%*s %s", buff, sizeof(buff));
			MtlName = buff;

			if(mapMtlTex.find(MtlName) == mapMtlTex.end())
			{
				mapMtlTex[MtlName] = new MtlTex;
			}
		}
		else if(buff[0] == 'K')
		{
			float r(0), g(0), b(0);
			sscanf_s(buff, "%*s %f %f %f", &r, &g, &b);
			
			switch(buff[1])
			{
			case 'a':
				mapMtlTex[MtlName]->GetMaterial().Ambient.r = r;
				mapMtlTex[MtlName]->GetMaterial().Ambient.g = g;
				mapMtlTex[MtlName]->GetMaterial().Ambient.b = b;
				mapMtlTex[MtlName]->GetMaterial().Ambient.a = 1.0f;
				break;
			case 'd':
				mapMtlTex[MtlName]->GetMaterial().Diffuse.r = r;
				mapMtlTex[MtlName]->GetMaterial().Diffuse.g = g;
				mapMtlTex[MtlName]->GetMaterial().Diffuse.b = b;
				mapMtlTex[MtlName]->GetMaterial().Diffuse.a = 1.0f;
				break;
			case 's':
				mapMtlTex[MtlName]->GetMaterial().Specular.r = r;
				mapMtlTex[MtlName]->GetMaterial().Specular.g = g;
				mapMtlTex[MtlName]->GetMaterial().Specular.b = b;
				mapMtlTex[MtlName]->GetMaterial().Specular.a = 1.0f;
				break;
			}
		}
		else if(buff[0] == 'd')
		{
			float power = 0.0f;
			sscanf_s(buff, "%*s %f", &power);

			mapMtlTex[MtlName]->GetMaterial().Power = power;
		}
		else if(buff[0] == 'm')
		{
			sscanf_s(buff, "%*s %s", buff, sizeof(buff));
			Path = folder + (string("/") + buff);

			LPDIRECT3DTEXTURE9 texture = TEXTUREMANAGER->GetTexture(Path);
			mapMtlTex[MtlName]->SetTexture(texture);
		}
	}

	fclose(SrcFile);
}

void Loader::LoadASE(std::vector<Group*>& vec_Group, char* folder, char* file)
{
	string Path = folder + string("/") + file;
	FILE* SrcFile;

	if (fopen_s(&SrcFile, Path.c_str(), "rb") != 0)
	{
		cout << file << " Open Failed!" << endl;
		return;
	}

	vector<D3DXVECTOR3> positions;
	vector<D3DXVECTOR3> normals;
	vector<D3DXVECTOR2> UVs;

	vector<PNT_VERTEX> vertices;
	string MtlName;
	int MtlCount = 0;

	while (!feof(SrcFile))
	{
		char buff[1024] = { 0 };
		fscanf_s(SrcFile, "%s", buff, sizeof(buff));

		if (strcmp(buff, "*COMMENT") == 0) continue;

		if (strcmp(buff, "*MATERIAL_LIST") == 0)
		{
			fgets(buff, sizeof(buff), SrcFile);
			fgets(buff, sizeof(buff), SrcFile);
			
			sscanf_s(buff, "%*s %d", &MtlCount);
			fgets(buff, sizeof(buff), SrcFile);

			float r(0), g(0), b(0);
			for(int i = 0; i < MtlCount; ++i)
			{
				if (mapMtlTex.find(to_string(i)) == mapMtlTex.end())
				{
					mapMtlTex[to_string(i)] = new MtlTex;
				}
				
				fgets(buff, sizeof(buff), SrcFile); // Name
				fgets(buff, sizeof(buff), SrcFile); // Class
				fgets(buff, sizeof(buff), SrcFile); // Ambient
				sscanf_s(buff, "%*s %f %f %f", &r, &g, &b);
				mapMtlTex[to_string(i)]->GetMaterial().Ambient.r = r;
				mapMtlTex[to_string(i)]->GetMaterial().Ambient.g = g;
				mapMtlTex[to_string(i)]->GetMaterial().Ambient.b = b;
				mapMtlTex[to_string(i)]->GetMaterial().Ambient.a = 1.0f;

				fgets(buff, sizeof(buff), SrcFile);
				sscanf_s(buff, "%*s %f %f %f", &r, &g, &b);
				mapMtlTex[to_string(i)]->GetMaterial().Diffuse.r = r;
				mapMtlTex[to_string(i)]->GetMaterial().Diffuse.g = g;
				mapMtlTex[to_string(i)]->GetMaterial().Diffuse.b = b;
				mapMtlTex[to_string(i)]->GetMaterial().Diffuse.a = 1.0f;

				fgets(buff, sizeof(buff), SrcFile);
				sscanf_s(buff, "%*s %f %f %f", &r, &g, &b);
				mapMtlTex[to_string(i)]->GetMaterial().Specular.r = r;
				mapMtlTex[to_string(i)]->GetMaterial().Specular.g = g;
				mapMtlTex[to_string(i)]->GetMaterial().Specular.b = b;
				mapMtlTex[to_string(i)]->GetMaterial().Specular.a = 1.0f;
				
				while(i != MtlCount) // skip for other data
				{
					fscanf_s(SrcFile, "%s", buff, sizeof(buff));

					if (strcmp(buff, "*BITMAP") == 0)
					{
						fgets(buff, sizeof(buff), SrcFile);
						sscanf_s(buff, "%*[^/]%*[/]%*[^/]%s", buff, sizeof(buff));
						Path = folder + string(buff);
						Path.erase(Path.size() - 1);

						LPDIRECT3DTEXTURE9 texture = TEXTUREMANAGER->GetTexture(Path);
						mapMtlTex[to_string(i)]->SetTexture(texture);

						if (i == MtlCount - 1) break;
					}
					
					if(strcmp(buff, "*MATERIAL") == 0)
					{
						fgets(buff, sizeof(buff), SrcFile);
						break;
					}
				} // end while
			} // end for
		} // end if
		else if (strcmp(buff, "*GEOMOBJECT") == 0)
		{
			if (!vertices.empty())
			{
				Group* group = new Group;
				group->SetVertex(vertices);
				group->SetMat(mapMtlTex[MtlName]);
				vec_Group.push_back(group);
				vertices.clear();
			}

			if (strcmp(buff, "*MESH_VERTEX") == 0)
			{
				fgets(buff, sizeof(buff), SrcFile);
				float x(0), y(0), z(0);
				sscanf_s(buff, "%*d %f %f %f", &x, &y, &z);
				//switch (buff[1])
				//{
				//case ' ':
				//	sscanf_s(buff, "%*s %f %f %f", &x, &y, &z);
				//	positions.push_back(D3DXVECTOR3(x, y, z));
				//	break;
				//case 't':
				//	sscanf_s(buff, "%*s %f %f %f", &x, &y, &z);
				//	UVs.push_back(D3DXVECTOR2(x, y));
				//	break;
				//case 'n':
				//	sscanf_s(buff, "%*s %f %f %f", &x, &y, &z);
				//	normals.push_back(D3DXVECTOR3(x, y, z));
				//	break;
				//}
			}
		}
		else if (buff[0] == 'u')
		{
			sscanf_s(buff, "%*s %s", buff, sizeof(buff));
			MtlName = buff;
		}
		else if (buff[0] == 'f')
		{
			unsigned int Index[3][3];
			sscanf_s(buff, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&Index[0][0], &Index[0][1], &Index[0][2],
				&Index[1][0], &Index[1][1], &Index[1][2],
				&Index[2][0], &Index[2][1], &Index[2][2]);

			for (int i = 0; i < 3; i++)
			{
				PNT_VERTEX v;
				v.p = positions[Index[i][0] - 1];
				v.t = UVs[Index[i][1] - 1];
				v.n = normals[Index[i][2] - 1];
				vertices.push_back(v);
			}
		}
	}

	fclose(SrcFile);

	for (auto it : mapMtlTex)
	{
		SafeRelease(it.second);
	}
	mapMtlTex.clear();
}

void Loader::LoadASEMtl(char* folder, char* file)
{

}
