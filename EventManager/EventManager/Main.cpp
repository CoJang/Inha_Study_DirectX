// EventManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConcreteObserverA.h"
#include "Subscriber.h"

int main()
{
	ConcreteObserverA* ObsA = new ConcreteObserverA;
	Subscriber* Cojang = new Subscriber;

	Cojang->Subscribe("YouTube", NULL);
	Cojang->SendEvent("YouTube", "Thumb Up!");


	
    return 0;
}

