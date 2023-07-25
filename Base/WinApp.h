#pragma once
#include<Windows.h>
#include<cstdint>
#include"../Utility/Log.h"
#include"../externals/imgui/imgui.h"
#include"../externals/imgui/imgui_impl_dx12.h"
#include"../externals/imgui/imgui_impl_win32.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
class WinApp
{
public:

	static LRESULT  WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	void Initialize(int32_t kClientWidth, int32_t kClientHeight);
	
	HWND GetHWND() const { return hwnd_; };

private:
	HWND hwnd_=nullptr;


};


