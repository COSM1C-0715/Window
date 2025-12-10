#include "Command_List.h"
#include<cassert>
Command_List::~Command_List()
{
	if (C_list)
	{
		C_list->Release();
		C_list = nullptr;
	}
}

bool Command_List::CreateGraphicsCommandList(Device& device, Command_Allocator& commandAllicator)
{
	auto hr = device.GetDevice()->CreateCommandList(0, commandAllicator.GetListType(), commandAllicator.GetC_Allo(), nullptr, IID_PPV_ARGS(&C_list));
	if (FAILED(hr))
	{
		assert(false && "コマンドリストの作成に失敗");
		return false;
	}
	C_list->Close();
	return true;
}

void Command_List::Reset(Command_Allocator& commandAllicator)
{
	if (!C_list)
	{
		assert(false && "コマンドリスト作れていませんが？");
	}

	C_list->Reset(commandAllicator.GetC_Allo(), nullptr);
}

ID3D12GraphicsCommandList* Command_List::GetCommandList()
{
	if (!C_list)
	{
		assert(false && "コマンドリストがなーい");
		return nullptr;
	}
	return C_list;
}
