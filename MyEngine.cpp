#include "MyEngine.h"

void MyEngine::Initialize(DirectXCommon* directX, int32_t kClientWidth, int32_t kClientHeight)
{
	kClientWidth_ = kClientWidth;
	kClientHeight_ = kClientHeight;
	directX_ = directX;
	#pragma region TriAngle
	vertexResource = CreateBufferResource(sizeof(VertexData)* kMaxVertex);
	materialResource = CreateBufferResource(sizeof(Material) * kMaxTriAngle);
	wvpResource = CreateBufferResource(sizeof(TransformationMatrix));
	MakeVertexBufferView();
	#pragma endregion 三角形
	#pragma region Sprite
	vertexResourceSprite = CreateBufferResource(sizeof(VertexData)* 4);
	materialResourceSprite = CreateBufferResource(sizeof(Material)* kMaxSprite);
	transformationMatrixResourceSprite = CreateBufferResource(sizeof(TransformationMatrix));
	MakeVertexBufferViewSprite();
	indexResourceSprite = CreateBufferResource(sizeof(uint32_t)* kMaxSpriteVertex);
	MakeIndexBufferViewSprite();
	#pragma endregion スプライト
	#pragma region Sphere
	vertexResourceSphere = CreateBufferResource(sizeof(VertexData) * 4 * kSubdivision * kSubdivision);
	materialResourceSphere = CreateBufferResource(sizeof(Material));
	transformationMatrixResourceSphere = CreateBufferResource(sizeof(TransformationMatrix));
	MakeVertexBufferViewSphere();
	indexResourceSphere = CreateBufferResource(sizeof(uint32_t) * 6 * kSubdivision * kSubdivision);
	MakeIndexBufferViewSphere();
	#pragma endregion 球
	#pragma region Box
	vertexResourceBox = CreateBufferResource(sizeof(VertexData) * 24);
	materialResourceBox = CreateBufferResource(sizeof(Material) * kMaxBox);
	transformationMatrixResourceBox = CreateBufferResource(sizeof(TransformationMatrix));
	MakeVertexBufferViewBox();
	indexResourceBox = CreateBufferResource(sizeof(uint32_t) * kMaxBoxVertex);
	MakeIndexBufferViewBox();
#pragma endregion ボックス
	#pragma region Light
	directionalLightResource = CreateBufferResource(sizeof(DirectionalLight));
	directionalLightResource->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData));
	directionalLightData->color={ 1.0f,1.0f,1.0f,1.0f };
	directionalLightData->direction = { 0.0f,-1.0f,0.0f };
	directionalLightData->intensity = 1.0f;
	#pragma endregion ライト

	descriptorSizeSRV = directX_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	descriptorSizeRTV = directX_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	descriptorSizeDSV = directX_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	for (int i = 0; i < kMaxTexture; i++) {
		IsusedTextureIndex[i] = false;
		textureResource[i]=nullptr;
		intermediateResource[i] = nullptr;
	}

}
void MyEngine::ImGui()
{
#pragma region TriAngleImGui
	ImGui::ShowDemoWindow();
	
	ImGui::Begin("TriAngle");
	float ImGuiScale[Vector3D] = { transform.scale.x,transform.scale.y ,transform.scale.z };
	ImGui::SliderFloat3("Scale", ImGuiScale, 1, 30, "%.3f");
	transform.scale = { ImGuiScale[x],ImGuiScale[y],ImGuiScale[z] };
	float ImGuiRotate[Vector3D] = { transform.rotate.x,transform.rotate.y ,transform.rotate.z };
	ImGui::SliderFloat3("Rotate", ImGuiRotate, -7, 7, "%.3f");
	transform.rotate = { ImGuiRotate[x],ImGuiRotate[y],ImGuiRotate[z] };
	float ImGuiTranslate[Vector3D] = { transform.translate.x,transform.translate.y ,transform.translate.z };
	ImGui::SliderFloat3("Translate", ImGuiTranslate, -2, 2, "%.3f");
	transform.translate = { ImGuiTranslate[x],ImGuiTranslate[y],ImGuiTranslate[z] };
	ImGui::End();
#pragma endregion
#pragma region SpriteImGui
	
	ImGui::Begin("Sprite");
	float ImGuiScaleSprite[Vector3D] = { transformSprite.scale.x,transformSprite.scale.y ,transformSprite.scale.z };
	ImGui::SliderFloat3("ScaleSprite", ImGuiScaleSprite, 1, 30, "%.3f");
	transformSprite.scale = { ImGuiScaleSprite[x],ImGuiScaleSprite[y],ImGuiScaleSprite[z] };
	float ImGuiRotateSprite[Vector3D] = { transformSprite.rotate.x,transformSprite.rotate.y ,transformSprite.rotate.z };
	ImGui::SliderFloat3("RotateSprite", ImGuiRotateSprite, -7, 7, "%.3f");
	transformSprite.rotate = { ImGuiRotateSprite[x],ImGuiRotateSprite[y],ImGuiRotateSprite[z] };
	float ImGuiTranslateSprite[Vector3D] = { transformSprite.translate.x,transformSprite.translate.y ,transformSprite.translate.z };
	ImGui::SliderFloat3("TranslateSprite", ImGuiTranslateSprite, -640, 640, "%.3f");
	transformSprite.translate = { ImGuiTranslateSprite[x],ImGuiTranslateSprite[y],ImGuiTranslateSprite[z] };
	ImGui::End();
#pragma endregion
#pragma region SphereImGui
	ImGui::Begin("Sphere");
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
#pragma endregion
#pragma region Light
	ImGui::Begin("Light");
	float ImGuidirectionalLightColor[Vector3D] = { directionalLightData->color.x,directionalLightData->color.y ,directionalLightData->color.z };
	ImGui::SliderFloat3("LightColor", ImGuidirectionalLightColor,0,1,"%.3f");
	directionalLightData->color.x = ImGuidirectionalLightColor[x];
	directionalLightData->color.y = ImGuidirectionalLightColor[y];
	directionalLightData->color.z = ImGuidirectionalLightColor[z];
	float ImGuidirectionalLightdirection[Vector3D] = { directionalLightData->direction.x,directionalLightData->direction.y,directionalLightData->direction.z };
	ImGui::SliderFloat3("Lightpotision", ImGuidirectionalLightdirection, -10, 10, "%.3f");
	directionalLightData->direction.x = ImGuidirectionalLightdirection[x];
	directionalLightData->direction.y = ImGuidirectionalLightdirection[y];
	directionalLightData->direction.z = ImGuidirectionalLightdirection[z];
	ImGui::End();
#pragma endregion ライト
}
void MyEngine::VertexReset()
{
	for (int i = 0; i < kMaxTriAngle; ++i) {
		if (IsusedTriAngleIndex[i] == true) {
			IsusedTriAngleIndex[i] = false;
		}
		if (IsusedSpriteIndex[i] == true) {
			IsusedSpriteIndex[i] = false;
		}
		if (IsusedBoxIndex[i] == true) {
			IsusedBoxIndex[i] = false;
		}
	}
}
void MyEngine::Release()
{
	vertexResource->Release();
	materialResource->Release();
	wvpResource->Release();

	for (int i = 0; i < kMaxTexture; ++i) {
		if (IsusedTextureIndex[i]==true) {
			textureResource[i]->Release();
			intermediateResource[i]->Release();
		}
	}
	
	vertexResourceSprite->Release();
	transformationMatrixResourceSprite->Release();
	materialResourceSprite->Release();
	indexResourceSprite->Release();

	vertexResourceSphere->Release();
	transformationMatrixResourceSphere->Release();
	materialResourceSphere->Release();
	indexResourceSphere->Release();

	vertexResourceBox->Release();
	materialResourceBox->Release();
	transformationMatrixResourceBox->Release();
	indexResourceBox->Release();

	directionalLightResource->Release();

}

#pragma region Draw
void MyEngine::Draw(const Vector4& Leftbottom, const Vector4& top, const Vector4& Rightbottom, const Vector4& color,const Matrix4x4& ViewMatrix, const int Index)
{
	int TriAngleIndex = kMaxVertex + 1;
	for (int i = 0; i < kMaxTriAngle; ++i) {
		if (IsusedTriAngleIndex[i] == false) {
			TriAngleIndex = i*3;
			IsusedTriAngleIndex[i] = true;
			break;
		}
	}
	if (TriAngleIndex < 0) {
		//0より少ない
		assert(false);
	}
	if (kMaxVertex < TriAngleIndex) {
		//MaxSpriteより多い
		assert(false);
	}
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	//左下
	vertexData[TriAngleIndex].position = Leftbottom;
	vertexData[TriAngleIndex].texcoord = {0.0f,1.0f};
	
	//上
	vertexData[TriAngleIndex+1].position = top;
	vertexData[TriAngleIndex+1].texcoord = {0.5f,0.0f};
	//右下
	vertexData[TriAngleIndex+2].position = Rightbottom;
	vertexData[TriAngleIndex+2].texcoord = {1.0f,1.0f};
	
	
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
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU[Index]);
	directX_->GetcommandList()->DrawInstanced(TriAngleIndex+3, 1, 0, 0);
}
void MyEngine::MakeVertexBufferView()
{
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(VertexData) * kMaxVertex;
	vertexBufferView.StrideInBytes = sizeof(VertexData);
}
#pragma endregion 三角形
#pragma region Sprite
void MyEngine::DrawSprite(const Vector4&LeftTop, const Vector4& LeftBottom, const Vector4& RightTop, const Vector4& RightBottom,const Vector4& color, const int Index)
{
#pragma region 
	int SpriteIndex = kMaxSpriteVertex + 1;
	for (int i = 0; i < kMaxSprite; ++i) {
		if (IsusedSpriteIndex[i] == false) {
			SpriteIndex = (i * 6);
			IsusedSpriteIndex[i] = true;
			break;
		}
	}
	if (SpriteIndex < 0) {
		//0より少ない
		assert(false);
	}
	if (kMaxSpriteVertex < SpriteIndex) {
		//MaxSpriteより多い
		assert(false);
	}
#pragma endregion 位置決め

	vertexResourceSprite->Map(0,nullptr,reinterpret_cast<void**>(&vertexDataSprite));
	
	//左下
	vertexDataSprite[0].position = LeftBottom;
	vertexDataSprite[0].texcoord={0.0f,1.0f};
	//左上
	vertexDataSprite[1].position = LeftTop;
	vertexDataSprite[1].texcoord={0.0f,0.0f};
	//右下
	vertexDataSprite[2].position = RightBottom;
	vertexDataSprite[2].texcoord={1.0f,1.0f};
	//右上
	vertexDataSprite[3].position = RightTop;
	vertexDataSprite[3].texcoord = { 1.0f,0.0f };
	//インデックスリソースにデータを書き込む
	indexResourceSprite->Map(0,nullptr,reinterpret_cast<void**>(&indexDataSprite));

	//三角形1枚目
	indexDataSprite[SpriteIndex] = 0;
	indexDataSprite[SpriteIndex+1] = 1;
	indexDataSprite[SpriteIndex+2] = 2;
	//三角形2枚目
	indexDataSprite[SpriteIndex+3] = 1;
	indexDataSprite[SpriteIndex+4] = 3;
	indexDataSprite[SpriteIndex+5] = 2;
	
	
	//色の書き込み
	materialResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&materialDataSprite));
	materialDataSprite->color = color;
	//ライティングをしない
	materialDataSprite->enableLighting = false;
	//WVPを書き込むためのアドレス取得
	transformationMatrixResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixDataSprite));
	Matrix4x4 worldMatrixSprite = MakeAffineMatrix(transformSprite.scale,transformSprite.rotate,transformSprite.translate);
	Matrix4x4 viewMatrixSprite = MakeIdentity4x4();
	Matrix4x4 ProjectionMatrixSprite = MakeOrthographicMatrix(0.0f, 0.0f, float(kClientWidth_), float(kClientHeight_), 0.0f, 100.0f);
	Matrix4x4 worldViewProjectionMatrixSprite = Multiply(worldMatrixSprite,Multiply(viewMatrixSprite,ProjectionMatrixSprite));
	//
	transformationMatrixDataSprite->WVP = worldViewProjectionMatrixSprite;
	transformationMatrixDataSprite->World = MakeIdentity4x4();

	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	//頂点
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSprite);
	directX_->GetcommandList()->IASetIndexBuffer(&indexBufferViewSprite);
	//色用のCBufferの場所を特定
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResourceSprite->GetGPUVirtualAddress());
	//WVP用のCBufferの場所を特定
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceSprite->GetGPUVirtualAddress());
	//テクスチャ
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU[Index]);
	//Light
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(3, directionalLightResource->GetGPUVirtualAddress());

	directX_->GetcommandList()->DrawIndexedInstanced(SpriteIndex+6,1,0,0,0);
}
void MyEngine::MakeVertexBufferViewSprite()
{
	//リソースの先頭のアドレス
	vertexBufferViewSprite.BufferLocation = vertexResourceSprite->GetGPUVirtualAddress();
	//使用する頂点サイズ
	vertexBufferViewSprite.SizeInBytes = sizeof(VertexData)* 4;
	//1頂点あたりのアドレス
	vertexBufferViewSprite.StrideInBytes = sizeof(VertexData);
}
void MyEngine::MakeIndexBufferViewSprite()
{
	//リソース先頭アドレス
	indexBufferViewSprite.BufferLocation = indexResourceSprite->GetGPUVirtualAddress();
	//使用するインデックスサイズ
	indexBufferViewSprite.SizeInBytes = sizeof(uint32_t)* kMaxSpriteVertex;
	//インデックスはuint32_t
	indexBufferViewSprite.Format = DXGI_FORMAT_R32_UINT;
}
#pragma endregion スプライト
#pragma region Sphere
void MyEngine::DrawSphere(const Sphere& sphere, const Matrix4x4& ViewMatrix, const Vector4& color, const int Index)
{
	vertexResourceSphere->Map(0,nullptr,reinterpret_cast<void**>(&vertexDataSphere));
	indexResourceSphere->Map(0, nullptr, reinterpret_cast<void**>(&indexDataSphere));
	//経度分割の1つ分の角度　φ 横
	const float kLonEvery = float(std::numbers::pi) * 2.0f / float(kSubdivision);
	//緯度分割の1つ分の角度　θ 縦
	const float kLatEvery = float(std::numbers::pi) / float(kSubdivision);
	for (int latIndex = 0; latIndex < kSubdivision;++latIndex) {
		float lat = -float(std::numbers::pi) / 2.0f + kLatEvery * latIndex;
		float uvLength = 1.0f / kSubdivision;
		for (int lonIndex = 0; lonIndex < kSubdivision;++lonIndex) {
			uint32_t Vertexstart = (latIndex * kSubdivision + lonIndex) * 4;
			uint32_t Indexstart = (latIndex * kSubdivision + lonIndex) * 6;
			float lon = lonIndex * kLonEvery;
			float u = float(lonIndex) / float(kSubdivision);
			float v = 1.0f-float(latIndex) / float(kSubdivision);
		#pragma region VertexData
			//点A(左下)
			vertexDataSphere[Vertexstart].position.x = cos(lat) * cos(lon) + sphere.center.x;
			vertexDataSphere[Vertexstart].position.y = sin(lat) + sphere.center.y;
			vertexDataSphere[Vertexstart].position.z = cos(lat) * sin(lon) + sphere.center.z;
			vertexDataSphere[Vertexstart].position.w = 1.0f;
			vertexDataSphere[Vertexstart].texcoord = { u ,v };
			vertexDataSphere[Vertexstart].normal.x = vertexDataSphere[Vertexstart].position.x;
			vertexDataSphere[Vertexstart].normal.y = vertexDataSphere[Vertexstart].position.y;
			vertexDataSphere[Vertexstart].normal.z = vertexDataSphere[Vertexstart].position.z;
			//点B(左上)
			vertexDataSphere[Vertexstart+1].position.x = cos(lat + kLatEvery) * cos(lon) + sphere.center.x;
			vertexDataSphere[Vertexstart+1].position.y = sin(lat + kLatEvery) + sphere.center.y;
			vertexDataSphere[Vertexstart+1].position.z = cos(lat + kLatEvery) * sin(lon) + sphere.center.z;
			vertexDataSphere[Vertexstart+1].position.w = 1.0f;
			vertexDataSphere[Vertexstart+1].texcoord = { u,v - uvLength };
			vertexDataSphere[Vertexstart+1].normal.x = vertexDataSphere[Vertexstart+1].position.x;
			vertexDataSphere[Vertexstart+1].normal.y = vertexDataSphere[Vertexstart+1].position.y;
			vertexDataSphere[Vertexstart+1].normal.z = vertexDataSphere[Vertexstart+1].position.z;
			//点C(右下)
			vertexDataSphere[Vertexstart+2].position.x = cos(lat) * cos(lon + kLonEvery) + sphere.center.x;	 
			vertexDataSphere[Vertexstart+2].position.y = sin(lat) + sphere.center.y;
			vertexDataSphere[Vertexstart+2].position.z = cos(lat) * sin(lon + kLonEvery) + sphere.center.z;
			vertexDataSphere[Vertexstart+2].position.w = 1.0f;
			vertexDataSphere[Vertexstart+2].texcoord = { u + uvLength,v};
			vertexDataSphere[Vertexstart+2].normal.x = vertexDataSphere[Vertexstart+2].position.x;
			vertexDataSphere[Vertexstart+2].normal.y = vertexDataSphere[Vertexstart+2].position.y;
			vertexDataSphere[Vertexstart+2].normal.z = vertexDataSphere[Vertexstart+2].position.z;
			//点D(右上)
			vertexDataSphere[Vertexstart+3].position.x = cos(lat + kLatEvery) * cos(lon + kLonEvery) + sphere.center.x;
			vertexDataSphere[Vertexstart+3].position.y = sin(lat + kLatEvery) + sphere.center.y;
			vertexDataSphere[Vertexstart+3].position.z = cos(lat + kLatEvery) * sin(lon + kLonEvery) + sphere.center.z;
			vertexDataSphere[Vertexstart+3].position.w = 1.0f;
			vertexDataSphere[Vertexstart+3].texcoord = { u + uvLength,v - uvLength };
			vertexDataSphere[Vertexstart+3].normal.x = vertexDataSphere[Vertexstart+3].position.x;
			vertexDataSphere[Vertexstart+3].normal.y = vertexDataSphere[Vertexstart+3].position.y;
			vertexDataSphere[Vertexstart+3].normal.z = vertexDataSphere[Vertexstart+3].position.z;
#pragma endregion 頂点データ
			//三角形1枚目
			indexDataSphere[Indexstart] = Vertexstart;
			indexDataSphere[Indexstart + 1] =Vertexstart+ 1;
			indexDataSphere[Indexstart + 2] =Vertexstart+ 2;
			//三角形2枚目
			indexDataSphere[Indexstart + 3] = Vertexstart+1;
			indexDataSphere[Indexstart + 4] = Vertexstart+3;
			indexDataSphere[Indexstart + 5] = Vertexstart+2;
		}
	}
	
	materialResourceSphere->Map(0, nullptr, reinterpret_cast<void**>(&materialDataSphere));
	
	//ライティングをする
	materialDataSphere->enableLighting = true;
	materialDataSphere->color = color;
	//
	transformationMatrixResourceSphere->Map(0,nullptr,reinterpret_cast<void**>(&transformationMatrixDataSphere));
	Matrix4x4 worldMatrixSphere = MakeAffineMatrix(transformSphere.scale, transformSphere.rotate, transformSphere.translate);
	transformationMatrixDataSphere->WVP = Multiply(worldMatrixSphere, ViewMatrix);
	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	transformationMatrixDataSphere->World = MakeIdentity4x4();
	
	//頂点
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSphere);
	directX_->GetcommandList()->IASetIndexBuffer(&indexBufferViewSphere);
	//色用のCBufferの場所を特定
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResourceSphere->GetGPUVirtualAddress());
	//WVP
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceSphere->GetGPUVirtualAddress());
	//テクスチャ
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU[Index]);
	//Light
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(3, directionalLightResource->GetGPUVirtualAddress());

	directX_->GetcommandList()->DrawIndexedInstanced(kSubdivision * kSubdivision * 6, 1, 0, 0, 0);
}
void MyEngine::MakeVertexBufferViewSphere()
{
	//リソースの先頭のアドレス
	vertexBufferViewSphere.BufferLocation = vertexResourceSphere->GetGPUVirtualAddress();
	//使用する頂点サイズ
	vertexBufferViewSphere.SizeInBytes = sizeof(VertexData) * 4 * kSubdivision * kSubdivision;
	//1頂点あたりのアドレス
	vertexBufferViewSphere.StrideInBytes = sizeof(VertexData);
}
void MyEngine::MakeIndexBufferViewSphere()
{
	//リソース先頭アドレス
	indexBufferViewSphere.BufferLocation = indexResourceSphere->GetGPUVirtualAddress();
	//使用するインデックスサイズ
	indexBufferViewSphere.SizeInBytes = sizeof(uint32_t) * 6 * kSubdivision * kSubdivision;
	//インデックスはuint32_t
	indexBufferViewSphere.Format = DXGI_FORMAT_R32_UINT;
}
#pragma endregion 球
#pragma region Box
void MyEngine::DrawBox(const float& width, const float& hight, const float& depth, const Transform& transform,const Matrix4x4& ViewportMatrix, const Vector4& color, const int Index)
{
#pragma region 
	int BoxIndex = kMaxBoxVertex + 1;
	for (int i = 0; i < kMaxBox; ++i) {
		if (IsusedBoxIndex[i] == false) {
			BoxIndex = (i * 36);
			IsusedBoxIndex[i] = true;
			break;
		}
	}
	if (BoxIndex < 0) {
		//0より少ない
		assert(false);
	}
	if (kMaxBoxVertex < BoxIndex) {
		//MaxSpriteより多い
		assert(false);
	}
#pragma endregion 位置決め

	vertexResourceBox->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataBox));

#pragma region flont
	//左下
	vertexDataBox[0].position = { 0.0f,0.0f,0.0f,1.0f };
	vertexDataBox[0].texcoord = { 0.0f,1.0f };
	//左上
	vertexDataBox[1].position = {0.0f,hight,0.0f,1.0f};
	vertexDataBox[1].texcoord = { 0.0f,0.0f };
	//右下
	vertexDataBox[2].position = { width ,0.0f,0.0f,1.0f};
	vertexDataBox[2].texcoord = { 1.0f,1.0f };
	//右上
	vertexDataBox[3].position = { width ,hight,0.0f,1.0f};
	vertexDataBox[3].texcoord = { 1.0f,0.0f };
#pragma endregion 正面
#pragma region Left
	//左下
	vertexDataBox[4].position = { width,0.0f,0.0f,1.0f };
	vertexDataBox[4].texcoord = { 0.0f,1.0f };
	//左上
	vertexDataBox[5].position = { width,hight,0.0f,1.0f };
	vertexDataBox[5].texcoord = { 0.0f,0.0f };
	//右下
	vertexDataBox[6].position = { width ,0.0f,depth,1.0f};
	vertexDataBox[6].texcoord = { 1.0f,1.0f };
	//右上
	vertexDataBox[7].position = { width ,hight,depth,1.0f};
	vertexDataBox[7].texcoord = { 1.0f,0.0f };
#pragma endregion 右面
#pragma region back
	//左下
	vertexDataBox[8].position = { width,0.0f,depth,1.0f };
	vertexDataBox[8].texcoord = { 0.0f,1.0f };
	//左上
	vertexDataBox[9].position = { width,hight,depth,1.0f };
	vertexDataBox[9].texcoord = { 0.0f,0.0f };
	//右下
	vertexDataBox[10].position = { 0.0f ,0.0f,depth,1.0f};
	vertexDataBox[10].texcoord = { 1.0f,1.0f };
	//右上
	vertexDataBox[11].position = { 0.0f ,hight,depth,1.0f};
	vertexDataBox[11].texcoord = { 1.0f,0.0f };
#pragma endregion 裏面
#pragma region right
	//左下
	vertexDataBox[12].position = { 0.0f,0.0f,depth,1.0f };
	vertexDataBox[12].texcoord = { 0.0f,1.0f };
	//左上
	vertexDataBox[13].position = { 0.0f,hight,depth,1.0f };
	vertexDataBox[13].texcoord = { 0.0f,0.0f };
	//右下
	vertexDataBox[14].position = { 0.0f ,0.0f,0.0f,1.0f};
	vertexDataBox[14].texcoord = { 1.0f,1.0f };
	//右上
	vertexDataBox[15].position = { 0.0f ,hight,0.0f,1.0f};
	vertexDataBox[15].texcoord = { 1.0f,0.0f };
#pragma endregion 左面
#pragma region bottom
	//左下
	vertexDataBox[16].position = { 0.0f,0.0f,depth,1.0f };
	vertexDataBox[16].texcoord = { 0.0f,1.0f };
	//左上
	vertexDataBox[17].position = { 0.0f,0.0f,0.0f,1.0f };
	vertexDataBox[17].texcoord = { 0.0f,0.0f };
	//右下
	vertexDataBox[18].position = { width ,0.0f,depth,1.0f};
	vertexDataBox[18].texcoord = { 1.0f,1.0f };
	//右上
	vertexDataBox[19].position = { width ,0.0f,0.0f,1.0f};
	vertexDataBox[19].texcoord = { 1.0f,0.0f };
#pragma endregion 底面
#pragma region top
	//左下
	vertexDataBox[20].position = { 0.0f,hight,0.0f,1.0f };
	vertexDataBox[20].texcoord = { 0.0f,1.0f };
	//左上
	vertexDataBox[21].position = { 0.0f,hight,depth,1.0f };
	vertexDataBox[21].texcoord = { 0.0f,0.0f };
	//右下
	vertexDataBox[22].position = { width ,hight,0.0f,1.0f};
	vertexDataBox[22].texcoord = { 1.0f,1.0f };
	//右上
	vertexDataBox[23].position = { width ,hight,depth,1.0f};
	vertexDataBox[23].texcoord = { 1.0f,0.0f };
#pragma endregion 上

	//インデックスリソースにデータを書き込む
	indexResourceBox->Map(0, nullptr, reinterpret_cast<void**>(&indexDataBox));
#pragma region flont
	//三角形1枚目
	indexDataBox[BoxIndex] = 0;indexDataBox[BoxIndex + 1] = 1;indexDataBox[BoxIndex + 2] = 2;
	//三角形2枚目
	indexDataBox[BoxIndex + 3] = 1;indexDataBox[BoxIndex + 4] = 3;indexDataBox[BoxIndex + 5] = 2;
#pragma endregion 正面
#pragma region Left
	//三角形1枚目
	indexDataBox[BoxIndex + 6] = 4;indexDataBox[BoxIndex + 7] = 5;indexDataBox[BoxIndex + 8] = 6;
	//三角形2枚目
	indexDataBox[BoxIndex + 9] = 5;indexDataBox[BoxIndex + 10] = 7;indexDataBox[BoxIndex + 11] = 6;
#pragma endregion 右面
#pragma region back
	//三角形1枚目
	indexDataBox[BoxIndex + 12] = 8;indexDataBox[BoxIndex + 13] = 9;indexDataBox[BoxIndex + 14] = 10;
	//三角形2枚目
	indexDataBox[BoxIndex + 15] = 9;indexDataBox[BoxIndex + 16] = 11;indexDataBox[BoxIndex + 17] = 10;
#pragma endregion 裏面
#pragma region right
	//三角形1枚目
	indexDataBox[BoxIndex + 18] = 12;indexDataBox[BoxIndex + 19] = 13;indexDataBox[BoxIndex + 20] = 14;
	//三角形2枚目
	indexDataBox[BoxIndex + 21] = 13;indexDataBox[BoxIndex + 22] = 15;indexDataBox[BoxIndex + 23] = 14;
#pragma endregion 左面
#pragma region bottom
	//三角形1枚目
	indexDataBox[BoxIndex + 24] = 16;indexDataBox[BoxIndex + 25] = 17;indexDataBox[BoxIndex + 26] = 18;
	//三角形2枚目
	indexDataBox[BoxIndex + 27] = 17;indexDataBox[BoxIndex + 28] = 19;indexDataBox[BoxIndex + 29] = 18;
#pragma endregion 底
#pragma region top
	//三角形1枚目
	indexDataBox[BoxIndex + 30] = 20;indexDataBox[BoxIndex + 31] = 21;indexDataBox[BoxIndex + 32] = 22;
	//三角形2枚目
	indexDataBox[BoxIndex + 33] = 21;indexDataBox[BoxIndex + 34] = 23;indexDataBox[BoxIndex + 35] = 22;
#pragma endregion 上

	//色の書き込み
	materialResourceBox->Map(0, nullptr, reinterpret_cast<void**>(&materialDataBox));
	materialDataBox->color = color;
	//ライティングをしない
	materialDataBox->enableLighting = false;
	//WVPを書き込むためのアドレス取得
	transformationMatrixResourceBox->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixDataBox));
	Matrix4x4 worldMatrixBox = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
	Matrix4x4 worldViewMatrixBox = Multiply(worldMatrixBox, ViewportMatrix);
	//
	transformationMatrixDataBox->WVP = worldViewMatrixBox;
	transformationMatrixDataBox->World = MakeIdentity4x4();

	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//頂点
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewBox);
	directX_->GetcommandList()->IASetIndexBuffer(&indexBufferViewBox);
	//色用のCBufferの場所を特定
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResourceBox->GetGPUVirtualAddress());
	//WVP用のCBufferの場所を特定
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceBox->GetGPUVirtualAddress());
	//テクスチャ
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU[Index]);
	//Light
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(3, directionalLightResource->GetGPUVirtualAddress());

	directX_->GetcommandList()->DrawIndexedInstanced(BoxIndex + 36, 1, 0, 0, 0);
}
void MyEngine::MakeVertexBufferViewBox()
{
	//リソースの先頭のアドレス
	vertexBufferViewBox.BufferLocation = vertexResourceBox->GetGPUVirtualAddress();
	//使用する頂点サイズ
	vertexBufferViewBox.SizeInBytes = sizeof(VertexData) * 24;
	//1頂点あたりのアドレス
	vertexBufferViewBox.StrideInBytes = sizeof(VertexData);
}
void MyEngine::MakeIndexBufferViewBox()
{
	//リソース先頭アドレス
	indexBufferViewBox.BufferLocation = indexResourceBox->GetGPUVirtualAddress();
	//使用するインデックスサイズ
	indexBufferViewBox.SizeInBytes = sizeof(uint32_t) * kMaxBoxVertex;
	//インデックスはuint32_t
	indexBufferViewBox.Format = DXGI_FORMAT_R32_UINT;
}
#pragma endregion ボックス

#pragma region Texture
int MyEngine::LoadTexture(const std::string& filePath)
{
	int SpriteIndex= kMaxTexture+1;
	for (int i = 0; i < kMaxTexture;++i) {
		if (IsusedTextureIndex[i] == false) {
			SpriteIndex = i;
			IsusedTextureIndex[i] = true;
			break;
		}
	}
	if (SpriteIndex<0) {
		//0より少ない
		assert(false);
	}
	if (kMaxTexture<SpriteIndex) {
		//MaxSpriteより多い
		assert(false);
	}
	//Textureを読んで転送する
	DirectX::ScratchImage mipImages = ImageFileOpen(filePath);
	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
	textureResource[SpriteIndex] = CreateTextureResource(directX_->GetDevice(), metadata);
	intermediateResource[SpriteIndex] = UploadTextureData(textureResource[SpriteIndex], mipImages);
	//metadataを基にSRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);
	
	//SRVを作成するDescriptorHeapの場所を決める
	textureSrvHandleCPU[SpriteIndex] = GetCPUDescriptorHandle(directX_->GetsrvDescriptorHeap(), descriptorSizeSRV, SpriteIndex);
	textureSrvHandleGPU[SpriteIndex] = GetGPUDescriptorHandle(directX_->GetsrvDescriptorHeap(), descriptorSizeSRV, SpriteIndex);
	//先頭はImGuiが使っているので次のを使う
	textureSrvHandleCPU[SpriteIndex].ptr += directX_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	textureSrvHandleGPU[SpriteIndex].ptr += directX_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	//SRVの作成
	directX_->GetDevice()->CreateShaderResourceView(textureResource[SpriteIndex], &srvDesc, textureSrvHandleCPU[SpriteIndex]);
	return SpriteIndex;
}

DirectX::ScratchImage MyEngine::ImageFileOpen(const std::string& filePath)
{
	//テクスチャファイルを読み込みプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = ConvertString(filePath);
	hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));
	//ミップマップの作成
	DirectX::ScratchImage mipImage{};
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImage);

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
	uint64_t intermediateSize = GetRequiredIntermediateSize(texture, 0, UINT(subresources.size()));
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
	directX_->GetcommandList()->ResourceBarrier(1, &barrier);
	return intermediateResource;
}


#pragma endregion テクスチャ

ID3D12Resource* MyEngine::CreateBufferResource(size_t sizeInBytes)
{
	ID3D12Resource* Resource = nullptr;
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
	hr = directX_->GetDevice()->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &ResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&Resource));
	assert(SUCCEEDED(hr));
	return Resource;
}
D3D12_CPU_DESCRIPTOR_HANDLE MyEngine::GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += (descriptorSize*index);
	return handleCPU;
}
D3D12_GPU_DESCRIPTOR_HANDLE MyEngine::GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index)
{
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += (descriptorSize * index);
	return handleGPU;
}