#include<d3d12.h>
#include<dxgi1_4.h>
#include"Device.h"
#pragma once
class Command_Allocator
{
public:
	ID3D12CommandAllocator* C_Allo;

	D3D12_COMMAND_LIST_TYPE List_Type;
public:
	Command_Allocator() = default;

	~Command_Allocator();

	bool CreateAllocator(Device& device, D3D12_COMMAND_LIST_TYPE type);

	void Reset();

	ID3D12CommandAllocator* GetC_Allo();

	D3D12_COMMAND_LIST_TYPE GetListType();
};

