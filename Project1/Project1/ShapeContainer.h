#pragma once
#include<d3d12.h>
#include<unordered_map>
#include<memory>
#include<cassert>
#include"Shape.h"
class ShapeContainer
{
public:
	static ShapeContainer& instance()
	{
		static ShapeContainer instance;
		return instance;
	}
public:
	template <class T>
	UINT64 Create()
	{
		auto id = id::get<T>();
		if (shapes_.find(id) != shapes_.end())return id;
		

		auto p = std::make_unique<T>();
		if (!p->Create())
		{
			assert(false&&"Œ`ó‚Ì¶¬‚É¸”s‚µ‚Ü‚µ‚½B");
			return 0;
		}
		shapes_.emplace(id,std::move(p));
		return id;
	}

	void Draw(Command_List& commandList, UINT64 id);
private:
	ShapeContainer() = default;
	~ShapeContainer() = default;

	ShapeContainer(const ShapeContainer&) = delete;
	ShapeContainer& operator=(const ShapeContainer&) = delete;
	ShapeContainer(ShapeContainer&&) = delete;
	ShapeContainer& operator=(ShapeContainer&&) = delete;
protected:
	std::unordered_map<UINT64, std::unique_ptr<Shape>> shapes_;
};

