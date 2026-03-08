#include "GameObject.h"
#include"ShapeContainer.h"
#include<DirectXMath.h>
namespace
{
	struct ConstBufferData
	{
		DirectX::XMMATRIX World{};
		DirectX::XMFLOAT4 Color{};
	};
}

void GameObject::Initialize()
{
	CreateDrawBuffer();
}

void GameObject::SetDrawCommand(Command_List& commandList, UINT slot)
{
	Objects::SetDrawCommand(commandList,slot);
	ShapeContainer::instance().Draw(commandList,ShapeId_);
}

void GameObject::CreateDrawBuffer()
{
	if (!ConstantBuffer_.Createcostantbuffer(sizeof(ConstBufferData)));
	{
		assert(false && "GameObject コンスタントバッファの作成に失敗しました");
	}
}

void GameObject::UpdateDrawBuffer()
{
	Objects::UpdateConstantBuffer(ConstBufferData{DirectX::XMMatrixTranspose(World),Color});
}

void GameObject::SetHandle(UINT64 handle)
{
	Handle_ = handle;
}

UINT64 GameObject::Handle()
{
	Handle_;
}

void GameObject::Set(DirectX::XMFLOAT3 Pos, DirectX::XMFLOAT3 Rot, DirectX::XMFLOAT3 Scale,DirectX::XMFLOAT4 color,UINT64 ShapeId)
{
	DirectX::XMMATRIX matScale = DirectX::XMMatrixScaling(Scale.x,Scale.y,Scale.z);
	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw(Rot.x,Rot.y,Rot.z);
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(Pos.x,Pos.y,Pos.z);
	World = matScale * rotation * translation;

	Color = color;

	ShapeId_ = ShapeId;
}
