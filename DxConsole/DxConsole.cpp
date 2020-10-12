#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include "DxConsole.h"


int main()
{
	D3DXVECTOR3 Vertex[3];

	Vertex[0] = D3DXVECTOR3(0, 0, 0);
	Vertex[1] = D3DXVECTOR3(3, 0, 0);
	Vertex[2] = D3DXVECTOR3(0, 0, -3);

	D3DXVECTOR3 RayPos = D3DXVECTOR3(1, 1, 0);
	D3DXVECTOR3 RayDir = D3DXVECTOR3(0, -1, 0);

	D3DXVec3Normalize(&RayDir, &RayDir);
	
	float _U(0), _V(0);
	float _Dist(0);
	bool IsHit = false;
	IsHit = D3DXIntersectTri(&Vertex[0], &Vertex[1], &Vertex[2], &RayPos, &RayDir, &_U, &_V, &_Dist);

	if(IsHit)
	{
		cout << "Ray Hit!" << endl;
		cout << "UV : (" << _U << ", " << _V << ")" << endl;
		cout << "Dist : " << _Dist << endl;
	}
	else
	{
		cout << "Ray Missed!" << endl;
	}
}

