#pragma once
#include<DirectXMath.h>
#include<d3d12.h>
class Object_Bullet
{
private:
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1.0f,1.0f, 1.0f, 1.0f);
	UINT64 typeId;
public:
	struct ConstantBuffer
	{
		DirectX::XMMATRIX world{};
		DirectX::XMFLOAT4 color{};
	};
public:
	Object_Bullet() = default;
	~Object_Bullet() = default;

	void initialize(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT4 color_);
	void update();

	UINT64 typeId()
	{
		return typeId;
	};

	void SetTypeID(UINT64 id)
	{
		typeId = id;
	};

	DirectX::XMMATRIX World();

	DirectX::XMFLOAT4 Color();
};

