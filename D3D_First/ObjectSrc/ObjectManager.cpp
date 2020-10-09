#include "stdafx.h"
#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::AddObject(ObjData* obj)
{
	setObject.insert(obj);
}

void ObjectManager::RemoveObject(ObjData* obj)
{
	setObject.erase(obj);
}

void ObjectManager::Destroy()
{
	setObject.clear();
}
