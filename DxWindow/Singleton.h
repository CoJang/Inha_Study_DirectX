#pragma once
#include "framework.h"

template<class T>
class Singleton
{
protected:
	static T* instance;
	Singleton() = default;
	virtual ~Singleton() = default;
public:
	static T* GetInstance()
	{
		if (instance == NULL)
			instance = new T;

		return instance;
	}

	static void Destroy()
	{
		SafeDelete(instance);
	}
};

template <class T>
T* Singleton<T>::instance = nullptr;