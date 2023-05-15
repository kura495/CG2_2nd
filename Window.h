#pragma once
#include<Windows.h>
#include<cstdint>
#include"Log.h"
class Window
{
public:
	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;

	Window();
	~Window();

	static LRESULT  WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	void Initialize();
	

private:



};


