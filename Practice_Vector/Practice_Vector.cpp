#include "stdafx.h"
#include "MyVector3.h"

/*
	1. º¤ÅÍ ºñ±³
	2. º¤ÅÍ µ¡¼À
	3. ³»Àû
	4. ¿ÜÀû

	°¢ case Ãâ·Â
*/
void PrintVector3(const MyVector3 & v)
{
	printf("x : %f\n", v.x);
	printf("y : %f\n", v.y);
	printf("z : %f\n\n", v.z);
}


int main()
{
	MyVector3 Vector1 = { 1.5f, 1.1232f, 3.1238f };
	MyVector3 Vector2 = { 6, 7, -1 };

	PrintVector3(Vector1);
	PrintVector3(Vector2);

	MyVector3 Vector3 = MyVector3::Cross(Vector1, Vector2);
	PrintVector3(Vector3);
	printf("Vector1 Dot Vector2 : %f\n\n", MyVector3::Dot(Vector1, Vector2));

	printf("Vector1 Length() : %f\n\n", Vector1.Length());
	Vector1.Normalize();
	PrintVector3(Vector1);
	printf("Vector1 Length() : %f\n\n", Vector1.Length());
	if (Vector1 == Vector2)
	{
		printf("Vector1, Vector2 is Equal! \n\n");
	}
	if (Vector1 != Vector2)
	{
		printf("Vector1, Vector2 is Not Equal! \n\n");
	}

	Vector1.Normalize(); Vector2.Normalize();
	float Result = MyVector3::Dot(Vector1, Vector2);
	printf("Vector1 Dot Vector2 : %f\n\n", Result);

	printf("Vector1, Vector2's Angle : %f\n\n", MyVector3::Angle(Vector1, Vector2));

    return 0;
}

