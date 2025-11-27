#include<Windows.h>
#include<d3d12.h>
#include<dxgi1_4.h>
#pragma once
class DX12
{	
public:
	IDXGIFactory4* factory;
public:
	DX12() = default;
	~DX12();
	bool CreateDXGIFactory();
	IDXGIFactory4* Factory();
	void EnableDebugLayer();
};

