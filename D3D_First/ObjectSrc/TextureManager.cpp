#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(char* path)
{
	if(mapTexture.find(path) == mapTexture.end())
	{
		D3DXCreateTextureFromFileA(DEVICE, path, &mapTexture[path]);
	}

	return mapTexture[path];
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(string& path)
{
	return GetTexture((char*)path.c_str());
}

void TextureManager::Destroy()
{
	for(auto it : mapTexture)
	{
		SafeRelease(it.second);
	}
	
	mapTexture.clear();
}
