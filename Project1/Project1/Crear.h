#include<Windows.h>
#include<d3d12.h>
#include<dxgi1_4.h>
#include<vector>
#pragma once
class Crear
{
public:
	ID3D12DescriptorHeap* rtvHeap;

	D3D12_DESCRIPTOR_HEAP_TYPE _type;

	std::vector<ID3D12Resource*> rn_tgt;
public:
	Crear();
	~Crear();

	ID3D12DescriptorHeap* Create(ID3D12Device& device,D3D12_DESCRIPTOR_HEAP_TYPE type,UINT numDescriptors);
	D3D12_DESCRIPTOR_HEAP_TYPE gettype();
	D3D12_CPU_DESCRIPTOR_HANDLE gethandle(ID3D12Device& device,ID3D12DescriptorHeap& heap,UINT index);
};

