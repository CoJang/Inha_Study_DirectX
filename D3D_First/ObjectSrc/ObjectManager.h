#pragma once
#include <set>
#define OBJECTMANAGER ObjectManager::GetInstance()


class ObjectManager
{
private:
	Singletone(ObjectManager);
	
	std::set<ObjData*> setObject;
public:
	void AddObject(ObjData* obj);
	void RemoveObject(ObjData* obj);
	void Destroy();
};

