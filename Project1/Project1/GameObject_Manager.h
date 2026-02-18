#pragma once
#include<functional>
#include<d3d12.h>
class GameObject_Manager
{
private:
	UINT64 counter_;
	void RegisterCreation();
public:
	void update();
public:
	template<typename T,typename... Args>
	UINT64 createObject(Args&&... args)
	{
		auto handle = ++counter_;

		auto func = [... a = std::forward<Args>(args)]() mutable
			{
				auto p = std::make_unique<T>(std::move(a)...);
				p->SetTypeID();
			}

	}
};

