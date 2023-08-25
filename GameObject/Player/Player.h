#pragma once
#include"Base/Model.h"
#include"Base/WorldTransform.h"
#include"Base/ViewProjection.h"
#include"IncludeStruct/Transform.h"
#include"Input/Input.h"
class Player
{
public:
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewProjection);
private:
	void ApplyGlobalVariables();
	void ImGui();

	Input* input = nullptr;
	Model* model = nullptr;
	GlobalVariables* globalVariables = nullptr;
	WorldTransform worldTransform_;
	float speed = 0.0f;
};

