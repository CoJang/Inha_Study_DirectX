#include "framework.h"
#include "SceneState.h"
#include "Scene.h"
#include "SceneStateManager.h"


cSceneStateManager::cSceneStateManager()
{
	m_CurrentScene = new cScene;
}


cSceneStateManager::~cSceneStateManager()
{
	delete m_CurrentScene;
}

void cSceneStateManager::ChangeState(eSceneState state)
{
	if(m_mapSceneState.find(state) == m_mapSceneState.end())
	{
		ISceneState* SceneState;
		switch (state)
		{
		case SS_LOADING:
			SceneState = new SSLoad;
			break;
		case SS_GAME:
			SceneState = new SSGame;
			break;
		case SS_END:
			SceneState = new SSEnd;
			break;
		default:
			SceneState = new SSLoad;
			break;
		}
		SceneState->Setup();
		m_mapSceneState[state] = SceneState;
	}
	
	m_CurrentScene->SetSceneState(m_mapSceneState[state]);
}

void cSceneStateManager::Destroy()
{
	for(auto state : m_mapSceneState)
	{
		delete state.second;
	}
}
