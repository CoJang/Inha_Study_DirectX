#pragma once

#define g_pUIManager UIManager::GetInstance()

class MySprite;

enum MouseState
{
	MS_LCLICK,
	MS_LDCLICK,
	MS_RCLICK,
	MS_RDCLICK,
	MS_DRAG,
	MS_NORMAL
};

enum FontType
{
	FONT_DEFAULT,
	FONT_WARNING,
};

class UIManager
{
private:
	Singletone(UIManager);

	map<string, LPDIRECT3DTEXTURE9> m_mapTexture;
	map<string, D3DXIMAGE_INFO> m_mapImageInfo;
	map<string, MySprite*> m_mapSprite;
	map<FontType, LPD3DXFONT> m_mapFont;
public:
	MouseState m_stMouseState;
	POINT m_ptMousePos;
	POINT m_ptOldMousePos;

	bool Update();

	void AddImageInfo(char* path, D3DXIMAGE_INFO info);
	void AddImageInfo(string & path, D3DXIMAGE_INFO info);
	D3DXIMAGE_INFO GetImageInfo(char* path);
	D3DXIMAGE_INFO GetImageInfo(string & path);
	
	void AddTexture(char* path, LPDIRECT3DTEXTURE9 texture);
	void AddTexture(string & path, LPDIRECT3DTEXTURE9 texture);
	LPDIRECT3DTEXTURE9 GetTexture(char* path);
	LPDIRECT3DTEXTURE9 GetTexture(string & path);

	void AddSprite(char* Name, MySprite* sprite);
	void AddSprite(string & Name, MySprite* sprite);
	MySprite* GetSprite(char* Name);
	MySprite* GetSprite(string & Name);

	LPD3DXFONT GetFont(FontType e);
	void Destroy();
};

