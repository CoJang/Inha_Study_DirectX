#pragma once

class cBox;

class ISceneState
{
public:
	virtual ~ISceneState() = default;

	virtual void Setup()  = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

class SSLoad : public ISceneState
{
private:
	LPD3DXSPRITE		m_pSprite;
	D3DXIMAGE_INFO		m_stImageInfo;
	LPDIRECT3DTEXTURE9	m_pTextureUI;
	RECT				m_rRect;
public:
	SSLoad();
	~SSLoad() override;

	void Setup()  override;
	void Update() override;
	void Render() override;
};

class MyGrid;

class SSGame : public ISceneState
{
private:
	MyGrid* m_pGrid;
	cBox* m_pBox;
public:
	SSGame();
	~SSGame() override;

	void Setup()  override;
	void Update() override;
	void Render() override;
};

class SSEnd : public ISceneState
{
private:
	LPD3DXSPRITE		m_pSprite;
	D3DXIMAGE_INFO		m_stImageInfo;
	LPDIRECT3DTEXTURE9	m_pTextureUI;
	RECT				m_rRect;
public:
	SSEnd();
	~SSEnd() override;

	void Setup()  override;
	void Update() override;
	void Render() override;
};

