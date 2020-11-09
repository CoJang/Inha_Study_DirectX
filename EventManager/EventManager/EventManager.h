#pragma once

class IObserver;
class Subject;

#define g_pEventManager EventManager::GetInstance()

class EventManager
{
private:
	static EventManager*	instance;
	map<string, IObserver*> mapObservers;
	map<string, Subject*>	mapSubject;
public:
	EventManager();
	~EventManager();

	static EventManager* GetInstance()
	{
		if (instance == nullptr)
			instance = new EventManager;

		return instance;
	}
};

