#include "stdafx.h"
#include "ConcreteObserverA.h"
#include "Subject.h"


Subject::Subject()
{
}


Subject::~Subject()
{
}

void Subject::OnSubscribe(string kind, IObserver* obs)
{
	if (mapObservers.find(kind) == mapObservers.end())
	{
		mapObservers[kind] = obs;
	}
}

void Subject::OnUnsubscribe(string kind, IObserver* obs)
{
	if (mapObservers.find(kind) != mapObservers.end())
	{
		mapObservers.erase(mapObservers.find(kind));
	}
}

void Subject::SendEvent(string kind, string msg)
{
	if(mapObservers.find(kind) != mapObservers.end())
	{
		mapObservers[kind]->ReceiveEvent(msg);
	}
}

void Subject::ReceiveEvent(string msg)
{
	for (auto observer : mapObservers)
	{
		observer.second->ReceiveEvent(msg);
	}
}
