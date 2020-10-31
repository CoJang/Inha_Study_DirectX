#pragma once

class IObserver;

class Subscriber
{
private:
	string EventMsg;
	map<string, IObserver*> mapObservers;
public:
	Subscriber();
	~Subscriber();

	void Subscribe(string kind, IObserver* obs);
	void UnSubscribe(string kind, IObserver* obs);

	void SendEvent(string kind, string msg);
	void ReciveEvent(string msg);
};

