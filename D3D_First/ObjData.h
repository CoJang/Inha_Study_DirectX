#pragma once
class ObjData
{
protected:
	ULONG RefCount;
public:
	ObjData();
	virtual ~ObjData();

	virtual void AddRef();
	virtual void Release();
	
};

