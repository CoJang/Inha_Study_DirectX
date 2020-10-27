#pragma once

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager
{
private:
	Singletone(cTimeManager);

	DWORD m_dwLastUpdateTime;
	float m_fElapsedTime;
	float m_fTimeMultiplier;

public:
	void Update();
	float GetElapsedTime();
	float GetLastUpdateTime();
	float GetTimeMultiplier();
	void  SetTimeMultiplier(float fMultiplier);
};

