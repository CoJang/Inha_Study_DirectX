// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <assert.h>//예외처리 할 때 경고문 사용하기 위해 사용
#include <iostream>

#include<d3dx9.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

using namespace std;

extern HWND g_hWnd;
#define SafeRelease(p)	{if(p) p->Release(); p = NULL;}
#define SafeDelete(p) {if(p) delete p; p = NULL;}
#define SafeDeleteArray(p) {if(p) delete[] p; p=NULL;}

#define Singletone(class_name)\
	private:\
	class_name(void);\
	~class_name(void);\
	public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
	return &instance;\
	}

struct ST_PC_VERTEX 
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DCOLOR c;
	
	enum {FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;
	enum {FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1};
};

struct ST_PT_VERTEX 
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;
	enum {FVF = D3DFVF_XYZ | D3DFVF_TEX1};
};

struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
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

struct ST_SPHERE 
{
	float fRadius;
	D3DXVECTOR3 vCenter;
	bool isPicked;
	ST_SPHERE() : fRadius(0.0f), vCenter(0, 0, 0) {}
};


#define Synthesize(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const {return varName;}\
public: inline void Set##funName(varType var) {varName = var;}

#define Synthesize_Pass_by_Ref(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) {return varName;}\
public: inline void Set##funName(varType& var) {varName = var;}

#define SafeAddRef(p) {if(p) p->AddRef();}

#define Synthesize_Add_Ref(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const {return varName;}\
public:virtual void Set##funName(varType var){\
	if(varName != var)\
	{\
		SafeAddRef(var);\
		SafeRelease(varName);\
		varName = var;\
	}\
}

//================================================================
#include "iMap.h"
#include "cDeviceManage.h"
#include "cObject.h"
#include "cObjectManager.h"
#include "cTextureManager.h"
#include "cTimerManager.h"
#include "cFontManager.h"