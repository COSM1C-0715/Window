#include<d3d12.h>
#include"Device.h"
#include"Descriptor_Heap.h"
#include"Window.h"
#pragma once
class Depth_buffer
{
public:
	ID3D12Resource* depthbuffer;
	D3D12_CPU_DESCRIPTOR_HANDLE handle;
public:
	Depth_buffer() = default;
	~Depth_buffer();
	bool CreateDepthBuffer(Device& device,Descriptor_Heap& heap,Window& window);
	ID3D12Resource* GetDepthbuffer();
	D3D12_CPU_DESCRIPTOR_HANDLE Gethandle();
};

