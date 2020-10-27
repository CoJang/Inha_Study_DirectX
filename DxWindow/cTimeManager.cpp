#include "framework.h"
#include "cTimeManager.h"

cTimeManager::cTimeManager()
	:m_fTimeMultiplier(1.0f)
{
	m_dwLastUpdateTime = GetTickCount();
}

cTimeManager::~cTimeManager()
{
	
}

void cTimeManager::Update()
{
	DWORD dwCurrentTime = GetTickCount();
	m_fElapsedTime = (dwCurrentTime - m_dwLastUpdateTime) / 1000.0f;
	m_dwLastUpdateTime = dwCurrentTime;
}

float cTimeManager::GetElapsedTime()
{
	return m_fElapsedTime * m_fTimeMultiplier;
}

float cTimeManager::GetLastUpdateTime()
{
	return m_dwLastUpdateTime * m_fTimeMultiplier / 1000.0f;
}

float cTimeManager::GetTimeMultiplier()
{
	return m_fTimeMultiplier;
}

void cTimeManager::SetTimeMultiplier(float fMultiplier)
{
	m_fTimeMultiplier = fMultiplier;
}
