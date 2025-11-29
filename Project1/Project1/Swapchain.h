#include<d3d12.h>
#include<dxgi1_4.h>
#include"DX12.h"
#pragma once
class Swapchain
{
public:
	IDXGISwapChain1* swapChain1;

	IDXGISwapChain3* swapChain;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
public:
	Swapchain() = default;
	~Swapchain();
	bool CreateSwapChain(DX12& factory, ID3D12CommandQueue* commandQueue, HWND hwnd);
	IDXGISwapChain3* GetSwapChain();
	DXGI_SWAP_CHAIN_DESC1& GetDesc();
};

