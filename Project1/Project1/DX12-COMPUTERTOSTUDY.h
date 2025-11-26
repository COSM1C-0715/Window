#include<Windows.h>
#include<d3d12.h>
#include<dxgi1_4.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;
#pragma once
class DX12
{	
public:
	IDXGIFactory4* factory;

	ID3D12CommandQueue* commandQueue;

	IDXGISwapChain1* swapChain1;

	IDXGISwapChain3* swapChain;
public:
	DX12();
	~DX12();
	IDXGIFactory4* CreateDXGIFactory();
	ID3D12CommandQueue* CreateCommandQueue(ID3D12Device* device);
	IDXGISwapChain3* CreateSwapChain(IDXGIFactory4* factory, ID3D12CommandQueue* commandQueue, HWND hwnd);
	void EnableDebugLayer();
};

