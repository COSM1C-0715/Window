#include<d3d12.h>
#include<dxgi1_4.h>
#pragma once
class Swapchain
{
public:
	IDXGISwapChain1* swapChain1;

	IDXGISwapChain3* swapChain;
public:
	Swapchain() = default;
	~Swapchain();
	IDXGISwapChain3* CreateSwapChain(IDXGIFactory4* factory, ID3D12CommandQueue* commandQueue, HWND hwnd);
};

