#include<iostream>
#include<cassert>
#include<Windows.h>
#include"DXGI.h"
#include"Device.h"
#include"Command_Allocator.h"
#include"Command_List.h"
#include"CommandQueue.h"
#include"Swapchain.h"
#include"Descriptor_Heap.h"
#include"Render_Target.h"
#include"Fence.h"
#include"Window.h"

class Application
{
public:
	Application() = default;
	~Application() = default;

	bool initialize(HINSTANCE instance)
	{
		if (S_OK !=W_Instance.createWindow(instance,1280,720, "GameWindow"))
		{
			assert(false && "ウィンドウ作成しっぱーい");
			return false;
		}

		if (!DX_Instance.SetDisplayAdapter())
		{
			assert(false && "ディスプレイアダプター作成しっぱーい");
			return false;
		}

		if (!D_Instance.CreateD3D12Device(DX_Instance))
		{
			assert(false && "残念");
			return false;
		}

		if (!CQ_Instance.CreateCommandQueue(D_Instance))
		{
			assert(false&& "コマンドキュー作れてないがー？");
			return false;
		}
		if (!S_Instance.CreateSwapChain(DX_Instance,CQ_Instance,W_Instance))
		{
			assert(false && "スワップチェインが....ない!");
			return false;
		}
		if (!DH_Instance.Create(D_Instance,D3D12_DESCRIPTOR_HEAP_TYPE_RTV,S_Instance.GetDesc().BufferCount))
		{
			assert(false && "ディスクリプターヒープが....ない!");
			return false;
		}
		if (!R_Instance.CreateBckBffr(D_Instance, S_Instance, DH_Instance))
		{
			assert(false && "レンダーターゲットが....ない!");
			return false;
		}
		if (!CA_Instance[0].CreateAllocator(D_Instance,D3D12_COMMAND_LIST_TYPE_DIRECT))
		{
			assert(false&&"一個目のアロケータが....ない!");
			return false;
		}
		if (!CA_Instance[1].CreateAllocator(D_Instance, D3D12_COMMAND_LIST_TYPE_DIRECT))
		{
			assert(false && "二個目のアロケータが....ない!");
			return false;
		}
		if (!CL_Instance.CreateGraphicsCommandList(D_Instance,CA_Instance[0]))
		{
			assert(false&&"コマンドリストが......ない!");
			return false;
		}
		if (!F_Instance.CreateFence(D_Instance))
		{
			assert(false && "フェンスが......ない!");
			return false;
		}
		return true;
	}

	void loop()
	{
		while (W_Instance.MassageLoop())
		{
			auto bckbffrIndex = S_Instance.GetSwapChain()->GetCurrentBackBufferIndex();

			if (FrameFenceValue[bckbffrIndex] != 0)
			{
				F_Instance.Wait(FrameFenceValue[bckbffrIndex]);
			}

			CA_Instance[bckbffrIndex].Reset();

			CL_Instance.Reset(CA_Instance[bckbffrIndex]);

			auto pToRT = resourceBarrier(R_Instance.GetResource(bckbffrIndex), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
			CL_Instance.GetCommandList()->ResourceBarrier(1, &pToRT);

			D3D12_CPU_DESCRIPTOR_HANDLE handles[] = { R_Instance.gethandle(D_Instance,DH_Instance,bckbffrIndex) };
			CL_Instance.GetCommandList()->OMSetRenderTargets(1, handles, false, nullptr);

			float clearColor[] = {0.2f,0.6f,0.3f,1.0f};
			CL_Instance.GetCommandList()->ClearRenderTargetView(handles[0], clearColor, 0, nullptr);

			auto rtToP = resourceBarrier(R_Instance.GetResource(bckbffrIndex), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
			CL_Instance.GetCommandList()->ResourceBarrier(1, &rtToP);

			CL_Instance.GetCommandList()->Close();

			ID3D12CommandList* ppCommandLists[] = { CL_Instance.GetCommandList() };
			CQ_Instance.Getcommandqueue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

			S_Instance.GetSwapChain()->Present(1, 0);

			CQ_Instance.Getcommandqueue()->Signal(F_Instance.GetFence(), nextFenceValue);
			FrameFenceValue[bckbffrIndex] = nextFenceValue;
			nextFenceValue++;
		}
	}

	D3D12_RESOURCE_BARRIER resourceBarrier(ID3D12Resource* resource,D3D12_RESOURCE_STATES from, D3D12_RESOURCE_STATES to)
	{
		D3D12_RESOURCE_BARRIER barrier{};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = resource;
		barrier.Transition.StateBefore = from;
		barrier.Transition.StateAfter = to;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

		return barrier;
	}
private:
	Window W_Instance{};
	DXGI DX_Instance{};
	Device D_Instance{};
	CommandQueue CQ_Instance{};
	Swapchain S_Instance{};
	Descriptor_Heap DH_Instance{};
	Render_Target R_Instance{};
	Command_Allocator CA_Instance[2]{};
	Command_List CL_Instance{};

	Fence F_Instance{};
	UINT64 FrameFenceValue[2]{};
	UINT64 nextFenceValue = 1;
};

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	Application app;

	if (!app.initialize(hInstance))
	{
		assert(false&&"アプリケーションの初期化に失敗");
	}

	app.loop();

	return 0;
}