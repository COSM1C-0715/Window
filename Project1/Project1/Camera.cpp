#include "Camera.h"
#include "Input.h"
#include<cmath>

namespace
{
	float eyeMoveSpeed = 1.0f;
	float destTargetToView = -5.0f;
}

void Camera::initialize()
{
	position = DirectX::XMFLOAT3(0.0f,0.0f,destTargetToView);

	target = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	up = DirectX::XMFLOAT3(0.0f,1.0f,0.0f);

	projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4,1280.0f / 720.0f,0.1f,100.0f);
}

void Camera::update()
{
	static float angle = 0.0f;

	if (Input::instance().getKey(VK_LEFT))
	{
		angle += eyeMoveSpeed;
		position.x = destTargetToView * std::sinf(angle);
		position.z = destTargetToView * std::cosf(angle);
	}
	else if (Input::instance().getKey(VK_RIGHT))
	{
		angle -= eyeMoveSpeed;
		position.x = destTargetToView * std::sinf(angle);
		position.z = destTargetToView * std::cosf(angle);
	}

	view = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&target), DirectX::XMLoadFloat3(&up));
}

DirectX::XMMATRIX XM_CALLCONV Camera::ViewMatrix()
{
	return view;
}

DirectX::XMMATRIX XM_CALLCONV Camera::Projection()
{
	return projection;
}
