#include"Base/Model.h"

void Model::Initialize(const std::string& directoryPath, const std::string& filename)
{
	directX_ = DirectXCommon::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	light_ = Light::GetInstance();
	materialResourceObj = CreateBufferResource(sizeof(Material));
	transformationMatrixResourceObj = CreateBufferResource(sizeof(TransformationMatrix));

	modelData_ = LoadObjFile(directoryPath,filename);
	vertexResourceObj.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataObj));
	std::memcpy(vertexDataObj, modelData_.vertices.data(), sizeof(VertexData) * modelData_.vertices.size());
}

void Model::ImGui(const char* Title)
{
	ImGui::Begin(Title);
	float ImGuiScaleObj[Vector3D] = { transformObj.scale.x,transformObj.scale.y ,transformObj.scale.z };
	ImGui::SliderFloat3("ScaleObj", ImGuiScaleObj, 1, 30, "%.3f");
	transformObj.scale = { ImGuiScaleObj[x],ImGuiScaleObj[y],ImGuiScaleObj[z] };
	float ImGuiRotateObj[Vector3D] = { transformObj.rotate.x,transformObj.rotate.y ,transformObj.rotate.z };
	ImGui::SliderFloat3("RotateObj", ImGuiRotateObj, -7, 7, "%.3f");
	transformObj.rotate = { ImGuiRotateObj[x],ImGuiRotateObj[y],ImGuiRotateObj[z] };
	float ImGuiTranslateObj[Vector3D] = { transformObj.translate.x,transformObj.translate.y ,transformObj.translate.z };
	ImGui::SliderFloat3("TranslateObj", ImGuiTranslateObj, -10, 10, "%.3f");
	transformObj.translate = { ImGuiTranslateObj[x],ImGuiTranslateObj[y],ImGuiTranslateObj[z] };
	ImGui::End();
}

Model* Model::CreateModelFromObj(const std::string& directoryPath, const std::string& filename)
{
	Model* model=new Model();
	model->Initialize(directoryPath,filename);
	return model;
}

void Model::DrawModel(const Matrix4x4& ViewMatrix, const Vector4& color)
{

	materialResourceObj.Get()->Map(0, nullptr, reinterpret_cast<void**>(&materialDataObj));

	//ライティングをしない
	materialDataObj->enableLighting = false;
	materialDataObj->color = color;
	materialDataObj->uvTransform = MakeIdentity4x4();

	transformationMatrixResourceObj.Get()->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixDataObj));
	Matrix4x4 worldMatrixObj = MakeAffineMatrix(transformObj.scale, transformObj.rotate, transformObj.translate);
	transformationMatrixDataObj->WVP = Multiply(worldMatrixObj, ViewMatrix);
	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	transformationMatrixDataObj->World = MakeIdentity4x4();

	//頂点
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewObj);
	//色用のCBufferの場所を特定
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResourceObj->GetGPUVirtualAddress());
	//WVP
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceObj->GetGPUVirtualAddress());
	//テクスチャ
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureManager_->GetGPUHandle(modelData_.TextureIndex));
	//Light
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(3, light_->GetDirectionalLight()->GetGPUVirtualAddress());

	directX_->GetcommandList()->DrawInstanced(UINT(modelData_.vertices.size()), 1, 0, 0);
}


ModelData Model::LoadObjFile(const std::string& directoryPath, const std::string& filename)
{
	ModelData modelData;//構築するモデルデータ
	std::vector<Vector4>positions;//位置　vを保存
	std::vector<Vector2>texcoords;//テクスチャ座標　vtを保存
	std::vector<Vector3>normals;//法線　vnを保存
	std::string line;//ファイルから読んだ一行を格納するもの
	std::ifstream file(directoryPath + "/" + filename);
	assert(file.is_open());//開けなかったら止める
	while (std::getline(file, line)) {
		std::string identifier;
		std::istringstream s(line);
		s >> identifier;//先頭の識別子を読む
		if (identifier == "v") {
			Vector4 position;
			s >> position.x >> position.y >> position.z;
			//右手系から左手系へ
			position.z *= -1.0f;
			position.w = 1.0f;
			positions.push_back(position);
		}
		else if (identifier == "vt") {
			Vector2 texcoord;
			s >> texcoord.x >> texcoord.y;
			texcoord.y = 1.0f - texcoord.y;
			texcoords.push_back(texcoord);
		}
		else if (identifier == "vn") {
			Vector3 normal;
			s >> normal.x >> normal.y >> normal.z;
			//右手系から左手系へ
			normal.z *= -1.0f;
			normals.push_back(normal);
		}
		else if (identifier == "f") {
			//面は三角形限定
			VertexData triamgle[3];
			for (int32_t faceVertex = 0; faceVertex < 3; ++faceVertex) {
				std::string vertexDefinition;
				s >> vertexDefinition;
				//頂点の要素へのIndexは「位置/UV/法線」で格納されているので、分解してIndexを取得する
				std::istringstream v(vertexDefinition);
				uint32_t elementIndices[3];
				for (int32_t element = 0; element < 3; ++element) {
					std::string index;
					std::getline(v, index, '/');// /区切りでインデックスを読んでいく
					elementIndices[element] = std::stoi(index);
				}
				Vector4 position = positions[elementIndices[0] - 1];
				Vector2 texcoord = texcoords[elementIndices[1] - 1];
				Vector3 normal = normals[elementIndices[2] - 1];
				//VertexData vertex = { position,texcoord,normal };
				//modelData.vertices.push_back(vertex);
				triamgle[faceVertex] = { position,texcoord,normal };

			}
			modelData.vertices.push_back(triamgle[2]);
			modelData.vertices.push_back(triamgle[1]);
			modelData.vertices.push_back(triamgle[0]);
		}
		else if (identifier == "mtllib") {
			//materialTemplateLibraryファイルの名前を取得する
			std::string materialFilename;
			s >> materialFilename;
			modelData.material = LoadMaterialTemplateFile(directoryPath, materialFilename);
		}
	}
	modelData.TextureIndex = textureManager_->LoadTexture(modelData.material.textureFilePath);
	//頂点リソースを作る
	vertexResourceObj = CreateBufferResource(sizeof(VertexData) * modelData.vertices.size());
	vertexBufferViewObj.BufferLocation = vertexResourceObj.Get()->GetGPUVirtualAddress();
	vertexBufferViewObj.SizeInBytes = UINT(sizeof(VertexData) * modelData.vertices.size());
	vertexBufferViewObj.StrideInBytes = sizeof(VertexData);
	return modelData;
}

MaterialData Model::LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename)
{
	MaterialData materialData;//構築するMaterialData
	std::string line;//ファイルから読んだ1行を格納するもの
	std::ifstream file(directoryPath + '/' + filename);//ファイルを開く
	assert(file.is_open());//開けなかったら止める
	while (std::getline(file, line)) {
		std::string identifier;
		std::istringstream s(line);
		s >> identifier;
		//identifierに応じた処理
		if (identifier == "map_Kd") {
			std::string textureFilename;
			s >> textureFilename;
			//連結してファイルパスにする
			materialData.textureFilePath = directoryPath + "/" + textureFilename;
		}
	}

	return materialData;
}

Microsoft::WRL::ComPtr<ID3D12Resource> Model::CreateBufferResource(size_t sizeInBytes)
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