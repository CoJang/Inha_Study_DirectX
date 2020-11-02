//#include "framework.h"
#include "MyMath.h"


float Lerp(float a, float b, float t)
{
	return a - (a * t) + (b * t);
}
