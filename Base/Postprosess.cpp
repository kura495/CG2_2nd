#include"Postprosess.h"

void Postprosess::Initialize(int width, int height, DirectXCommon* directX)
{
	//
	directX_ = directX;
	//
#pragma region
		//RTDescriptorHeapを作る
		renderTargetDescriptorHeap = directX_->CreateDescriptorHeap(directX_->GetDevice(),D3D12_DESCRIPTOR_HEAP_TYPE_RTV,1,false);
		//DSDescriptorHeapを作る
		depthStencilDescriptorHeap = directX_->CreateDescriptorHeap(directX_->GetDevice(), D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 1, false);
#pragma endregion Heap作成

#pragma region
		//DepthStencilViewの作成
		//DepthStencilTextureResourceを作る
		// ヒーププロパティの設定
		D3D12_HEAP_PROPERTIES prop;
		prop.Type = D3D12_HEAP_TYPE_DEFAULT;
		prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		prop.CreationNodeMask = 1;
		prop.VisibleNodeMask = 1;
		// リソースの設定
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
		hr = directX_->GetDevice()->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&clearValue,
			IID_PPV_ARGS(depthStencil.GetAddressOf())
		);
		assert(SUCCEEDED(hr));
		//
		//DSVを設定
		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
		//DSVを作成
		directX_->GetDevice()->CreateDepthStencilView(depthStencil.Get(), &dsvDesc, depthStencilDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
#pragma endregion DSView

#pragma region
		auto rtdhHandle = renderTargetDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	//ReaderTargetViewの作成
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

	directX_->GetDevice()->CreateRenderTargetView(texture.Get(), &rtvDesc, rtdhHandle);
#pragma endregion RTView

	//ShederResourceViewの作成
	{
		auto srvHandleCPU = directX_->GetsrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
		auto srvHandleGPU = directX_->GetsrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart();
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Format = rtvDesc.Format;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

		directX_->GetDevice()->CreateShaderResourceView(
			texture.Get(),
			&srvDesc,
			srvHandleCPU);
	}
	//RTVのハンドルを取得
	rtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		renderTargetDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), 0,
		directX_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
	//DSVのハンドルを取得
	dsvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		depthStencilDescriptorHeap->GetCPUDescriptorHandleForHeapStart()
	);


	scissorRect.left = 0;
	scissorRect.right = width;
	scissorRect.top = 0;
	scissorRect.bottom = height;

}

void Postprosess::SetRenderTarget(Vector4& clearColor)
{

}
