#pragma once
#include<DirectXMath.h>
class Object
{
private:
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f);

	float move = 0.02f;
public:
	struct ConstBuffer
	{
		DirectX::XMMATRIX world{};
		DirectX::XMFLOAT4 color{};
	};
public:
	Object() = default;
	~Object() = default;

	void initialize(DirectX::XMFLOAT3 pos,DirectX::XMFLOAT4 color_);

	void update();

	DirectX::XMMATRIX World();

	DirectX::XMFLOAT4 Color();
};

