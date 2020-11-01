#include "stdafx.h"
#include "Subject.h"
#include "ConcreteObserverA.h"


ConcreteObserverA::ConcreteObserverA()
{
}


ConcreteObserverA::~ConcreteObserverA()
{
}

void ConcreteObserverA::Subscribe(string kind, Subject* sub)
{
	//if(mapSubs.find(kind) == mapSubs.end())
	//{
	//	mapSubs[kind] = sub;
	//	sub->OnSubscribe(kind, this);
	//}
	Publisher = sub;
	Publisher->OnSubscribe(kind, this);
}

void ConcreteObserverA::Unsubscribe(string kind)
{
	//if (mapSubs.find(kind) != mapSubs.end())
	//{
	//	mapSubs[kind]->OnUnsubscribe(kind, this);
	//}
	Publisher->OnUnsubscribe(kind, this);
}

void ConcreteObserverA::SendEvent(string event)
{
	Publisher->ReceiveEvent(event);
}

void ConcreteObserverA::ReceiveEvent(string event)
{
	printf("Received Data : %s\n", event.c_str());
}
