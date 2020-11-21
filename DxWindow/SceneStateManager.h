#pragma once
#include "Singleton.h"

#define g_pSceneStateManager cSceneStateManager::GetInstance()
#define g_pCurrentScene cSceneStateManager::GetInstance()->GetCurrentScene()

enum eSceneState
{
	SS_LOADING = 0,
	SS_GAME,
	SS_END,
};

class cScene;
class ISceneState;

class cSceneStateManager : public Singleton<cSceneStateManager>
{
private:
	friend class Singleton<cSceneStateManager>;
	
	cSceneStateManager();
	~cSceneStateManager();
	cScene* m_CurrentScene;
	map<eSceneState, ISceneState*> m_mapSceneState;
public:
	cScene* GetCurrentScene() { return m_CurrentScene; }
	void ChangeState(eSceneState state);
	void Destroy();
};
