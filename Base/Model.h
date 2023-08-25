#pragma once
#include "Material.h"
#include "Transform.h"
#include "VertexData.h"
#include "ModelData.h"
#include "TextureManager.h"
#include "Light.h"
#include "ImGuiManager.h"
#include "GlobalVariables.h"
#include "MatrixCalc.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <d3d12.h>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#include <wrl.h>

class Model
{
public:
	void Initialize(const std::string& directoryPath, const std::string& filename);
	void ImGui(const char* Title);
	static Model* CreateModelFromObj(const std::string& directoryPath, const std::string& filename);
	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);
	void Draw(const WorldTransform& transform,const ViewProjection& ViewMatrix);
private:

	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	Light* light_ = nullptr;
	//フラグたち
	int32_t lightFlag = Lighting::harfLambert;
	//
	ModelData modelData_;

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource = nullptr;
	VertexData* vertexData = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource = nullptr;
	Material* materialData = nullptr;
	Vector4 color_ = { 1.0f,1.0f,1.0f,1.0f };
	
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

};