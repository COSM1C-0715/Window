#pragma once
#include<functional>
#include<d3d12.h>
#include<dxgi1_4.h>
#include<wrl/client.h>
#include"Device.h"
#include"Command_List.h"
class Bullet
{
public:
	Microsoft::WRL::ComPtr<ID3D12Resource> bullet_vertexbuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource> bullet_indexbuffer;

	D3D12_VERTEX_BUFFER_VIEW bullet_vbv;
	D3D12_INDEX_BUFFER_VIEW bullet_ibv;
public:
	Bullet() = default;
	~Bullet() = default;
	bool createvertex(Device& device);
	bool createindex(Device& device);

	void BulletDraw(Command_List& C_List);
};