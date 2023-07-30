#pragma once
#include<d3d12.h>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")
#pragma comment(lib,"dxguid.lib")
#include"externals/DirectXTex/d3dx12.h"
#include"DirectXCommon.h"
#include<cassert>
class Postprosess
{
public:
	void Initialize(int width,int height,DirectXCommon*directX);
	void SetRenderTarget();
	void DisSetRenderTarget();
	void Attach(const int slot);
	void SetIsCleared(const bool arg_isClear);
private:
	DirectXCommon* directX_ = nullptr;
	D3D12_RECT	scissorRect;
	HRESULT hr;
	Microsoft::WRL::ComPtr<ID3D12Resource> depthStencil;
	Microsoft::WRL::ComPtr<ID3D12Resource> texture;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> depthStencilDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> renderTargetDescriptorHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle;
	bool isCleared = false;
	D3D12_GPU_DESCRIPTOR_HANDLE handle;
	D3D12_HEAP_PROPERTIES prop;
	
};
