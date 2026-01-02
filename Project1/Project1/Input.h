#pragma once
#include<Windows.h>
#include<cstdint>
class Input
{
private:
	byte keyState[256];
private:
	Input() = default;
	~Input() = default;
public:
	static Input& instance()
	{
		static Input instance;
		return instance;
	}

	bool getKey(uint16_t sKey);

	void updateKeyState(void* pState);
};

