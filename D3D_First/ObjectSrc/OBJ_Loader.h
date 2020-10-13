#pragma once

class Group;
class MtlTex;

class Loader
{
private:
	std::map<string, MtlTex*> mapMtlTex;
public:
	Loader() = default;
	~Loader() = default;

	void LoadOBJ(OUT std::vector<Group*> & vec_Group, IN char * folder, IN char * file);
	void LoadMtlLib(char * folder, char * file);

	void LoadASE(OUT std::vector<Group*> & vec_Group, IN char * folder, IN char * file);
	void LoadASEMtl(char * folder, char * file);
};