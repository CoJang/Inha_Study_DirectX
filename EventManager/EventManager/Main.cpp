// EventManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConcreteObserverA.h"
#include "Subject.h"

int main()
{
	ConcreteObserverA* ObsA = new ConcreteObserverA;
	Subject* Cojang = new Subject;


	ObsA->Subscribe("YouTube", Cojang);
	Cojang->SendEvent("YouTube", "�ȳ��ϼ��� ��Ʃ�� ������ ������");

	delete Cojang;
	delete ObsA;
    return 0;
}

