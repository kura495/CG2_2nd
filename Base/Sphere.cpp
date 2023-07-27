﻿#include"Sphere.h"

void Sphere::Initialize()
{
	directX_ = DirectXCommon::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	light_ = Light::GetInstance();

	vertexResourceSphere = CreateBufferResource(sizeof(VertexData) * 4 * kSubdivision * kSubdivision);
	materialResourceSphere = CreateBufferResource(sizeof(Material));
	transformationMatrixResourceSphere = CreateBufferResource(sizeof(TransformationMatrix));
	MakeVertexBufferViewSphere();
	indexResourceSphere = CreateBufferResource(sizeof(uint32_t) * 6 * kSubdivision * kSubdivision);
	MakeIndexBufferViewSphere();

	vertexResourceSphere.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataSphere));
	indexResourceSphere.Get()->Map(0, nullptr, reinterpret_cast<void**>(&indexDataSphere));
	//経度分割の1つ分の角度　φ 横
	const float kLonEvery = float(std::numbers::pi) * 2.0f / float(kSubdivision);
	//緯度分割の1つ分の角度　θ 縦
	const float kLatEvery = float(std::numbers::pi) / float(kSubdivision);
	for (int latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -float(std::numbers::pi) / 2.0f + kLatEvery * latIndex;
		float uvLength = 1.0f / kSubdivision;
		for (int lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			uint32_t Vertexstart = (latIndex * kSubdivision + lonIndex) * 4;
			uint32_t Indexstart = (latIndex * kSubdivision + lonIndex) * 6;
			float lon = lonIndex * kLonEvery;
			float u = float(lonIndex) / float(kSubdivision);
			float v = 1.0f - float(latIndex) / float(kSubdivision);
#pragma region VertexData
			//点A(左下)
			vertexDataSphere[Vertexstart].position.x = cos(lat) * cos(lon);
			vertexDataSphere[Vertexstart].position.y = sin(lat);
			vertexDataSphere[Vertexstart].position.z = cos(lat) * sin(lon);
			vertexDataSphere[Vertexstart].position.w = 1.0f;
			vertexDataSphere[Vertexstart].texcoord = { u ,v };
			vertexDataSphere[Vertexstart].normal.x = vertexDataSphere[Vertexstart].position.x;
			vertexDataSphere[Vertexstart].normal.y = vertexDataSphere[Vertexstart].position.y;
			vertexDataSphere[Vertexstart].normal.z = vertexDataSphere[Vertexstart].position.z;
			//点B(左上)
			vertexDataSphere[Vertexstart + 1].position.x = cos(lat + kLatEvery) * cos(lon);
			vertexDataSphere[Vertexstart + 1].position.y = sin(lat + kLatEvery);
			vertexDataSphere[Vertexstart + 1].position.z = cos(lat + kLatEvery) * sin(lon);
			vertexDataSphere[Vertexstart + 1].position.w = 1.0f;
			vertexDataSphere[Vertexstart + 1].texcoord = { u,v - uvLength };
			vertexDataSphere[Vertexstart + 1].normal.x = vertexDataSphere[Vertexstart + 1].position.x;
			vertexDataSphere[Vertexstart + 1].normal.y = vertexDataSphere[Vertexstart + 1].position.y;
			vertexDataSphere[Vertexstart + 1].normal.z = vertexDataSphere[Vertexstart + 1].position.z;
			//点C(右下)
			vertexDataSphere[Vertexstart + 2].position.x = cos(lat) * cos(lon + kLonEvery);
			vertexDataSphere[Vertexstart + 2].position.y = sin(lat);
			vertexDataSphere[Vertexstart + 2].position.z = cos(lat) * sin(lon + kLonEvery);
			vertexDataSphere[Vertexstart + 2].position.w = 1.0f;
			vertexDataSphere[Vertexstart + 2].texcoord = { u + uvLength,v };
			vertexDataSphere[Vertexstart + 2].normal.x = vertexDataSphere[Vertexstart + 2].position.x;
			vertexDataSphere[Vertexstart + 2].normal.y = vertexDataSphere[Vertexstart + 2].position.y;
			vertexDataSphere[Vertexstart + 2].normal.z = vertexDataSphere[Vertexstart + 2].position.z;
			//点D(右上)
			vertexDataSphere[Vertexstart + 3].position.x = cos(lat + kLatEvery) * cos(lon + kLonEvery);
			vertexDataSphere[Vertexstart + 3].position.y = sin(lat + kLatEvery);
			vertexDataSphere[Vertexstart + 3].position.z = cos(lat + kLatEvery) * sin(lon + kLonEvery);
			vertexDataSphere[Vertexstart + 3].position.w = 1.0f;
			vertexDataSphere[Vertexstart + 3].texcoord = { u + uvLength,v - uvLength };
			vertexDataSphere[Vertexstart + 3].normal.x = vertexDataSphere[Vertexstart + 3].position.x;
			vertexDataSphere[Vertexstart + 3].normal.y = vertexDataSphere[Vertexstart + 3].position.y;
			vertexDataSphere[Vertexstart + 3].normal.z = vertexDataSphere[Vertexstart + 3].position.z;
#pragma endregion 頂点データ
			//三角形1枚目
			indexDataSphere[Indexstart] = Vertexstart;
			indexDataSphere[Indexstart + 1] = Vertexstart + 1;
			indexDataSphere[Indexstart + 2] = Vertexstart + 2;
			//三角形2枚目
			indexDataSphere[Indexstart + 3] = Vertexstart + 1;
			indexDataSphere[Indexstart + 4] = Vertexstart + 3;
			indexDataSphere[Indexstart + 5] = Vertexstart + 2;
		}
	}
}

void Sphere::DrawSphere(const Vector4& color, const Matrix4x4& ViewMatrix, const uint32_t& TextureHandle)
{
	
	materialResourceSphere.Get()->Map(0, nullptr, reinterpret_cast<void**>(&materialDataSphere));

	//ライティングをする
	materialDataSphere->color = color;
	materialDataSphere->enableLighting = true;
	materialDataSphere->uvTransform = MakeIdentity4x4();
	//
	transformationMatrixResourceSphere.Get()->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixDataSphere));
	Matrix4x4 worldMatrixSphere = MakeAffineMatrix(transformSphere.scale, transformSphere.rotate, transformSphere.translate);
	transformationMatrixDataSphere->WVP = Multiply(worldMatrixSphere, ViewMatrix);
	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	transformationMatrixDataSphere->World = MakeIdentity4x4();

	//頂点
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSphere);
	directX_->GetcommandList()->IASetIndexBuffer(&indexBufferViewSphere);
	//色用のCBufferの場所を特定
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResourceSphere.Get()->GetGPUVirtualAddress());
	//WVP
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceSphere.Get()->GetGPUVirtualAddress());
	//テクスチャ
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureManager_->GetGPUHandle(TextureHandle));
	//Light
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(3, light_->GetDirectionalLight()->GetGPUVirtualAddress());

	directX_->GetcommandList()->DrawIndexedInstanced(kSubdivision * kSubdivision * 6, 1, 0, 0, 0);
}
void Sphere::ImGui(const char* Title)
{
	ImGui::Begin(Title);
	float ImGuiScaleSphere[Vector3D] = { transformSphere.scale.x,transformSphere.scale.y ,transformSphere.scale.z };
	ImGui::SliderFloat3("ScaleSphere", ImGuiScaleSphere, 1, 30, "%.3f");
	transformSphere.scale = { ImGuiScaleSphere[x],ImGuiScaleSphere[y],ImGuiScaleSphere[z] };
	float ImGuiRotateSphere[Vector3D] = { transformSphere.rotate.x,transformSphere.rotate.y ,transformSphere.rotate.z };
	ImGui::SliderFloat3("RotateSphere", ImGuiRotateSphere, -7, 7, "%.3f");
	transformSphere.rotate = { ImGuiRotateSphere[x],ImGuiRotateSphere[y],ImGuiRotateSphere[z] };
	float ImGuiTranslateSphere[Vector3D] = { transformSphere.translate.x,transformSphere.translate.y ,transformSphere.translate.z };
	ImGui::SliderFloat3("TranslateSphere", ImGuiTranslateSphere, -10, 10, "%.3f");
	transformSphere.translate = { ImGuiTranslateSphere[x],ImGuiTranslateSphere[y],ImGuiTranslateSphere[z] };
	ImGui::End();
}
void Sphere::MakeVertexBufferViewSphere()
{
	//リソースの先頭のアドレス
	vertexBufferViewSphere.BufferLocation = vertexResourceSphere.Get()->GetGPUVirtualAddress();
	//使用する頂点サイズ
	vertexBufferViewSphere.SizeInBytes = sizeof(VertexData) * 4 * kSubdivision * kSubdivision;
	//1頂点あたりのアドレス
	vertexBufferViewSphere.StrideInBytes = sizeof(VertexData);
}
void Sphere::MakeIndexBufferViewSphere()
{
	//リソース先頭アドレス
	indexBufferViewSphere.BufferLocation = indexResourceSphere.Get()->GetGPUVirtualAddress();
	//使用するインデックスサイズ
	indexBufferViewSphere.SizeInBytes = sizeof(uint32_t) * 6 * kSubdivision * kSubdivision;
	//インデックスはuint32_t
	indexBufferViewSphere.Format = DXGI_FORMAT_R32_UINT;
}
Microsoft::WRL::ComPtr<ID3D12Resource> Sphere::CreateBufferResource(size_t sizeInBytes)
{
	Microsoft::WRL::ComPtr<ID3D12Resource> Resource = nullptr;
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
	D3D12_RESOURCE_DESC ResourceDesc{};
	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	ResourceDesc.Width = sizeInBytes;
	ResourceDesc.Height = 1;
	ResourceDesc.DepthOrArraySize = 1;
	ResourceDesc.MipLevels = 1;
	ResourceDesc.SampleDesc.Count = 1;
	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//頂点リソースを作る
	HRESULT hr = directX_->GetDevice()->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &ResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&Resource));
	assert(SUCCEEDED(hr));
	return Resource;
}