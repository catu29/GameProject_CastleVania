#include "SceneManager.h"


SceneManager * SceneManager::instance = NULL;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
}

Scene * SceneManager::GetCurrentScene()
{
	return currentScene;
}

SceneManager * SceneManager::GetInstance()
{
	if (!instance)
	{
		instance = new SceneManager();
	}
	return instance;
}

bool SceneManager::Initialze(HWND hWnd)
{
	return true;
}



void SceneManager::Update(DWORD dt)
{
	currentScene->Update(dt);

	if (currentScene->GetChangingStage())
	{
		this->MoveToNextScene();
		this->LoadScene(sceneID);
	}
}


void SceneManager::LoadScene(int sceneID)
{
	switch (sceneID)
	{
	case GAME_MENU_SCENE:
		currentScene = new GameMenuScene();
		currentScene->Initialize();
		this->sceneID = sceneID;
		break;
	case GAME_INTRO_SCENE:
		currentScene = new GameIntroScene();
		this->sceneID = sceneID;
		currentScene->Initialize();
		break;
	case GAME_ENTRANCE_SCENE:
		currentScene = new GameEntranceScene();
		currentScene->Initialize();
		this->sceneID = sceneID;
		break;
	}

}

void SceneManager::MoveToNextScene()
{
	sceneID++;
}