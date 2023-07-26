#pragma once
#include"IgameState.h"
#include"Base/MyEngine.h"
#include"GameObject/Camera/Camera.h"
#include"IncludeStruct/ModelData.h"
#include"Audio/XAudio2.h"
#include"Input/Input.h"
#include"Base/Mesh.h"
#include"Base/Sprite.h"
#include"Base/Light.h"
#include"Base/Sphere.h"
#include"Base/TextureManager.h"
#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include<dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

class GamePlayState :public GameState
{
public:

	void Initialize();
	void Update();
	void Draw();

private:

	MyEngine* myEngine = nullptr;
	Camera* camera_ = nullptr;
	Mesh* mesh = nullptr;
	Mesh* mesh2 = nullptr;
	Sprite* sprite = nullptr;
	Sprite* sprite2 = nullptr;
	Sphere* sphere = nullptr;
	Sphere* sphere2 = nullptr;
	Light* light_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	uint32_t TextureHundle;
	uint32_t MonsterBall;

	Vector4 Color[2] = { 1.0f,1.0f,1.0f,1.0f };
	//Sprite
	Vector4 LeftTop[2] = {
		{ 0.0f,0.0f,0.0f,1.0f },
		{ 640.0f,0.0f,0.0f,1.0f }
	};
	Vector4 LeftBottom[2] = {
		{ 0.0f,360.0f,0.0f,1.0f },
		{ 640.0f,360.0f,0.0f,1.0f }
	};
	Vector4 RightTop[2] = {
		{ 640.0f,0.0f,0.0f,1.0f },
		{ 1280.0f,0.0f,0.0f,1.0f }

	};
	Vector4 RightBottom[2] = {
		{ 640.0f,360.0f,0.0f,1.0f },
		{ 1280.0f,360.0f,0.0f,1.0f }
	};
	int UV;
	int Ball;
	int Base;
	int Max;
	bool useMonsterBall = true;
	int SphereTexture = 0;
	Transform Box = {
		{2.0f,2.0f,2.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	Transform Box2 = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,10.0f},
	};
	ModelData modelData;
	ModelData modelData2;

	Input* input = nullptr;
	std::array<BYTE, 256> keys;
	std::array<BYTE, 256> preKeys;
	XAudio2* Audio=nullptr;
	int mokugyo;
};