#pragma once
#include "IObserver.h"

class Subscriber;

class ConcreteObserverA : public IObserver
{
private:
	string ObsKind;
	vector<Subscriber*> Subs;
public:
	ConcreteObserverA();
	~ConcreteObserverA();

	void OnSubscribe(string kind, Subscriber* sub);
	void OnUnsubscribe(Subscriber* sub);
	
	void Update(string msg);
	
};

