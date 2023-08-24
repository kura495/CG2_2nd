#pragma once
#include"IgameState.h"
#include"Base/MyEngine.h"
#include"IncludeStruct/ModelData.h"
#include"Audio/XAudio2.h"
#include"Input/Input.h"
#include"Base/Mesh.h"
#include"Base/Sprite.h"
#include"Base/Light.h"
#include"Base/Sphere.h"
#include"Base/TextureManager.h"
#include"Base/Model.h"
#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include<dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include"GameObject/Camera/Camera.h"
#include"GameObject/Player/Player.h"
#include "Base/WorldTransform.h"
#include "Base/ViewProjection.h"

class GamePlayState :public GameState
{
public:

	void Initialize();
	void Update();
	void Draw();
private:
	//基本機能ズ
	MyEngine* myEngine = nullptr;
	Camera* camera_ = nullptr;
	TextureManager* textureManager_ = nullptr;	
	Input* input = nullptr;
	XAudio2* Audio=nullptr;
	Light* light_ = nullptr;
	DirectXCommon* DirectX_ = nullptr;
	GlobalVariables* globalVariables = nullptr;
	Model* model = nullptr;
	//
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	//3Dオブジェクトたち
	Player* player = nullptr;
	Transform transform{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	Sphere* sphere;
	//2Dオブジェクトたち
	
	//
	//テクスチャハンドルたち
	int Texture;
	//
	//サウンドハンドルたち
	uint32_t mokugyo;
	//
	int Pan = 0;
	float Volume = 0.1f;
	//ImGui用フラッグ
	bool IsMeshFlag = false;
	bool IsSpriteFlag = false;
	bool IsSphereFlag = false;
	bool IsPlaneFlag = false;
	bool IsTeapotFlag = false;
	bool IsBunnyFlag = false;
	bool IsMultiMeshFlag = false;
	bool IsMultiMaterialFlag = false;
	bool IsSuzanneFlag = false;
	bool IsBaseFlag = false;
	bool IsLightFlag = false;
	bool IsCameraFlag = false;
	//２こめ
	bool IsChengePipeline = false;
	bool IsMesh2Flag = false;
	bool IsSprite2Flag = false;
	bool IsSphere2Flag = false;
	bool IsBunny2Flag = false;
	bool IsTeapot2Flag = false;
	//
	//Sprite用の位置
	Vector4 LeftTop[2] = {
		{ 0.0f,0.0f,0.0f,1.0f },
		{ 320.0f,0.0f,0.0f,1.0f }
	};
	Vector4 LeftBottom[2] = {
		{ 0.0f,180.0f,0.0f,1.0f },
		{ 320.0f,180.0f,0.0f,1.0f }
	};
	Vector4 RightTop[2] = {
		{ 320.0f,0.0f,0.0f,1.0f },
		{ 640.0f,0.0f,0.0f,1.0f }
	};
	Vector4 RightBottom[2] = {
		{ 320.0f,180.0f,0.0f,1.0f },
		{ 640.0f,180.0f,0.0f,1.0f }
	};
	//
};