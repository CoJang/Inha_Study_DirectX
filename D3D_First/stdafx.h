// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include <iostream>
#include <vector>
#include <string>
#include <assert.h> // 예외처리, 경고를 위한 헤더

#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

using namespace std;

extern HWND g_hwnd;

#define SafeRelease(p) { if(p) p->Release(); p = NULL; }
#define SafeDeleteArray(p) {if(p) delete[] p; p=NULL;}
#define SafeDelete(p) { if(p) delete p; p = NULL; }
#define SafeAddRef(p) { if (p) p->AddRef(); }
#define Singletone(class_name) \
		private : \
			class_name(void) ; \
			~class_name(void) ; \
		public : \
				static class_name* GetInstance() \
				{	\
					static class_name instance ; \
					return &instance; \
				}

#define  Synthesize(varType, varName, FunName)\
   protected: varType varName ; \
   public: inline varType Get##FunName(void) const { return varName; } \
   public: inline void Set##FunName(varType var) { varName = var; }

#define Synthesize_pass_by_Ref(varType, varName, FunName)\
   protected: varType varName; \
   public: inline varType & Get##FunName(void)  { return varName; } \
   public: inline void Set##FunName(varType & var) { varName = var; }

#define Synthesize_Add_Ref(varType, varName, funName) \
	protected: varType varName; \
	public : virtual varType Get##funName(void) const { return varName; } \
	public : virtual void  Set##funName(varType var) \
	{ \
		if(varName != var) \
		{ \
			SafeAddRef(var); \
			SafeRelease(varName); \
			varName = var; \
		} \
	}

struct Ray
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Dir;
};

// point & color
struct PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

// point & normal & texture
struct PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2	t;

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2	t;

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

//회전과 이동처리에 관한 구조체
struct ST_POS_SAMPLE
{
	int n;
	D3DXVECTOR3 v;
	ST_POS_SAMPLE()
		:n(0)
		, v(0, 0, 0)
	{}//구조체 안에서 초기화 가능하다
};

struct ST_ROT_SAMPLE
{
	int n;
	D3DXQUATERNION q;
	ST_ROT_SAMPLE()
		:n(0)
	{
		D3DXQuaternionIdentity(&q);
	}

};

#include "MyMath.h"
#include "ManagerSrc/DeviceManager.h"
#include "ObjectSrc/ObjData.h"
#include "ObjectSrc/ObjectManager.h"
#include "ObjectSrc/TextureManager.h"
#include "UIManager.h"

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif