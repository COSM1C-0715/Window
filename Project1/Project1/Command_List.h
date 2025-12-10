#include<d3d12.h>
#include<dxgi1_4.h>
#include"Device.h"
#include"Command_Allocator.h"
#pragma once
class Command_List
{
public:
	ID3D12GraphicsCommandList* C_list;
public:
	Command_List() = default;
	~Command_List();
	bool CreateGraphicsCommandList(Device& device, Command_Allocator& commandAllicator);
	void Reset(Command_Allocator& C_allocator);
	ID3D12GraphicsCommandList* GetCommandList();
};