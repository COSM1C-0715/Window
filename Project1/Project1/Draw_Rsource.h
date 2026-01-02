#include<d3d12.h>
#include <dxgi1_4.h>
#include"Device.h"
#include"Command_List.h"
#include<DirectXMath.h>
#pragma once
class Draw_Rsource
{
public:
	ID3D12Resource* VertexBuffer;
	ID3D12Resource* IndexBuffer;

	D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
	D3D12_INDEX_BUFFER_VIEW IndexBufferView;
public:
	Draw_Rsource() = default;
	~Draw_Rsource();

	struct ConstBufferData
	{
		DirectX::XMMATRIX world{};
		DirectX::XMFLOAT4 color{};
	};
	bool createVertexBuffer(Device& device);
	bool createIndexBuffer(Device& device);

	void Draw(Command_List& commandlist);
	bool Create(Device& device);
};