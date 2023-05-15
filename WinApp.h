#pragma once
#include<Windows.h>
#include<cstdint>
#include"Log.h"
class WinApp
{
public:
	

	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void Initialize(int kWindowWidth, int kWindowHeight);
	

private:



};


