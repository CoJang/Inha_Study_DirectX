#pragma once
class GameScene
{
public:
	GameScene();
	~GameScene();

private:
	LPDIRECT3DDEVICE9 Device;

public:
	void InitGameScene();
	void Update();
	void Render(float delta);
};

