#include"Sprite.h"
void Sprite::Initialize(const Vector4& LeftTop, const Vector4& LeftBottom, const Vector4& RightTop, const Vector4& RightBottom)
{
	directX_ = DirectXCommon::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	vertexResourceSprite = CreateBufferResource(sizeof(VertexData) * 4);
	materialResourceSprite = CreateBufferResource(sizeof(Material));
	transformationMatrixResourceSprite = CreateBufferResource(sizeof(TransformationMatrix));
	MakeVertexBufferViewSprite();
	indexResourceSprite = CreateBufferResource(sizeof(uint32_t) * 6);
	MakeIndexBufferViewSprite();

	vertexResourceSprite.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataSprite));

	//左下
	vertexDataSprite[0].position = LeftBottom;
	vertexDataSprite[0].texcoord = { 0.0f,1.0f };
	//左上
	vertexDataSprite[1].position = LeftTop;
	vertexDataSprite[1].texcoord = { 0.0f,0.0f };
	//右下
	vertexDataSprite[2].position = RightBottom;
	vertexDataSprite[2].texcoord = { 1.0f,1.0f };
	//右上
	vertexDataSprite[3].position = RightTop;
	vertexDataSprite[3].texcoord = { 1.0f,0.0f };

	//インデックスリソースにデータを書き込む
	indexResourceSprite.Get()->Map(0, nullptr, reinterpret_cast<void**>(&indexDataSprite));

	//三角形1枚目
	indexDataSprite[0] = 0;
	indexDataSprite[1] = 1;
	indexDataSprite[2] = 2;
	//三角形2枚目
	indexDataSprite[3] = 1;
	indexDataSprite[4] = 3;
	indexDataSprite[5] = 2;
}
void Sprite::DrawSprite(const Vector4& color, const uint32_t TextureIndex)
{

	//色の書き込み
	materialResourceSprite.Get()->Map(0, nullptr, reinterpret_cast<void**>(&materialDataSprite));
	materialDataSprite->color = color;
	//ライティングをしない
	materialDataSprite->enableLighting = false;
	materialDataSprite->uvTransform = MakeIdentity4x4();
	Matrix4x4 uvTransformMatrix = MakeScaleMatrix(uvTranformSprite.scale);
	uvTransformMatrix = Multiply(uvTransformMatrix, MakeRotateZMatrix(uvTranformSprite.rotate.z));
	uvTransformMatrix = Multiply(uvTransformMatrix, MakeTranslateMatrix(uvTranformSprite.translate));
	materialDataSprite->uvTransform = uvTransformMatrix;
	//WVPを書き込むためのアドレス取得
	transformationMatrixResourceSprite.Get()->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixDataSprite));
	Matrix4x4 worldMatrixSprite = MakeAffineMatrix(transformSprite.scale, transformSprite.rotate, transformSprite.translate);
	Matrix4x4 viewMatrixSprite = MakeIdentity4x4();
	Matrix4x4 ProjectionMatrixSprite = MakeOrthographicMatrix(0.0f, 0.0f, float(WinApp::kClientWidth), float(WinApp::kClientHeight), 0.0f, 100.0f);
	Matrix4x4 worldViewProjectionMatrixSprite = Multiply(worldMatrixSprite, Multiply(viewMatrixSprite, ProjectionMatrixSprite));
	//
	transformationMatrixDataSprite->WVP = worldViewProjectionMatrixSprite;
	transformationMatrixDataSprite->World = MakeIdentity4x4();

	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//頂点
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSprite);
	directX_->GetcommandList()->IASetIndexBuffer(&indexBufferViewSprite);
	//色用のCBufferの場所を特定
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResourceSprite.Get()->GetGPUVirtualAddress());
	//WVP用のCBufferの場所を特定
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceSprite.Get()->GetGPUVirtualAddress());
	//テクスチャ
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureManager_->GetGPUHandle(TextureIndex));

	directX_->GetcommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);
}
void Sprite::ImGui(const char* Title)
{
	ImGui::Begin(Title);
	float ImGuiScaleSprite[Vector3D] = { transformSprite.scale.x,transformSprite.scale.y ,transformSprite.scale.z };
	ImGui::SliderFloat3("ScaleSprite", ImGuiScaleSprite, 1, 30, "%.3f");
	transformSprite.scale = { ImGuiScaleSprite[x],ImGuiScaleSprite[y],ImGuiScaleSprite[z] };
	float ImGuiRotateSprite[Vector3D] = { transformSprite.rotate.x,transformSprite.rotate.y ,transformSprite.rotate.z };
	ImGui::SliderFloat3("RotateSprite", ImGuiRotateSprite, -7, 7, "%.3f");
	transformSprite.rotate = { ImGuiRotateSprite[x],ImGuiRotateSprite[y],ImGuiRotateSprite[z] };
	float ImGuiTranslateSprite[Vector3D] = { transformSprite.translate.x,transformSprite.translate.y ,transformSprite.translate.z };
	ImGui::SliderFloat3("TranslateSprite", ImGuiTranslateSprite, -640, 640, "%.3f");
	transformSprite.translate = { ImGuiTranslateSprite[x],ImGuiTranslateSprite[y],ImGuiTranslateSprite[z] };
	ImGui::DragFloat2("UVTranslate", &uvTranformSprite.translate.x, 0.01f, -10.0f, 10.0f);
	ImGui::DragFloat2("UVScale", &uvTranformSprite.scale.x, 0.01f, -10.0f, 10.0f);
	ImGui::SliderAngle("UVRotate", &uvTranformSprite.rotate.z);
	ImGui::End();
}
void Sprite::MakeVertexBufferViewSprite()
{
	//リソースの先頭のアドレス
	vertexBufferViewSprite.BufferLocation = vertexResourceSprite.Get()->GetGPUVirtualAddress();
	//使用する頂点サイズ
	vertexBufferViewSprite.SizeInBytes = sizeof(VertexData) * 4;
	//1頂点あたりのアドレス
	vertexBufferViewSprite.StrideInBytes = sizeof(VertexData);
}
void Sprite::MakeIndexBufferViewSprite()
{
	//リソース先頭アドレス
	indexBufferViewSprite.BufferLocation = indexResourceSprite.Get()->GetGPUVirtualAddress();
	//使用するインデックスサイズ
	indexBufferViewSprite.SizeInBytes = sizeof(uint32_t) * 6;
	//インデックスはuint32_t
	indexBufferViewSprite.Format = DXGI_FORMAT_R32_UINT;
}
Microsoft::WRL::ComPtr<ID3D12Resource> Sprite::CreateBufferResource(size_t sizeInBytes)
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