#include<Windows.h>
#include<d3d12.h>
#include<dxgi1_4.h>
#pragma once
class DXGI
{	
public:
	IDXGIFactory4* factory;

	IDXGIAdapter1* Getadapter;
public:
	DXGI() = default;
	~DXGI();
	bool SetDisplayAdapter();
	IDXGIFactory4* FActroy();
	IDXGIAdapter1* adapter();
	void enabledebugLayer();
};

