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

	IDXGIAdapter1* adapter;
public:
	DX12(unsigned int width, unsigned int height);
	~DX12();
	IDXGIFactory4* CreateDXGIFactory();
	IDXGIAdapter* GetHardwareAdapter(IDXGIFactory4* factory);
	ID3D12Device* CreateD3D12Device(IDXGIAdapter1* adapter);
	ID3D12CommandQueue* CreateCommandQueue(ID3D12Device* device);
	IDXGISwapChain3* CreateSwapChain(IDXGIFactory4* factory, ID3D12CommandQueue* commandQueue, HWND hwnd);
	void EnableDebugLayer();

	void OnInit(HWND hWnd);

	void OnRender();

	void OnDestroy();

	ComPtr<ID3D12DescriptorHeap> _rtvHeaps;
	//ComPtr<ID3D12Resource> _renderTargets[];
	ComPtr<ID3D12Fence> _fence;
};

