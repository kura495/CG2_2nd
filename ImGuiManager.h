#pragma once
#include"WinApp.h"
#include"DirectXCommon.h"
class ImGuiManager
{
public:
	void Initialize(WinApp* winapp, DirectXCommon* directXcommon);
	void BeginFrame();
	void EndFrame();
private:

};