#pragma once
#include"Log.h"
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#include"WinApp.h"
#include"includeStruct\Vector3.h"
#include"includeStruct\Vector4.h"
#include"ResourceObject.h"
#include<dxcapi.h>
#pragma comment(lib,"dxcompiler.lib")
#include<dxgidebug.h>
#pragma comment(lib,"dxguid.lib")
#include"externals/DirectXTex/d3dx12.h"
#include<wrl.h>
class DirectXCommon
{
public:
	
	void Initialize(WinApp* Window,int32_t kClientWidth, int32_t kClientHeight);

	void PreView();

	void PostView();

	void Release();
	
	ID3D12GraphicsCommandList* GetcommandList()const { return commandList.Get(); }

	ID3D12Device* GetDevice()const { return device.Get(); }

	DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc()const { return swapChainDesc; }
	D3D12_RENDER_TARGET_VIEW_DESC GetrtvDesc()const { return rtvDesc; }
	ID3D12DescriptorHeap* GetsrvDescriptorHeap()const { return srvDescriptorHeap.Get(); }
	
private:
	WinApp* winApp_;
	int32_t kClientWidth_;
	int32_t kClientHeight_;
	HRESULT hr;
	//TransitionBarrier
	D3D12_RESOURCE_BARRIER barrier{};
	//DXGIファクトリー
	Microsoft::WRL::ComPtr<IDXGIFactory7>dxgiFactory = nullptr;
	//アダプターを作成
	Microsoft::WRL::ComPtr<IDXGIAdapter4>useAdapter = nullptr;
	//デバイス
	Microsoft::WRL::ComPtr<ID3D12Device>device = nullptr;
	//コマンドキューを生成
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue = nullptr;
	//コマンドアロケータを作成
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>commandAllocator = nullptr;
	//コマンドリストを作成
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>commandList = nullptr;
	//スワップチェーンを作成
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	Microsoft::WRL::ComPtr<IDXGISwapChain4>swapChain = nullptr;
	//RTVDescriptorHeap
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>rtvDescriptorHeap = nullptr;
	//SRVDescriptorHeap
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>srvDescriptorHeap = nullptr;
	//DSVDescriptorHeap
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>dsvDescriptorHeap = nullptr;
	//深度
	Microsoft::WRL::ComPtr<ID3D12Resource>depthStencilResource = nullptr;
	//RTVの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	//SwapChainからResourceを持ってくる
	Microsoft::WRL::ComPtr<ID3D12Resource>swapChainResources[2] = { nullptr };
	//RTVを2つつくるので2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	//Fenceを作る
	Microsoft::WRL::ComPtr<ID3D12Fence>fence = nullptr;
	uint64_t fenceValue = 0;
	//FenceのSignalを待つイベント
	HANDLE fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	//dxCompiler初期化
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;
	//コンパイルシェーダー
	IDxcBlobUtf8* shaderError = nullptr;
	IDxcBlob* shaderBlob = nullptr;
	//ルートシグネチャ―
	Microsoft::WRL::ComPtr<ID3D12RootSignature>rootSignature = nullptr;
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	//インプットレイアウト
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[3] = {};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	//ブレンドステート
	D3D12_BLEND_DESC blendDesc{};
	//ラスタライザステート
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	//シェーダーコンパイル
	IDxcBlob* vertexShaderBlob = nullptr;
	IDxcBlob* pixelShaderBlob = nullptr;
	//PSO
	Microsoft::WRL::ComPtr<ID3D12PipelineState>graphicsPipelineState = nullptr;
	//ビューポート
	D3D12_VIEWPORT viewport{};
	//シザー
	D3D12_RECT scissorRect{};
#ifdef _DEBUG
	Microsoft::WRL::ComPtr<ID3D12Debug1>debugController = nullptr;
#endif

//プライベート関数
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>
	 CreateDescriptorHeap(Microsoft::WRL::ComPtr<ID3D12Device> device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);
	Microsoft::WRL::ComPtr<ID3D12Resource>
	 CreateDepthStencilTextureResource(int32_t width, int32_t height);
	void MakeDXGIFactory();
	void MakeD3D12Device();
	void MakeCommandQueue();
	void MakeCommandAllocator();
	void MakeCommandList();
	void MakeSwapChain();
	void MakeDescriptorHeap();
	void MakeFence();
	void MakeDXC();
	IDxcBlob* CompileShader(const std::wstring& filePath,const wchar_t* profile,IDxcUtils*dxcUtils,IDxcCompiler3*dxcCompiler,IDxcIncludeHandler*includeHandler);
	//PSO
	void MakeRootSignature();
	void MakeInputLayOut();
	void MakeBlendState();
	void MakeRasterizarState();
	void MakeShaderCompile();
	void MakePipelineStateObject();

	void MakeViewport();
	void MakeScissor();
};


