#pragma once
#include"../Base/WinApp.h"
#include"../Base/DirectXcommon.h"
class ImGuiManager
{
public:
	void Initialize(WinApp* winapp, DirectXCommon* directXcommon);
	void BeginFrame();
	void EndFrame();
private:

};