#pragma once

class Group;
class MtlTex;

int ReadData(vector<PNT_VERTEX> & containor, D3DMATERIAL9 & material, LPDIRECT3DTEXTURE9 & texture, const char* srcFile);
int LoadMaterial(D3DMATERIAL9 & material, LPDIRECT3DTEXTURE9 & texture, const char* srcFile);

class ObjLoader
{
private:
	std::map<string, MtlTex*> mapMtlTex;
public:
	ObjLoader();
	~ObjLoader();

	void Load(OUT std::vector<Group*> & vec_Group, IN char * folder, IN char * file);
	void LoadMtlLib(char * folder, char * file);
};