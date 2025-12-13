#include<d3d12.h>
#include<dxgi1_4.h>
#include"DXGI.h"
#include"CommandQueue.h"
#include"Window.h"
#pragma once
class Swapchain
{
public:
	IDXGISwapChain3* swapChain;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
public:
	Swapchain() = default;
	~Swapchain();
	bool CreateSwapChain(DXGI& factory, CommandQueue& commandQueue, Window& window);
	IDXGISwapChain3* GetSwapChain();
	DXGI_SWAP_CHAIN_DESC1& GetDesc();
};

