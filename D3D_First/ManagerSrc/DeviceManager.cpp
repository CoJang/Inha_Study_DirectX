#include "stdafx.h"
#include "DeviceManager.h"


DeviceManager::DeviceManager()
	: Device(NULL)
{
	InitDeviceManager();
}


DeviceManager::~DeviceManager()
{
	SafeRelease(Device);
}

void DeviceManager::InitDeviceManager()
{
	IDirect3D9* _d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	_d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	int nVertexProcessing = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	//d3dpp.BackBufferWidth = 800;
	//d3dpp.BackBufferHeight = 600;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	//d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	//d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hwnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	//d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	Device = 0;
	HRESULT hr = _d3d9->CreateDevice
	(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hwnd,
		nVertexProcessing,
		&d3dpp,
		&Device
	);

	if (FAILED(hr))
	{
		::MessageBox(0, TEXT("CreateDevice() - FAILED!"), 0, 0);
		return;
	}

	Device->SetRenderState(D3DRS_ZENABLE, true);
}

void DeviceManager::Destroy()
{
	SafeRelease(Device);
}
