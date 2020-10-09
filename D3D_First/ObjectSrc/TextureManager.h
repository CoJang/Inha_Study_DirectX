#pragma once
#include <map>
#define TEXTUREMANAGER TextureManager::GetInstance()

class TextureManager
{
private:
	Singletone(TextureManager);
	std::map<string, LPDIRECT3DTEXTURE9> mapTexture;

public:
	LPDIRECT3DTEXTURE9 GetTexture(char* path);
	LPDIRECT3DTEXTURE9 GetTexture(string & path);

	void Destroy();
};

