#include"Scenes/Manager/GameManager.h"
int GameState::StateNo;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	GameManager* gameManager=new GameManager();
	gameManager->Initialize();
	gameManager->Gameloop();
	return 0;
}

