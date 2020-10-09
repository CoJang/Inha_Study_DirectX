#pragma once

class Group;
class MtlTex;

class ObjLoader
{
private:
	std::map<string, MtlTex*> mapMtlTex;
public:
	ObjLoader() = default;
	~ObjLoader() = default;

	void Load(OUT std::vector<Group*> & vec_Group, IN char * folder, IN char * file);
	void LoadMtlLib(char * folder, char * file);
};