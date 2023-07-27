#pragma once
#include"IncludeStruct/Material.h"
#include"IncludeStruct/ModelData.h"
#include"IncludeStruct/Transform.h"
#include"IncludeStruct/TransformationMatrix.h"
#include"Base/TextureManager.h"
#include"Base/Light.h"
#include"Utility/ImGuiManager.h"
#include"Math/MatrixCalc.h"
#include<d3d12.h>
#include<string>
#include<cassert>
#include<fstream>
#include<sstream>
#include<wrl.h>
class Model
{
public:
	void Initialize();
	void ImGui(const char* Title);
	Model* LoadObjFile(const std::string& directoryPath, const std::string& filename);
	void DrawModel(const Matrix4x4& ViewMatrix, const Vector4& color);
private:

	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	Light* light_ = nullptr;

	Transform transformObj{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	ModelData modelData;
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResourceObj = nullptr;
	//Obj用頂点データ
	VertexData* vertexDataObj = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewObj{};
	//マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResourceObj = nullptr;
	//色データ
	Material* materialDataObj = nullptr;
	//Sprite用WVPリソース
	Microsoft::WRL::ComPtr<ID3D12Resource>transformationMatrixResourceObj = nullptr;
	//Sprite用WVPデータ
	TransformationMatrix* transformationMatrixDataObj = nullptr;
	
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);
};