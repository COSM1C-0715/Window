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
#include"Root_Signature.h"
#include"Shader.h"
#include"Pipline_state_object.h"
#include"Depth_buffer.h"

#include"Constant_buffer.h"
#include"Camera.h"
#include"Object.h"
#include"Quad_polygon.h"
#include"Triangle_prigon.h"

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

		if (!QP_Instance.Create(D_Instance))
		{
			assert(false&&"四角形ポリゴンが...ない！");
			return false;
		}
		
		QuadObjectInstance.initialize({ 0.2f,0.0f,-0.1f }, {1,1,1,1});

		if (!TP_Instance.Create(D_Instance))
		{
			assert(false && "三角形ポリゴンが...ない！");
		}

		TriangleObjectInstance.initialize({0.5f,0.3f,-0.5f},{0.1f,0.1f,0.1f,0.1f});
		//BulletObjectInstance.initialize({0.5,0.0f,-0.5f},{1,0.5f,0.5f,1});

		if (!RS_Instance.Create(D_Instance))
		{
			assert(false && "ルートシグネチャーが...ない！");
			return false;
		}
		if (!SH_Instance.Create(D_Instance))
		{
			assert(false && "シェーダーが...ない！");
			return false;
		}
		if (!PSO_Instance.Create(D_Instance,SH_Instance,RS_Instance))
		{
			assert(false && "パイプラインステートオブジェクトが...ない！");
			return false;
		}

		Camera_Instance.initialize();

		if (!ConstantBufferDH_Instance.Create(D_Instance,D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,2,true))
		{
			assert(false&&"定数バッファ用ディスクリプターヒープが...ない！");
			return false;
		}
		if (!CameraConstantBufferInstance.Createcostantbuffer(D_Instance,ConstantBufferDH_Instance,sizeof(Camera::ConstBuffer),0))
		{
			assert(false&&"カメラ用コンスタントバッファが...ない！");
			return false;
		}
		if (!QuadPolygonConstantBufferInstance.Createcostantbuffer(D_Instance,ConstantBufferDH_Instance,sizeof(Object::ConstBuffer),1))
		{
			assert(false&&"四角形ポリゴン用コンスタントバッファが...ない！");
			return false;
		}
		if (!TrianglePolygonConstantBufferInstance.Createcostantbuffer(D_Instance, ConstantBufferDH_Instance, sizeof(Object::ConstBuffer), 1))
		{
			assert(false && "三角形ポリゴン用コンスタントバッファが...ない！");
			return false;
		}
		if (!depthBufferDescriptorHeapInstance.Create(D_Instance,D3D12_DESCRIPTOR_HEAP_TYPE_DSV,1))
		{
			assert(false && "デプスバッファ用ディスクリプターヒープが...ない！");
			return false;
		}
		if (!DB_Instance.CreateDepthBuffer(D_Instance, depthBufferDescriptorHeapInstance, W_Instance))
		{
			assert(false && "デプスバッファ用ディスクリプターヒープが...ない！");
			return false;
		}
		return true;
	}

	void loop()
	{
		while (W_Instance.MassageLoop())
		{
			Camera_Instance.update();

			QuadObjectInstance.update();

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

			float clearColor[] = {0.1f,0.35f,0.24f,0.2f};
			CL_Instance.GetCommandList()->ClearRenderTargetView(handles[0], clearColor, 0, nullptr);

			CL_Instance.GetCommandList()->SetPipelineState(PSO_Instance.GetPipeline());

			CL_Instance.GetCommandList()->SetGraphicsRootSignature(RS_Instance.GetSignature());

			auto [w, h] = W_Instance.size();
			D3D12_VIEWPORT viewport{};
			viewport.TopLeftX = 0.0f;
			viewport.TopLeftY = 0.0f;
			viewport.Width = static_cast<float>(w);
			viewport.Height = static_cast<float>(h);
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			CL_Instance.GetCommandList()->RSSetViewports(1,&viewport);

			D3D12_RECT scissorRect{};
			scissorRect.left = 0;
			scissorRect.top = 0;
			scissorRect.right = w;
			scissorRect.bottom = h;
			CL_Instance.GetCommandList()->RSSetScissorRects(1,&scissorRect);

			ID3D12DescriptorHeap* p[] = {ConstantBufferDH_Instance.GetHeap()};
			CL_Instance.GetCommandList()->SetDescriptorHeaps(1,p);

			Camera::ConstBuffer cameraData
			{
				DirectX::XMMatrixTranspose(Camera_Instance.ViewMatrix()),
				DirectX::XMMatrixTranspose(Camera_Instance.Projection()),
			};

			UINT8* pCameraData{};

			CameraConstantBufferInstance.ConstantBuffer()->Map(0, nullptr, reinterpret_cast<void**>(&pCameraData));
			memcpy_s(pCameraData, sizeof(cameraData), &cameraData, sizeof(cameraData));
			CameraConstantBufferInstance.ConstantBuffer()->Unmap(0,nullptr);
			CL_Instance.GetCommandList()->SetGraphicsRootDescriptorTable(0, CameraConstantBufferInstance.getGpuDescriptorHandle());

			CL_Instance.GetCommandList()->SetPipelineState(PSO_Instance.GetPipeline());

			{
				Object::ConstBuffer QuadData
				{
					DirectX::XMMatrixTranspose(QuadObjectInstance.World()),
					QuadObjectInstance.Color()
				};
				UINT8* pquadData{};
				QuadPolygonConstantBufferInstance.ConstantBuffer()->Map(0, nullptr, reinterpret_cast<void**>(&pquadData));
				memcpy_s(pquadData, sizeof(QuadData), &QuadData, sizeof(QuadData));
				QuadPolygonConstantBufferInstance.ConstantBuffer()->Unmap(0, nullptr);
				CL_Instance.GetCommandList()->SetGraphicsRootDescriptorTable(1, QuadPolygonConstantBufferInstance.getGpuDescriptorHandle());

				QP_Instance.Draw(CL_Instance);
			}

			{
				Object::ConstBuffer TriangleData
				{
					DirectX::XMMatrixTranspose(TriangleObjectInstance.World()),
					QuadObjectInstance.Color()
				};
				UINT8* ptriangleData{};
				TrianglePolygonConstantBufferInstance.ConstantBuffer()->Map(0, nullptr, reinterpret_cast<void**>(&ptriangleData));
				memcpy_s(ptriangleData,sizeof(TriangleData),&TriangleData, sizeof(TriangleData));
				TrianglePolygonConstantBufferInstance.ConstantBuffer()->Unmap(0, nullptr);
				CL_Instance.GetCommandList()->SetGraphicsRootDescriptorTable(1, TrianglePolygonConstantBufferInstance.getGpuDescriptorHandle());
				TP_Instance.Draw(CL_Instance);
			}
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

	Root_Signature RS_Instance{};
	Shader SH_Instance{};
	Pipline_state_object PSO_Instance{};
	Descriptor_Heap ConstantBufferDH_Instance{};

	Quad_polygon QP_Instance{};
	Object QuadObjectInstance{};
	Constant_buffer QuadPolygonConstantBufferInstance{};

	Triangle_prigon TP_Instance{};
	Object TriangleObjectInstance{};
	Constant_buffer TrianglePolygonConstantBufferInstance{};

	Camera Camera_Instance{};
	Constant_buffer CameraConstantBufferInstance{};

	Descriptor_Heap depthBufferDescriptorHeapInstance{};
	Depth_buffer DB_Instance{};
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