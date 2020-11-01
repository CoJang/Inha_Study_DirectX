#pragma once
#include "IObserver.h"

class Subject;

class ConcreteObserverA : public IObserver
{
private:
	//map<string, Subject*> mapSubs;
	Subject* Publisher;
public:
	ConcreteObserverA();
	~ConcreteObserverA();

	void Subscribe(string kind, Subject* sub);
	void Unsubscribe(string kind);

	void SendEvent(string event);
	void ReceiveEvent(string event) override;
};

