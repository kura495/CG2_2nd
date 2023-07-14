#pragma once
#include"Bace\MyEngine.h"
#include"Scene\GameScene.h"
#include"GameObject\Camera\Camera.h"
#include"Utility\ImGuiManager.h"
//マネージャークラスの前方宣言
class GameManager;
//StatePatternの基底クラス
class GameState
{
public:
	virtual void Initialize() = 0;
	virtual void Up(GameManager* pGameManager) = 0;
	virtual void Down(GameManager* pGameManager) = 0;
	virtual void Gameloop() = 0;

private:

};
//StatePatternの派生クラス
class GameTitle :public GameState
{
public:
	void Initialize();
	void Up(GameState* pGameState);
	void Down(GameState* pGameState);
	void Gameloop();

private:

};
class GamePlay :public GameState
{
public:
	void Initialize();
	void Up(GameState* pGameState);
	void Down(GameState* pGameState);
	void Gameloop();

private:

};
class GameClear :public GameState
{
public:
	void Initialize();
	void Up(GameState* pGameState);
	void Down(GameState* pGameState);
	void Gameloop();

private:

};
//StatePatternの管理
class GameManager
{
public:
	GameManager();
	~GameManager();

	void Initialize();
	void Up();
	void Down();
	void ChangeState(GameState* newState);
	void Gameloop();
	
private:
	//Base
	WinApp* winApp = nullptr;
	DirectXCommon* directX = nullptr;
	MyEngine* myEngine = nullptr;
	//ウィンドウサイズ
	int32_t kClientWidth;
	int32_t kClientHeight;
	//State
	GameState* state=nullptr;
	//Scenes
	GameScene* gameScene = nullptr;

};


