#pragma once

#define g_pDeviceManager DeviceManager::GetInstance()
#define g_pDevice DeviceManager::GetInstance()->GetDevice()

class DeviceManager
{
	Singletone(DeviceManager);

private:
	LPDIRECT3DDEVICE9 Device;
	
public:
	void InitDeviceManager();
	void Destroy();
	
	LPDIRECT3DDEVICE9 GetDevice() { return Device; }
};

