#pragma once

#define g_pUIManager UIManager::GetInstance()

class MySprite;

class UIManager
{
private:
	Singletone(UIManager);

	map<string, LPDIRECT3DTEXTURE9> m_mapTexture;
	map<string, MySprite*> m_mapSprite;
public:
	POINT m_ptMousePos;
	POINT m_ptOldMousePos;

	bool Update();
	
	LPDIRECT3DTEXTURE9 GetTexture(char* path);
	LPDIRECT3DTEXTURE9 GetTexture(string & path);

	void AddSprite(char* Name, MySprite* sprite);
	void AddSprite(string & Name, MySprite* sprite);
	MySprite* GetSprite(char* Name);
	MySprite* GetSprite(string & Name);

	void Destroy();
};

