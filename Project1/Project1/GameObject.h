#pragma once
#include<d3d12.h>
#include<DirectXMath.h>
#include"Objects.h"
class GameObject : Objects
{
public:
	GameObject() = default;
	GameObject(UINT64 parent) : Parent_(parent) {}

	virtual ~GameObject() = default;
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void SetDrawCommand(Command_List& commandList, UINT Slot) override;
public:
	virtual void CreateDrawBuffer() override;
	virtual void UpdateDrawBuffer() override;
public:
	void SetHandle();
	UINT64 Handle();
	void Set(DirectX::XMFLOAT3 Pos, DirectX::XMFLOAT3 Rot, DirectX::XMFLOAT3 Scale);
protected:
	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT4 Color = DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f);
	UINT64 ShapeId_{};
	UINT64 Handle_{};
	UINT64 Parent_{};
};

