#include "stdafx.h"
#include "Subscriber.h"
#include "ConcreteObserverA.h"


ConcreteObserverA::ConcreteObserverA()
{
}


ConcreteObserverA::~ConcreteObserverA()
{
}

void ConcreteObserverA::OnSubscribe(string kind, Subscriber* sub)
{
	ObsKind = kind;
	Subs.push_back(sub);
	sub->Subscribe(kind, this);
}

void ConcreteObserverA::OnUnsubscribe(Subscriber* sub)
{
}

void ConcreteObserverA::Update(string msg)
{
	for(auto sub : Subs)
	{
		sub->ReciveEvent(msg);
	}
}
