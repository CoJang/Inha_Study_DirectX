// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <iostream>
#include <vector>
#include <string>
#include <assert.h> // 예외처리, 경고를 위한 헤더
#include <map>

#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

using namespace std;

extern HWND g_hwnd;

#define SafeRelease(p) { if(p) p->Release(); p = NULL; }
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

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include "DeviceManager.h"