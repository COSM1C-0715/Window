#include "Command_Allocator.h"
#include<cassert>
Command_Allocator::~Command_Allocator()
{
	if (C_Allo)
	{
		C_Allo->Release();
		C_Allo = nullptr;
	}
}

bool Command_Allocator::CreateAllocator(Device& device, D3D12_COMMAND_LIST_TYPE type)
{
	type = List_Type;

	auto hr = device.GetDevice()->CreateCommandAllocator(type, IID_PPV_ARGS(&C_Allo));

	if (FAILED(hr))
	{
		assert(false && "コマンドアロケーターの作成に失敗！");
		return false;
	}

	return true;
}

void Command_Allocator::Reset()
{
	if (!C_Allo)
	{
		assert(false && "コマンドリスト作れていませんが？");
	}
	C_Allo->Reset();
}

ID3D12CommandAllocator* Command_Allocator::GetC_Allo()
{
	if (!C_Allo)
	{
		assert(false && "それはぁ～～違うよぉ～～");
		return nullptr;
	}
	return C_Allo;
}

D3D12_COMMAND_LIST_TYPE Command_Allocator::GetListType()
{
	if (!C_Allo)
	{
		assert(false && "コマンドリストのタイプが設定されてないよぉ");
	}
	return List_Type;
}
