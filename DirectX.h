#pragma once
#include"Log.h"
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
class DirectX
{
public:

	void Initialize();

private:
	IDXGIFactory7* dxgiFactory=nullptr;
	HRESULT hr;
	IDXGIAdapter4* useAdapter = nullptr;
	ID3D12Device* device = nullptr;

};


