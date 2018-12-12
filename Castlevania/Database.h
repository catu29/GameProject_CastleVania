#pragma once
#include "d3d9.h"
#include "Textures.h"
#include "Sprites.h"
#include "Animations.h"

#define TEX_SIMON_SOURCE			"Resource\\Simon\\Simon.png"
#define TEX_WHIP_SOURCE				"Resource\\Weapons\\Whip.png"
#define TEX_GAME_MENU_SOURCE		"Resource\\GameMenuScene\\GameMenu.png"
#define TEX_GAME_INTRO_SOURCE		"Resource\\GameIntroScene\\GameIntro.png"
#define TEX_GAME_ENTRANCE_A_SOURCE	"Resource\\Map\\MapState1_a_TileSet.png"
#define TEX_GAME_ENTRANCE_B_SOURCE	"Resource\\Map\\MapState1_b_TileSet.png"
#define TEX_OBJECT_SOURCE			"Resource\\Object\\Object.png"
#define TEX_SUBWEAPONS_SOURCE		"Resource\\Weapons\\SubWeapons.png"
#define TEX_BBOX_SOURCE				"Resource\\BoundingBox.png"
#define TEX_ITEM_SOURCE				"Resource\\Item\\Item.png"
#define TEX_ENEMY_SOURCE			"Resource\\Enemy\\Enemy.png"

#define TEX_SIMON_ID					0
#define TEX_WHIP_ID						1
#define TEX_GAME_MENU_SCENE_ID			2
#define TEX_GAME_INTRO_SCENE_ID			3
#define TEX_GAME_ENTRANCE_SCENE_A_ID	4
#define TEX_GAME_ENTRANCE_SCENE_B_ID	9
#define TEX_OBJECT_ID					5
#define TEX_SUBWEAPONS_ID				6
#define TEX_BBOX_ID						7		// special texture to draw object bounding box
#define TEX_ITEM_ID						8
#define TEX_ENEMY_ID					10

#define TXT_SIMON_SPRITE_SOURCE			"Resource\\Simon\\Simon_Sprite.txt"
#define TXT_SIMON_ANI_SOURCE			"Resource\\Simon\\Simon_Ani.txt"

#define TXT_WHIP_SPRITE_SOURCE			"Resource\\Weapons\\Whip_Sprite.txt"
#define TXT_WHIP_ANI_SOURCE				"Resource\\Weapons\\Whip_Ani.txt"

#define TXT_GAMEMENU_SPRITE_SOURCE		"Resource\\GameMenuScene\\GameMenu_Sprite.txt"
#define TXT_GAMEMENU_ANI_SOURCE			"Resource\\GameMenuScene\\GameMenu_Ani.txt"

#define TXT_GAMEINTRO_SPRITE_SOURCE		"Resource\\GameIntroScene\\GameIntro_Sprite.txt"
#define TXT_GAMEINTRO_ANI_SOURCE		"Resource\\GameIntroScene\\GameIntro_Ani.txt"

#define TXT_OBJECT_SPRITE_SOURCE		"Resource\\Object\\Object_Sprite.txt"
#define TXT_OBJECT_ANI_SOURCE			"Resource\\Object\\Object_Ani.txt"

#define TXT_WALKINGGHOST_SPRITE_SOURCE	"Resource\\Enemy\\WalkingGhost_Sprite.txt"
#define TXT_WALKINGGHOST_ANI_SOURCE		"Resource\\Enemy\\WalkingGhost_Ani.txt"

#define TXT_ITEM_SPRITE_SOURCE			"Resource\\Item\\Item_Sprite.txt"
#define TXT_ITEM_ANI_SOURCE				"Resource\\Item\\Item_Ani.txt"

#define TXT_SW_SPRITE_SOURCE			"Resource\\Weapons\\SW_Sprite.txt"
#define TXT_SW_ANI_SOURCE				"Resource\\Weapons\\SW_Ani.txt"

class Database
{
	static Database * instance;
public:
	Database();
	~Database();
	static Database * GetInstance();

	void LoadTexture();
	void CreateSprite();
	void CreateAnimation();
};

