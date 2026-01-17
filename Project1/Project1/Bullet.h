#pragma once
#include<functional>
#include<d3d12.h>
#include<dxgi1_4.h>
#include<wrl/client.h>
#include"Device.h"
class Bullet
{
public:
	Microsoft::WRL::ComPtr<ID3D12Resource> bullet_vertexbuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource> bullet_indexbuffer;
public:
	Bullet() = default;
	~Bullet() = default;
	bool createvertex(Device& device);
	bool createindex(Device& device);
};