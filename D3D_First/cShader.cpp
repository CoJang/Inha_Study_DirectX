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

	// ���̴� �ε��� ������ ��� outputâ�� ���̴�
	// ������ ������ ����Ѵ�.
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
		OutputDebugStringA("�ؽ�ó �ε� ����: ");
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
		OutputDebugStringA("�� �ε� ����: ");
		OutputDebugStringA(filename);
		OutputDebugStringA("\n");
	};

	return ret;
}
