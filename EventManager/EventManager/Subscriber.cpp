#include "stdafx.h"
#include "ConcreteObserverA.h"
#include "Subscriber.h"


Subscriber::Subscriber()
{
}


Subscriber::~Subscriber()
{
}

void Subscriber::Subscribe(string kind, IObserver* obs)
{
	if (mapObservers.find(kind) == mapObservers.end())
	{
		ConcreteObserverA* Observer = new ConcreteObserverA;
		mapObservers[kind] = Observer;
		Observer->OnSubscribe(kind, this);
	}
}

void Subscriber::UnSubscribe(string kind, IObserver* obs)
{

}

void Subscriber::SendEvent(string kind, string msg)
{
	if(mapObservers.find(kind) != mapObservers.end())
	{
		mapObservers[kind]->Update(msg);
	}
}

void Subscriber::ReciveEvent(string msg)
{
	printf("Recived Data : %s\n", msg.c_str());
}
