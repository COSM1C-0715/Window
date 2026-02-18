#pragma once
#include<DirectXMath.h>
#include"Command_List.h"
#include<wrl/client.h>
class Shape
{
public:
	struct ConstBufferData
	{
		DirectX::XMMATRIX world{};
		DirectX::XMFLOAT4 color{};
	};
public:
	Shape() = default;

	virtual ~Shape() = default;

	bool Create();

	void Draw(Command_List& commandList);
protected:
	virtual bool CreateVertexBuffer() = 0;

	virtual bool CreateIndexBuffer() = 0;
protected:
	Microsoft::WRL::ComPtr<ID3D12Resource> VertexBuffer_{};
	Microsoft::WRL::ComPtr<ID3D12Resource> IndexBuffer_{};
	D3D12_VERTEX_BUFFER_VIEW VBV_{};
	D3D12_INDEX_BUFFER_VIEW IBV_{};
	D3D_PRIMITIVE_TOPOLOGY Toporogy_;
	UINT IndexCount_{};
};

