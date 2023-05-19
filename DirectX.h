#pragma once
#include"Log.h"
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#include"WinApp.h"
#include"Vector4.h"
#include<dxcapi.h>
#pragma comment(lib,"dxcompiler.lib")

class DirectX
{
public:

	void Initialize(WinApp* Window,int32_t kClientWidth, int32_t kClientHeight);

	void PreView();

	void Release();

private:
	WinApp* winApp_;
	int32_t kClientWidth_;
	int32_t kClientHeight_;

	HRESULT hr;
	//DXGIファクトリー
	IDXGIFactory7* dxgiFactory = nullptr;
	//アダプターを作成
	IDXGIAdapter4* useAdapter = nullptr;
	//デバイス
	ID3D12Device* device = nullptr;
	//コマンドキューを生成
	ID3D12CommandQueue* commandQueue = nullptr;
	//コマンドアロケータを作成
	ID3D12CommandAllocator* commandAllocator = nullptr;
	//コマンドリストを作成
	ID3D12GraphicsCommandList* commandList = nullptr;
	//スワップチェーンを作成
	IDXGISwapChain4* swapChain = nullptr;
	//SwapChainからResourceを持ってくる
	ID3D12Resource* swapChainResources[2] = { nullptr };
	//ディスクリプタヒープの作成
	ID3D12DescriptorHeap* rtvDescriptorHeap = nullptr;
	//RTVを2つつくるので2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	//Fenceを作る
	ID3D12Fence* fence = nullptr;
	uint64_t fenceValue = 0;
	//FenceのSignalを待つイベント
	HANDLE fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	//dxCompiler初期化
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;
	//ルートシグネチャ―
	ID3D12RootSignature* rootSignature = nullptr;
	//インプットレイアウト
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	//ブレンドステート
	D3D12_BLEND_DESC blendDesc{};
	//ラスタライザステート
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	//シェーダーコンパイル
	IDxcBlob* vertexShaderBlob = nullptr;
	IDxcBlob* pixelShaderBlob = nullptr;
	//PSO
	ID3D12PipelineState* graphicsPipelineState = nullptr;
	//バーテックスリソース

#ifdef _DEBUG
	ID3D12Debug1* debugController = nullptr;
#endif

//プライベート関数
	void DXGIFactory();
	void D3D12Device();
	void CommandQueue();
	void CommandAllocator();
	void CommandList();
	void SwapChain();
	void DescriptorHeap();
	void Fence();
	void DXC();
	IDxcBlob* CompileShader(const std::wstring& filePath,const wchar_t* profile,IDxcUtils*dxcUtils,IDxcCompiler3*dxcCompiler,IDxcIncludeHandler*includeHandler);
	//PSO
	void RootSignature();
	void InputLayOut();
	void BlendState();
	void RasterizarState();
	void ShaderCompile();
	void PipelineStateObject();
	void VertexResource();
};


