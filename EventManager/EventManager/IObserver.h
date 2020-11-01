#pragma once

class IObserver
{
public:
	IObserver() = default;
	virtual ~IObserver() = default;

	virtual void ReceiveEvent(string event) = 0;
};

