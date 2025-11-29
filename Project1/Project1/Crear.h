#include<Windows.h>
#include<d3d12.h>
#include<dxgi1_4.h>
#include<vector>
#include"Device.h"
#include"Swapchain.h"
#pragma once
class Crear
{
public:
	ID3D12DescriptorHeap* rtvHeap;

	D3D12_DESCRIPTOR_HEAP_TYPE _type;

	std::vector<ID3D12Resource*> rn_tgt;

	std::vector<ID3D12CommandAllocator*> C_Allos;
public:
	Crear() = default;
	~Crear();

	bool Create(Device& device,D3D12_DESCRIPTOR_HEAP_TYPE type,UINT numDescriptors);
	bool CreateBckBffr(Device& device,Swapchain& swapchain,Crear& heap);
	ID3D12DescriptorHeap* GetHeap();
	D3D12_DESCRIPTOR_HEAP_TYPE gettype();
	D3D12_CPU_DESCRIPTOR_HANDLE gethandle(Device& device,Crear& heap,UINT index);
	ID3D12Resource* GetResource(uint32_t index);
};

