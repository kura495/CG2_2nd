#pragma once
#include"Bace\WinApp.h"
#include"Bace\DirectXCommon.h"
class ImGuiManager
{
public:
	void Initialize(WinApp* winapp,DirectXCommon*directXcommon);
	void BeginFrame();
	void EndFrame();
private:

};