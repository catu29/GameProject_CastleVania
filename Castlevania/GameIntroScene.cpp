#include "GameIntroScene.h"

GameIntroScene::GameIntroScene()
{
	simonPos = D3DXVECTOR3(240, 169, 0);
	bat1Pos = D3DXVECTOR3(30, 120, 0);
	bat2Pos = D3DXVECTOR3(114, 93, 0);
	cloudPos = D3DXVECTOR3(256, 64, 0);
	gameTime = GetTickCount();
}


GameIntroScene::~GameIntroScene()
{
}

void GameIntroScene::Update(DWORD dt)
{
	Scene::Update(dt);

	bat1Pos += D3DXVECTOR3(dt * 0.005f, dt * -0.005f, 0);
	bat2Pos += D3DXVECTOR3(dt * -0.005f, dt * -0.005f, 0);
	cloudPos += D3DXVECTOR3(dt * -0.01f, 0, 0);

	if (simonPos.x > 120)
	{
		simonPos += D3DXVECTOR3(dt * -0.018f, 0, 0);
	}
	else
	{
		simonPos = D3DXVECTOR3(120, 169, 0);
		if (GetTickCount() - gameTime >= 10000)
		{
			this->SetChangingStage(true);
		}
	}

	
}

void GameIntroScene::Initialize()
{
	this->isChangeStage = false;
}

void GameIntroScene::DestroyAll()
{

}

void GameIntroScene::Draw()
{
	Sprites::GetInstance()->GetSprite(50)->Draw(0, 0);

	Animations::GetInstance()->GetAnimation(2)->Render(bat1Pos.x, bat1Pos.y);
	Animations::GetInstance()->GetAnimation(2)->Render(bat2Pos.x, bat2Pos.y);
	Animations::GetInstance()->GetAnimation(3)->Render(cloudPos.x, cloudPos.y);

	if (simonPos.x > 120)
	{
		Animations::GetInstance()->GetAnimation(-47)->Render(simonPos.x, simonPos.y);
	}
	else
	{
		Animations::GetInstance()->GetAnimation(-50)->Render(simonPos.x, simonPos.y);
	}
	

}

void GameIntroScene::OnKeyUp(int keyCode)
{

}

void GameIntroScene::OnKeyDown(int keyCode)
{

}

void GameIntroScene::KeyState()
{

}
