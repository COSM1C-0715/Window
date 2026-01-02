#include "Input.h"

bool Input::getKey(uint16_t sKey)
{
	return (keyState[sKey] & 0x80) != 0;
}

void Input::updateKeyState(void* pState)
{
	memcpy_s(keyState, sizeof(keyState), pState, sizeof(keyState));
}
