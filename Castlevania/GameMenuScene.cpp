#include "GameMenuScene.h"

GameMenuScene::GameMenuScene()
{
	gameTime = GetTickCount();
}


GameMenuScene::~GameMenuScene()
{

}

void GameMenuScene::Update(DWORD dt)
{
	Scene::Update(dt);
}

void GameMenuScene::Initialize()
{
	this->isChangeStage = false;
}

void GameMenuScene::Draw()
{
	Sprites::GetInstance()->GetSprite(0)->Draw(0, 0);

	Animations::GetInstance()->GetAnimation(1)->Render(73, 128);
  
	
	if (GetTickCount() - gameTime <= 1500)
	{
		Animations::GetInstance()->GetAnimation(0)->Render(184, 97);
	}
	else
	{
		Animations::GetInstance()->GetAnimation(-1)->Render(184, 97);
	}
	
	
}

void GameMenuScene::DestroyAll()
{

}

void GameMenuScene::OnKeyUp(int keyCode)
{

}

void GameMenuScene::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_SPACE:

		this->SetChangingStage(true);

		break;
	}
}

void GameMenuScene::KeyState()
{

}
