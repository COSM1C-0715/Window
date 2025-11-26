#include<d3d12.h>
#include<dxgi1_4.h>
#pragma once
class Device
{
public:
	ID3D12Device* device;
public:
	Device();
	~Device();
	ID3D12Device* CreateD3D12Device(IDXGIAdapter1* adapter);
};

