#pragma once
#include "SceneState.h"

class MyCamera;

class cScene
{
private:
	MyCamera* m_pCamera;
	ISceneState* m_sceneState;
public:
	cScene();
	~cScene();

	void Setup();
	void Update();
	void Render();

	void SetSceneState(ISceneState* scenestate);
};

