#include "Database.h"

Database * Database::instance = NULL;

Database::Database()
{
}

Database::~Database()
{
}

Database * Database::GetInstance()
{
	if (instance == NULL)
	{
		instance = new Database();
	}
	return instance;
}

void Database::LoadTexture()
{
	Textures::GetInstance()->Add(TEX_SIMON_ID, TEX_SIMON_SOURCE, D3DCOLOR_XRGB(0, 128, 128));

	Textures::GetInstance()->Add(TEX_WHIP_ID, TEX_WHIP_SOURCE, D3DCOLOR_XRGB(0, 128, 128));

	Textures::GetInstance()->Add(TEX_OBJECT_ID, TEX_OBJECT_SOURCE, D3DCOLOR_XRGB(34, 177, 76));

	Textures::GetInstance()->Add(TEX_GAME_MENU_SCENE_ID, TEX_GAME_MENU_SOURCE, D3DCOLOR_XRGB(128, 0, 0));

	Textures::GetInstance()->Add(TEX_GAME_INTRO_SCENE_ID, TEX_GAME_INTRO_SOURCE, D3DCOLOR_XRGB(128, 0, 0));

	Textures::GetInstance()->Add(TEX_GAME_ENTRANCE_SCENE_A_ID, TEX_GAME_ENTRANCE_A_SOURCE, D3DCOLOR_XRGB(255, 0, 255));

	Textures::GetInstance()->Add(TEX_GAME_ENTRANCE_SCENE_B_ID, TEX_GAME_ENTRANCE_B_SOURCE, D3DCOLOR_XRGB(255, 0, 255));

	Textures::GetInstance()->Add(TEX_SUBWEAPONS_ID, TEX_SUBWEAPONS_SOURCE, D3DCOLOR_XRGB(255, 0, 255));

	Textures::GetInstance()->Add(TEX_BBOX_ID, TEX_BBOX_SOURCE, D3DCOLOR_XRGB(255, 255, 255));

	Textures::GetInstance()->Add(TEX_ITEM_ID, TEX_ITEM_SOURCE, D3DCOLOR_XRGB(128, 0, 0));

	Textures::GetInstance()->Add(TEX_ENEMY_ID, TEX_ENEMY_SOURCE, D3DCOLOR_XRGB(96, 68, 106));
}

void Database::CreateSprite()
{
	Sprites::GetInstance()->LoadDataFromFile(TXT_SIMON_SPRITE_SOURCE, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	Sprites::GetInstance()->LoadDataFromFile(TXT_WHIP_SPRITE_SOURCE, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));

	Sprites::GetInstance()->LoadDataFromFile(TXT_GAMEMENU_SPRITE_SOURCE, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));

	Sprites::GetInstance()->LoadDataFromFile(TXT_GAMEINTRO_SPRITE_SOURCE, Textures::GetInstance()->GetTexture(TEX_GAME_INTRO_SCENE_ID));

	Sprites::GetInstance()->LoadDataFromFile(TXT_OBJECT_SPRITE_SOURCE, Textures::GetInstance()->GetTexture(TEX_OBJECT_ID));

	Sprites::GetInstance()->LoadDataFromFile(TXT_ITEM_SPRITE_SOURCE, Textures::GetInstance()->GetTexture(TEX_ITEM_ID));

	Sprites::GetInstance()->LoadDataFromFile(TXT_SW_SPRITE_SOURCE, Textures::GetInstance()->GetTexture(TEX_SUBWEAPONS_ID));

#pragma region Sprite Entrance Map
	Sprites::GetInstance()->Add(99, 0, 0, 256, 64, Textures::GetInstance()->GetTexture(TEX_GAME_ENTRANCE_SCENE_A_ID));
	Sprites::GetInstance()->Add(98, 0, 0, 256, 112, Textures::GetInstance()->GetTexture(TEX_GAME_ENTRANCE_SCENE_B_ID));
#pragma endregion

#pragma region Sprite Enemy
	// Walking Ghost
	Sprites::GetInstance()->LoadDataFromFile(TXT_WALKINGGHOST_SPRITE_SOURCE, Textures::GetInstance()->GetTexture(TEX_ENEMY_ID));

#pragma endregion 
}

void Database::CreateAnimation()
{
	Animations::GetInstance()->LoadDataFromFile(TXT_SIMON_ANI_SOURCE);

	Animations::GetInstance()->LoadDataFromFile(TXT_WHIP_ANI_SOURCE);

	Animations::GetInstance()->LoadDataFromFile(TXT_GAMEMENU_ANI_SOURCE);

	Animations::GetInstance()->LoadDataFromFile(TXT_GAMEINTRO_ANI_SOURCE);

	Animations::GetInstance()->LoadDataFromFile(TXT_OBJECT_ANI_SOURCE);

	Animations::GetInstance()->LoadDataFromFile(TXT_ITEM_ANI_SOURCE);

#pragma region Animation Enemy
	//walking ghost
	Animations::GetInstance()->LoadDataFromFile(TXT_WALKINGGHOST_ANI_SOURCE);
#pragma endregion 
}