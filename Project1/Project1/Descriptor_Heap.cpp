#include "Descriptor_Heap.h"
#include"Device.h"
#include<cassert>
#include<wrl/client.h>

class Descriptor_Heap
{
public:
	Descriptor_Heap() = default;
	~Descriptor_Heap() = default;
public:
	bool Create(D3D12_DESCRIPTOR_HEAP_TYPE type,UINT numDescriptors,bool shaderVisible = false)
	{
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
		heapDesc.Type = type;
		heapDesc.NumDescriptors = numDescriptors;
		heapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		type_ = type;

		HRESULT hr = Device::instance().GetDevice()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&heap_));
		if (FAILED(hr))
		{
			assert(false && "ディスクリプターヒープの生成に失敗しました");
			return false;
		}
		maxDescriptorCount_ = numDescriptors;
		for (UINT i = 0;i < maxDescriptorCount_; ++i)
		{
			FreeIndices_.push_back(i);
		}
		return true;
	}
	ID3D12DescriptorHeap* Get()
	{
		if (!heap_)
		{
			assert(false &&  "ディスクリプターヒープが未作成です");
		}
		return heap_.Get();
	}
	D3D12_DESCRIPTOR_HEAP_TYPE GetType() 
	{
		if (!heap_)
		{
			assert(false && "ディスクリプターヒープが未作成です");
		}
		return type_;
	}
	std::optional<UINT> AllocateDescriptor()
	{
		if (FreeIndices_.empty())
		{
			assert(false && "ディスクリプタの空きがありません");
			return std::nullopt;
		}
		auto index = FreeIndices_.back();
		FreeIndices_.pop_back();
		return index;
	}
private:
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap_{};
	D3D12_DESCRIPTOR_HEAP_TYPE type_{};
	UINT maxDescriptorCount_{};
	std::vector<UINT> FreeIndices_{};
};

DescriptorHeapContainer::DescriptorHeapContainer() = default;
DescriptorHeapContainer::~DescriptorHeapContainer()
{
	map_.clear();
}

bool DescriptorHeapContainer::Create(Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors,bool shaderVisible)
{
	if (map_.find(type) != map_.end())return false;

	auto p = std::make_unique<Descriptor_Heap>();

	if (p->Create(type, numDescriptors, shaderVisible))map_.emplace(type, std::move(p));

	return true;
}

ID3D12DescriptorHeap* DescriptorHeapContainer::GetHeap(D3D12_DESCRIPTOR_HEAP_TYPE type)
{
	auto it = map_.find(type);
	if (it == map_.end())
	{
		assert(false && "ディスクリプターヒープがありません");
		return nullptr;
	}

	return it->second->Get();
}

std::optional<UINT> DescriptorHeapContainer::AllocateDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type)
{
	auto it = map_.find(type);
	if (it == map_.end())
	{
		assert(false && "ディスクリプタヒープがありません");
		return std::nullopt;
	}

	return it->second->AllocateDescriptor();
}