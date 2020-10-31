#pragma once

class IObserver
{
public:
	IObserver() = default;
	virtual ~IObserver() = default;

	virtual void Update(string event) = 0;
};

