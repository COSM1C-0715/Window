#include<Windows.h>
#include<d3d12.h>
#include<dxgi1_4.h>
#include <wrl.h>
#pragma once
class DX12
{	
public:
	IDXGIFactory4* factory;

	IDXGIAdapter1* adapter;

	ID3D12Device* device;

	ID3D12CommandQueue* commandQueue;

	IDXGISwapChain1* swapChain1;

	IDXGISwapChain3* swapChain;
public:
	DX12();
	~DX12();
	IDXGIFactory4* CreateDXGIFactory();
	IDXGIAdapter* GetHardwareAdapter(IDXGIFactory4* factory);
	ID3D12Device* CreateD3D12Device(IDXGIAdapter1* adapter);
	ID3D12CommandQueue* CreateCommandQueue(ID3D12Device* device);
	IDXGISwapChain3* CreateSwapChain(IDXGIFactory4* factory, ID3D12CommandQueue* commandQueue, HWND hwnd);
	void EnableDebugLayer();
};

