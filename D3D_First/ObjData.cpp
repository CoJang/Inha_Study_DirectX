#include "stdafx.h"
#include "ObjData.h"


ObjData::ObjData()
	:RefCount(1)
{
	OBJECTMANAGER->AddObject(this);
}


ObjData::~ObjData()
{
	OBJECTMANAGER->RemoveObject(this);
}

void ObjData::AddRef()
{
	++RefCount;
}

void ObjData::Release()
{
	--RefCount;
	
	if(RefCount == 0)
	{
		delete this;
	}
}
