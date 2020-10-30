#include "stdafx.h"
#include "cShader.h"


LPD3DXEFFECT LoadShader(const char * filename)
{
	LPD3DXEFFECT ret = NULL;

	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFileA(DEVICE, filename,
		NULL, NULL, dwShaderFlags, NULL, &ret, &pError);

	// 쉐이더 로딩에 실패한 경우 output창에 쉐이더
	// 컴파일 에러를 출력한다.
	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void *ack = pError->GetBufferPointer();

		if (ack)
		{
			char* str = new char[size];
			sprintf(str, (const char*)ack, size);
			OutputDebugStringA(str);
			delete[] str;
		}
	}

	return ret;
}

LPDIRECT3DTEXTURE9 LoadTexture(const char * filename)
{
	LPDIRECT3DTEXTURE9 ret = NULL;
	if (FAILED(D3DXCreateTextureFromFileA(DEVICE, filename, &ret)))
	{
		OutputDebugStringA("텍스처 로딩 실패: ");
		OutputDebugStringA(filename);
		OutputDebugStringA("\n");
	}

	return ret;
}

LPD3DXMESH LoadModel(const char * filename)
{
	LPD3DXMESH ret = NULL;
	if (FAILED(D3DXLoadMeshFromXA(filename, D3DXMESH_SYSTEMMEM, DEVICE, NULL, NULL, NULL, NULL, &ret)))
	{
		OutputDebugStringA("모델 로딩 실패: ");
		OutputDebugStringA(filename);
		OutputDebugStringA("\n");
	};

	return ret;
}
