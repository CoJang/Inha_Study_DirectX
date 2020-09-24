#pragma once

#define DEVICEMANAGER DeviceManager::GetInstance()
#define DEVICE DeviceManager::GetInstance()->GetDevice()

class DeviceManager
{
	Singletone(DeviceManager);

private:
	LPDIRECT3DDEVICE9 Device;
	
public:
	void InitDeviceManager();
	void Destroy();
	
	inline LPDIRECT3DDEVICE9 GetDevice() { return Device; }
};

