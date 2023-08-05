#pragma once
#include"Base/Model.h"
#include"IncludeStruct/Transform.h"
#include"Input/Input.h"
class Player
{
public:
	void Initialize();
	void Update();
	void Draw(const Matrix4x4& ViewMatrix);
private:
	void ApplyGlobalVariables();
	Input* input = nullptr;
	Model* model = nullptr;
	GlobalVariables* globalVariables = nullptr;
	Transform transform{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	Matrix4x4 AffineMatrix;
	float speed = 0.0f;
};

