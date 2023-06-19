#include "MyEngine.h"

void MyEngine::Initialize(DirectXCommon* directX)
{
	directX_ = directX;
	vertexResource = CreateBufferResource(sizeof(VertexData)*3);
	materialResource = CreateBufferResource(sizeof(Vector4) * 3);
	wvpResource = CreateBufferResource(sizeof(Matrix4x4));
	MakeVertexBufferView();
}

void MyEngine::Draw(const Vector4& Leftbottom, const Vector4& top, const Vector4& Rightbottom, const Vector4& color,const Matrix4x4& ViewMatrix)
{
	//左下
	vertexData[0].position = Leftbottom;
	vertexData[0].texcoord = {0.0f,1.0f};
	//上
	vertexData[1].position = top;
	vertexData[1].texcoord = {0.5f,0.0f};
	//右下
	vertexData[2].position = Rightbottom;
	vertexData[2].texcoord = {1.0f,1.0f};
	//色を書き込むアドレスを取得
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	//色情報を書き込む
	*materialData = color;
	//行列を作る
	Matrix4x4 worldMatrix = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
	//WVPを書き込むアドレスを取得
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));
	//単位行列を書き込む
	*wvpData =Multiply(worldMatrix,ViewMatrix);
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//色用のCBufferの場所を特定
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	//WVP用のCBufferの場所を特定
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());
	//SRVのDescriptorTableの先頭を設定　2はrootParameter[2]の2
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU);
	directX_->GetcommandList()->DrawInstanced(3, 1, 0, 0);
}

void MyEngine::ImGui()
{
#pragma region ImGui
	ImGui::ShowDemoWindow();
	
	ImGui::Begin("TriAngle");
	float ImGuiScale[Vector3D] = { transform.scale.x,transform.scale.y ,transform.scale.z };
	ImGui::SliderFloat3("Scale", ImGuiScale, 1, 30, "%.3f");
	transform.scale = { ImGuiScale[x],ImGuiScale[y],ImGuiScale[z] };
	float ImGuiRotate[Vector3D] = { transform.rotate.x,transform.rotate.y ,transform.rotate.z };
	ImGui::SliderFloat3("Rotate", ImGuiRotate, 0, 7, "%.3f");
	transform.rotate = { ImGuiRotate[x],ImGuiRotate[y],ImGuiRotate[z] };
	float ImGuiTranslate[Vector3D] = { transform.translate.x,transform.translate.y ,transform.translate.z };
	ImGui::SliderFloat3("Translate", ImGuiTranslate, -2, 2, "%.3f");
	transform.translate = { ImGuiTranslate[x],ImGuiTranslate[y],ImGuiTranslate[z] };
	ImGui::End();
#pragma endregion
}

void MyEngine::Release()
{
	vertexResource->Release();
	materialResource->Release();
	wvpResource->Release();
	textureResource->Release();
	intermediateResource->Release();
}

void MyEngine::LoadTexture(const std::string& filePath)
{
	//Textureを読んで転送する
	DirectX::ScratchImage mipImages = ImageFileOpen(filePath);
	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
	textureResource = CreateTextureResource(directX_->GetDevice(), metadata);
	intermediateResource=UploadTextureData(textureResource, mipImages);
	//metadataを基にSRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);
	//SRVを作成するDescriptorHeapの場所を決める
	textureSrvHandleCPU = directX_->GetsrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
	textureSrvHandleGPU = directX_->GetsrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart();
	//先頭はImGuiが使っているので次のを使う
	textureSrvHandleCPU.ptr += directX_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	textureSrvHandleGPU.ptr += directX_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	//SRVの作成
	directX_->GetDevice()->CreateShaderResourceView(textureResource, &srvDesc, textureSrvHandleCPU);
}

DirectX::ScratchImage MyEngine::ImageFileOpen(const std::string& filePath)
{
	//テクスチャファイルを読み込みプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW=ConvertString(filePath);
	hr = DirectX::LoadFromWICFile(filePathW.c_str(),DirectX::WIC_FLAGS_FORCE_SRGB,nullptr,image);
	assert(SUCCEEDED(hr));
	//ミップマップの作成
	DirectX::ScratchImage mipImage{};
	hr = DirectX::GenerateMipMaps(image.GetImages(),image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImage);

	return mipImage;
}

ID3D12Resource* MyEngine::CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata)
{
	//metadataを基にResourceの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = UINT(metadata.width);
	resourceDesc.Height = UINT(metadata.height);
	resourceDesc.MipLevels = UINT16(metadata.mipLevels);
	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);
	resourceDesc.Format = metadata.format;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);
	//利用するheapの設定
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;//細かい設定を行う
	
	//Resourceの生成
	ID3D12Resource* resource = nullptr;
	hr = device->CreateCommittedResource(
		&heapProperties,//Heapの設定
		D3D12_HEAP_FLAG_NONE,//Heapの特殊な設定
		&resourceDesc,//Resourceの設定
		D3D12_RESOURCE_STATE_COPY_DEST,//初回のResourceState　Textureは基本読むだけ
		nullptr,//Clear最適値　使わないためnullptr
		IID_PPV_ARGS(&resource)//作成するResourceポインタへのポインタ
	);
	return resource;
}
[[nodiscard]]
ID3D12Resource* MyEngine::UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages)
{
	std::vector<D3D12_SUBRESOURCE_DATA>subresources;
	DirectX::PrepareUpload(directX_->GetDevice(), mipImages.GetImages(), mipImages.GetImageCount(), mipImages.GetMetadata(), subresources);
	uint64_t intermediateSize = GetRequiredIntermediateSize(texture,0,UINT(subresources.size()));
	ID3D12Resource* intermediateResource = CreateBufferResource(intermediateSize);
	UpdateSubresources(directX_->GetcommandList(), texture, intermediateResource, 0, 0, UINT(subresources.size()), subresources.data());
	//Tetureへの転送後は利用できるようにD3D12_RESOURCE_STATE_COPY_DESTからD3D12_RESOURCE_STATE_GENERIC_READへResourceStateを変更する
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = texture;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
	directX_->GetcommandList()->ResourceBarrier(1,&barrier);
	return intermediateResource;
}

void MyEngine::MakeVertexBufferView()
{
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(VertexData) * 3;
	vertexBufferView.StrideInBytes = sizeof(VertexData);
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
}

ID3D12Resource* MyEngine::CreateBufferResource(size_t sizeInBytes)
{
	ID3D12Resource* Resource = nullptr;
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
	D3D12_RESOURCE_DESC vertexResourceDesc{};
	vertexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertexResourceDesc.Width = sizeInBytes;
	vertexResourceDesc.Height = 1;
	vertexResourceDesc.DepthOrArraySize = 1;
	vertexResourceDesc.MipLevels = 1;
	vertexResourceDesc.SampleDesc.Count = 1;
	vertexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//頂点リソースを作る
	hr = directX_->GetDevice()->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &vertexResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&Resource));
	assert(SUCCEEDED(hr));
	return Resource;
}
