#pragma once
#include<d3d12.h>
#include"DirectXCommon.h"
#include<cassert>
class Postprosess
{
public:
	void Initialize(int width,int height,DirectXCommon*directX);

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
};
