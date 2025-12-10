#include<Windows.h>
#include<string>
#pragma once
class Window
{
public:
	HWND hwnd;
	int width;
	int height;
public:
	Window() = default;
	~Window() = default;

	HRESULT createWindow(HINSTANCE hInstance,int Width,int Height,std::string_view name);

	bool MassageLoop();

	HWND Handle();

	std::pair<int, int> size();
};

