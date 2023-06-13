#include"GameScene.h"

void GameScene::Initialize(DirectXCommon* directX, MyEngine* myEngine,WinApp*winApp,int32_t kClientWidth,int32_t kClientHeight)
{
	directX_ = directX;
	myEngine_ = myEngine;
	kClientWidth_ = kClientWidth;
	kClientHeight_ = kClientHeight;
	camera_ = new Camera();
	camera_->Initialize(kClientWidth_, kClientHeight_);
	ImGuiManager_ = new ImGuiManager();
	ImGuiManager_->Initialize(winApp,directX_);

	//Textureを読んで転送する
	DirectX::ScratchImage mipImages = myEngine_->LoadTexture("resources/uvChecker.png");
	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
	ID3D12Resource* textureResource = myEngine->CreateTextureResource(directX_->GetDevice(),metadata);
	myEngine_->UploadTextureData(textureResource,mipImages);
	//metadataを基にSRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);
	//SRVを作成するDescriptorHeapの場所を決める
	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU = directX_->GetsrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU = directX_->GetsrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart();
	//先頭はImGuiが使っているので次のを使う
	textureSrvHandleCPU.ptr += directX_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	textureSrvHandleGPU.ptr += directX_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	//SRVの作成
	directX_->GetDevice()->CreateShaderResourceView(textureResource,&srvDesc,textureSrvHandleCPU);
}

void GameScene::UpDate()
{
	camera_->Update();
	transform.rotate.y += 0.03f;
}

void GameScene::Draw()
{
	
	ImGuiManager_->BeginFrame();
	directX_->PreView();
	//ここから
	ImGui::ShowDemoWindow();
	myEngine_->Draw(Left,Top,Right,Color,transform,camera_->transformationMatrixData);

	//ここまで
	ImGuiManager_->EndFrame();
	directX_->PostView();
}

void GameScene::Release()
{
	ImGui_ImplDX12_Shutdown();
	myEngine_->Release();
	directX_->Release();
}
