#pragma once
class cSkinnedMesh;

class cZealot
{
public:
	cZealot();
	virtual	~cZealot(void);

private:
	cSkinnedMesh* m_pSkinnedMesh;
public:
	void Setup();
	void Update();
	void Render(D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255));
};

