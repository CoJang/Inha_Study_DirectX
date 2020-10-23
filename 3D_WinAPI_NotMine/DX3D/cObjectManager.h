#pragma once
#define g_pObjectManager cObjectManager::GetInstance()

class cObjectManager
{
private:
	Singletone(cObjectManager);

	std::set<cObject*> m_setObject;

public:
//	cObjectManager();
//	~cObjectManager();
	void AddObject(cObject* pObject);
	void RemoveObject(cObject* pObject);
	void Destroy();
};

