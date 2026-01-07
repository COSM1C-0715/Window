#pragma once
#include<DirectXMath.h>
class Camera
{
private:
	DirectX::XMMATRIX view{};
	DirectX::XMMATRIX projection{};

	DirectX::XMFLOAT3 position{};
	DirectX::XMFLOAT3 target{};
	DirectX::XMFLOAT3 up{};
public:
	struct ConstBuffer
	{
		DirectX::XMMATRIX view{};
		DirectX::XMMATRIX projection{};
	};
public:
	Camera() = default;
	~Camera() = default;
public:
	void initialize();

	void update();

	DirectX::XMMATRIX XM_CALLCONV ViewMatrix();

	DirectX::XMMATRIX XM_CALLCONV Projection();
};

