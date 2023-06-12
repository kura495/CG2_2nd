#pragma once
#include"MyEngine.h"
#include"Camera.h"
class GameScene
{
public:
	void Initialize(DirectXCommon* directX, MyEngine* myEngine,WinApp* winApp, int32_t kClientWidth,int32_t kClientHeight);

	void UpDate();

	void Draw();

	void Release();
	
private:
	int32_t kClientWidth_=0;
	int32_t kClientHeight_=0;
	DirectXCommon* directX_ = nullptr;
	MyEngine* myEngine_ = nullptr;
	Camera* camera_ = nullptr;
	Vector4 Left = {-0.5f,-0.5f,0.0f,1.0f};
	Vector4 Top = { 0.0f,0.5f,0.0f,1.0f };
	Vector4 Right = { 0.5f,-0.5f,0.0f,1.0f };
	Vector4 Color = { 1.0f,0.0f,0.0f,1.0f };
	
	Transform transform{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};

};

