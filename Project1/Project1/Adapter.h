#include<d3d12.h>
#include<dxgi1_4.h>
#pragma once
class Adapter
{
public:
	IDXGIAdapter1* Getadapter;
public:
	Adapter() = default;
	~Adapter();

	bool GetHardwareAdapter(IDXGIFactory4* factory);
	IDXGIAdapter1* adapter();
};

