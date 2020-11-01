#pragma once

class IObserver;

class Subject
{
private:
	string EventMsg;
	map<string, IObserver*> mapObservers;
public:
	Subject();
	~Subject();

	void OnSubscribe(string kind, IObserver* obs);
	void OnUnsubscribe(string kind, IObserver* obs);

	void SendEvent(string kind, string msg);
	void ReceiveEvent(string msg);
};

