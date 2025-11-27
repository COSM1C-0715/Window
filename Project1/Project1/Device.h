#include<d3d12.h>
#include<dxgi1_4.h>
#include"Adapter.h"
#pragma once
class Device
{
public:
	ID3D12Device* device;
public:
	Device() = default;
	~Device();
	bool CreateD3D12Device(Adapter& adapter);
	ID3D12Device* GetDevice();
};

