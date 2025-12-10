#include "Fence.h"
#include"Device.h"
#include<Windows.h>
#include<d3d12.h>
#include<cassert>

Fence::~Fence()
{
	if (fence)
	{
		fence->Release();
		fence = nullptr;
	}
}

bool Fence::CreateFence(Device& device)
{
	HRESULT hr = device.GetDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));

	if (FAILED(hr))
	{
		assert(false&&"フェンスの作成に失敗！、誠に残念だ");
		return false;
	}
	waitGpuEvent = CreateEvent(nullptr, false, false, "WAIT_GPU");
	if (!waitGpuEvent)
	{
		assert(false&&"GPU同期用のイベントハンドルを作るの失敗しちゃった、あちゃー");
		return false;
	}
	return true;
}

void Fence::Wait(UINT64 fenceValue)
{
	if (!fence)
	{
		assert(false&&"フェンス作れてないよ？");
		return;
	}

	if (fence->GetCompletedValue() < fenceValue)
	{
		fence->SetEventOnCompletion(fenceValue, waitGpuEvent);
		WaitForSingleObject(waitGpuEvent, INFINITE);
	}
}

ID3D12Fence* Fence::GetFence()
{
	if (!fence)
	{
		assert(false&&"フェンスがなーーーーい！");
		return nullptr;
	}
	return fence;
}
