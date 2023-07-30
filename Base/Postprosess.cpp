#include"Postprosess.h"

void Postprosess::Initialize(int width, int height, DirectXCommon* directX)
{
	//
	directX_ = directX;
	//		
	//ディスクリプタ―ヒープ作成
	{
		//RenderTargetのディスクリプタヒープの作成
		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.NumDescriptors = 1;
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		hr = directX_->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(renderTargetDescriptorHeap.GetAddressOf()));
		assert(SUCCEEDED(hr));
		//DSV(SEPTH_STENCIL_View)のディスクリプタヒープの作成
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		hr = directX_->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(depthStencilDescriptorHeap.GetAddressOf()));
		assert(SUCCEEDED(hr));
	}
	//ヒーププロパティ
	D3D12_HEAP_PROPERTIES prop;
	prop.Type = D3D12_HEAP_TYPE_DEFAULT;
	prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	prop.CreationNodeMask = 1;
	prop.VisibleNodeMask = 1;
	// DepthStencil(リソース)の設定
	D3D12_RESOURCE_DESC desc;
	desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	desc.Alignment = 0;
	desc.Width = width;
	desc.Height = height;
	desc.DepthOrArraySize = 1;
	desc.MipLevels = 0;
	desc.Format = DXGI_FORMAT_D32_FLOAT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	// クリア値の設定
	D3D12_CLEAR_VALUE clearValue;
	clearValue.Format = DXGI_FORMAT_D32_FLOAT;
	clearValue.DepthStencil.Depth = 1.0f;
	clearValue.DepthStencil.Stencil = 0;
	// DepthStencil(リソース)を生成
	hr = directX_->GetDevice()->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&clearValue,
		IID_PPV_ARGS(depthStencil.GetAddressOf())
	);
	// DSVの設定
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	// DSVを生成
	directX_->GetDevice()->CreateDepthStencilView(depthStencil.Get(),&dsvDesc,depthStencilDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
	auto rtdhHandle = renderTargetDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	hr = directX_->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE, &desc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		nullptr,
		IID_PPV_ARGS(texture.GetAddressOf()));

	directX_->GetDevice()->CreateRenderTargetView(texture.Get(), &rtvDesc, rtvHandle);

	auto srvHandleInfo = directX_->GetswapChainResources();
	auto handle = srvHandleInfo.GPUHandle;

}
