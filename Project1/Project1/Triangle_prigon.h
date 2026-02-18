#pragma once
#include<d3d12.h>
#include <dxgi1_4.h>
#include"Device.h"
#include"Command_List.h"
#include <wrl/client.h>
#include<DirectXMath.h>
#include"About_GameObject.h"
#include"Shape.h"
class Triangle_prigon : public Shape
{
public:
	Microsoft::WRL::ComPtr<ID3D12Resource> TriangleVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource> TriangleIndexBuffer;

	D3D12_VERTEX_BUFFER_VIEW Triangle_VBV;
	D3D12_INDEX_BUFFER_VIEW  Triangle_IBV;
public:
	Triangle_prigon() = default;
	~Triangle_prigon() = default;

private:
	bool CreateVertexBuffer() override;
	bool CreateIndexBuffer() override;

	void Draw(Command_List& commandlist);
	bool Create(Device& device);
};

