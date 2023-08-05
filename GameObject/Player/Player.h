#pragma once
#include"Base/Model.h"
#include"IncludeStruct/Transform.h"

class Player
{
public:
	void Initialize(Model* model_);
	void Update();
	void Draw(const Matrix4x4& ViewMatrix);
private:
	Model* model = nullptr;
	GlobalVariables* globalVariables = nullptr;
	Transform transform{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	Matrix4x4 AffineMatrix;
};

