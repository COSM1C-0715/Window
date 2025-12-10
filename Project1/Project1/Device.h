#include<d3d12.h>
#include<dxgi1_4.h>
#include"DXGI.h"
#pragma once
class Device
{
public:
	ID3D12Device* device;
public:
	Device() = default;
	~Device();
	bool CreateD3D12Device(DXGI& adapter);
	ID3D12Device* GetDevice();
};

