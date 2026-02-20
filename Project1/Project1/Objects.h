#pragma once
#include"Command_List.h"
#include"Constant_buffer.h"
#include<cstddef>
class Objects
{
public:
	Objects() = default;

	virtual ~Objects() = default;

	virtual void Initialize();

	virtual void Update();

	virtual void SetDrawCommand(Command_List& commandList,UINT Slot);
public:
	virtual void CreateDrawBuffer() = 0;
	virtual void UpdateDrawBuffer() = 0;
public:
	UINT64 TypeId()
	{
		return TypeId_;
	};

	void SetTypeId(UINT64 id)
	{
		TypeId_ = id;
	};
protected:
	template<class T>
	void UpdateConstantBuffer(T& data)
	{
		std::byte* dst{};
		ConstantBuffer_.ConstantBuffer()->Map(0, nullptr, reinterpret_cast<void**>(&dst));
		memcpy_s(dst, sizeof(T), &data, sizeof(T));
		ConstantBuffer_.ConstantBuffer()->Unmap(0, nullptr);
	};
protected:
	Constant_buffer ConstantBuffer_{};
	UINT64 TypeId_{};
};

