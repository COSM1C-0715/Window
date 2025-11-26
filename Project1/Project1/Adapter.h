#include<d3d12.h>
#include<dxgi1_4.h>
#pragma once
class Adapter
{
public:
	IDXGIAdapter1* Getadapter;
public:
	Adapter();
	~Adapter();

	IDXGIAdapter* GetHardwareAdapter(IDXGIFactory4* factory);
};

