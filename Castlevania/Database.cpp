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

	Textures::GetInstance()->Add(TEX_CANDLE_SOURCE_ID, TEX_CANDLE_SOURCE, D3DCOLOR_XRGB(34, 177, 76));

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
#pragma region Sprite Simon
	//turn back
	Sprites::GetInstance()->Add(-201, 249, 7, 265, 39, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//sit left
	Sprites::GetInstance()->Add(-200, 82, 7, 105, 39, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//idle left + walking left
	Sprites::GetInstance()->Add(-199, 0, 7, 24, 39, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-198, 29, 7, 47, 39, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-197, 55, 7, 76, 39, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//upstairs left
	Sprites::GetInstance()->Add(-196, 156, 7, 172, 39, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//downstairs left
	Sprites::GetInstance()->Add(-195, 131, 7, 147, 39, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//stand attack left
	Sprites::GetInstance()->Add(-194, 21, 46, 51, 78, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-193, 52, 46, 74, 78, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-192, 82, 46, 104, 78, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//sit attack left
	Sprites::GetInstance()->Add(-191, 20, 91, 50, 123, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-190, 49, 91, 71, 123, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-189, 79, 91, 101, 123, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//upstairs attack left
	Sprites::GetInstance()->Add(-188, 123, 47, 153, 79, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-187, 153, 47, 175, 79, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-186, 188, 47, 210, 79, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//downstairs attack left
	Sprites::GetInstance()->Add(-185, 123, 91, 153, 123, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-184, 153, 91, 174, 123, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-183, 188, 91, 210, 123, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));


	//eat sp item left
	Sprites::GetInstance()->Add(-182, 223, 89, 224, 121, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-181, 254, 89, 274, 121, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-180, 223, 47, 224, 79, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-179, 254, 47, 274, 79, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//======================================================================
	//sit right
	Sprites::GetInstance()->Add(-178, 164, 136, 188, 168, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//idle right + walking right
	Sprites::GetInstance()->Add(-177, 250, 136, 274, 168, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-176, 222, 136, 247, 168, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-175, 193, 136, 217, 168, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//upstairs right
	Sprites::GetInstance()->Add(-174, 103, 136, 119, 168, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//downstairs right
	Sprites::GetInstance()->Add(-173, 128, 136, 145, 168, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//stand attack right
	Sprites::GetInstance()->Add(-172, 224, 175, 248, 207, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-171, 193, 175, 217, 207, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-170, 163, 175, 193, 207, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//sit attack right
	Sprites::GetInstance()->Add(-169, 225, 220, 249, 252, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-168, 196, 220, 220, 252, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-167, 166, 220, 196, 252, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//upstairs attack right
	Sprites::GetInstance()->Add(-166, 122, 176, 146, 208, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-165, 92, 176, 116, 208, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-164, 57, 176, 81, 214, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//downstairs attack right
	Sprites::GetInstance()->Add(-163, 122, 220, 146, 252, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-162, 93, 220, 117, 252, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-161, 57, 220, 81, 258, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));

	//eat sp item right
	Sprites::GetInstance()->Add(-160, 26, 218, 50, 250, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-159, 2, 218, 26, 250, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-158, 26, 176, 50, 208, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
	Sprites::GetInstance()->Add(-157, 2, 176, 26, 208, Textures::GetInstance()->GetTexture(TEX_SIMON_ID));
#pragma endregion

#pragma region Sprite Whip
	//nomal left
	Sprites::GetInstance()->Add(100, 8, 9, 68, 38, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(101, 92, 9, 152, 31, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(102, 179, 9, 208, 22, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));

	//nomal right
	Sprites::GetInstance()->Add(103, 432, 9, 448, 38, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(104, 348, 9, 364, 31, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(105, 260, 9, 320, 38, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));

	//short left
	Sprites::GetInstance()->Add(112, 8, 52, 68, 81, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(113, 92, 52, 152, 74, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(114, 179, 52, 208, 65, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));

	//short right
	Sprites::GetInstance()->Add(115, 432, 52, 448, 38, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(116, 348, 52, 364, 74, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(117, 260, 52, 320, 65, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));

	//red left
	Sprites::GetInstance()->Add(106, 33, 133, 109, 162, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(107, 117, 133, 193, 155, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(108, 203, 133, 248, 145, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));

	//red right
	Sprites::GetInstance()->Add(109, 473, 133, 489, 162, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(110, 389, 133, 405, 155, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(111, 302, 133, 378, 145, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));

	//yellow left
	Sprites::GetInstance()->Add(118, 33, 93, 109, 122, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(119, 117, 93, 193, 115, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(120, 203, 93, 248, 105, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));

	//yellow right
	Sprites::GetInstance()->Add(121, 473, 93, 489, 122, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(122, 389, 93, 405, 115, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(123, 302, 93, 378, 105, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	
	//blue left
	Sprites::GetInstance()->Add(124, 33, 172, 109, 201, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(125, 117, 172, 193, 194, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(126, 203, 172, 248, 184, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));

	//blue right
	Sprites::GetInstance()->Add(127, 473, 172, 489, 201, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(128, 389, 172, 405, 194, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(129, 302, 172, 378, 184, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));

	//violet left
	Sprites::GetInstance()->Add(130, 33, 212, 109, 241, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(131, 117, 212, 193, 234, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(132, 203, 212, 248, 224, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));

	//violet right
	Sprites::GetInstance()->Add(133, 473, 212, 489, 241, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(134, 389, 212, 405, 234, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));
	Sprites::GetInstance()->Add(135, 302, 212, 378, 224, Textures::GetInstance()->GetTexture(TEX_WHIP_ID));


#pragma endregion

#pragma region Sprite Menu
	//load sprite to sprites map from textures map
	Sprites::GetInstance()->Add(0, 2, 2, 258, 226, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));

	//bat animation
	Sprites::GetInstance()->Add(1, 275, 2, 346, 57, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));
	Sprites::GetInstance()->Add(2, 353, 2, 424, 57, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));
	Sprites::GetInstance()->Add(3, 431, 2, 502, 57, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));
	Sprites::GetInstance()->Add(4, 511, 2, 582, 57, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));
	Sprites::GetInstance()->Add(5, 589, 2, 660, 57, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));

	Sprites::GetInstance()->Add(6, 275, 63, 346, 118, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));
	Sprites::GetInstance()->Add(7, 353, 63, 424, 118, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));
	Sprites::GetInstance()->Add(8, 431, 63, 502, 118, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));
	Sprites::GetInstance()->Add(9, 511, 63, 582, 118, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));
	Sprites::GetInstance()->Add(10, 589, 63, 660, 118, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));

	Sprites::GetInstance()->Add(11, 275, 125, 346, 180, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));
	Sprites::GetInstance()->Add(12, 353, 125, 424, 180, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));
	Sprites::GetInstance()->Add(13, 431, 125, 502, 180, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));
	Sprites::GetInstance()->Add(14, 511, 125, 582, 180, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));
	Sprites::GetInstance()->Add(15, 589, 125, 660, 180, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));


	//title animation
	Sprites::GetInstance()->Add(16, 75, 130, 186, 137, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));
	Sprites::GetInstance()->Add(17, 75, 138, 186, 145, Textures::GetInstance()->GetTexture(TEX_GAME_MENU_SCENE_ID));
#pragma endregion

#pragma region Sprite Intro
	//background
	Sprites::GetInstance()->Add(50, 6, 6, 262, 230, Textures::GetInstance()->GetTexture(TEX_GAME_INTRO_SCENE_ID));

	//bat
	Sprites::GetInstance()->Add(51, 287, 102, 295, 109, Textures::GetInstance()->GetTexture(TEX_GAME_INTRO_SCENE_ID));
	Sprites::GetInstance()->Add(52, 274, 102, 282, 110, Textures::GetInstance()->GetTexture(TEX_GAME_INTRO_SCENE_ID));

	//cloud
	Sprites::GetInstance()->Add(53, 268, 78, 300, 92, Textures::GetInstance()->GetTexture(TEX_GAME_INTRO_SCENE_ID));
#pragma endregion

#pragma region Sprite Entrance
	Sprites::GetInstance()->Add(99, 0, 0, 256, 64, Textures::GetInstance()->GetTexture(TEX_GAME_ENTRANCE_SCENE_A_ID));
	Sprites::GetInstance()->Add(98, 0, 0, 256, 112, Textures::GetInstance()->GetTexture(TEX_GAME_ENTRANCE_SCENE_B_ID));

#pragma endregion

#pragma region Sprite Large candle
	Sprites::GetInstance()->Add(401, 44, 21, 60, 53, Textures::GetInstance()->GetTexture(TEX_CANDLE_SOURCE_ID));
	Sprites::GetInstance()->Add(402, 71, 21, 87, 53, Textures::GetInstance()->GetTexture(TEX_CANDLE_SOURCE_ID));
#pragma endregion

#pragma region Sprite Object Hitted
	Sprites::GetInstance()->Add(403, 11, 73, 19, 86, Textures::GetInstance()->GetTexture(TEX_CANDLE_SOURCE_ID));
	Sprites::GetInstance()->Add(404, 27, 73, 35, 86, Textures::GetInstance()->GetTexture(TEX_CANDLE_SOURCE_ID));
	Sprites::GetInstance()->Add(405, 38, 73, 46, 86, Textures::GetInstance()->GetTexture(TEX_CANDLE_SOURCE_ID));
	Sprites::GetInstance()->Add(406, 52, 73, 60, 86, Textures::GetInstance()->GetTexture(TEX_CANDLE_SOURCE_ID));

#pragma endregion

#pragma region Sub Weapons
	//AXE
	Sprites::GetInstance()->Add(600, 0, 0, 16, 16, Textures::GetInstance()->GetTexture(TEX_SUBWEAPONS_ID));
	Sprites::GetInstance()->Add(601, 16, 0, 32, 16, Textures::GetInstance()->GetTexture(TEX_SUBWEAPONS_ID));
	Sprites::GetInstance()->Add(602, 32, 0, 48, 16, Textures::GetInstance()->GetTexture(TEX_SUBWEAPONS_ID));
	Sprites::GetInstance()->Add(603, 48, 0, 64, 16, Textures::GetInstance()->GetTexture(TEX_SUBWEAPONS_ID));

	//KNIFE
	Sprites::GetInstance()->Add(604, 48, 16, 64, 24, Textures::GetInstance()->GetTexture(TEX_SUBWEAPONS_ID));
	Sprites::GetInstance()->Add(605, 48, 24, 64, 32, Textures::GetInstance()->GetTexture(TEX_SUBWEAPONS_ID));

	//BOOMERANG
	Sprites::GetInstance()->Add(606, 0, 16, 16, 32, Textures::GetInstance()->GetTexture(TEX_SUBWEAPONS_ID));
	Sprites::GetInstance()->Add(607, 16, 16, 32, 32, Textures::GetInstance()->GetTexture(TEX_SUBWEAPONS_ID));
	Sprites::GetInstance()->Add(608, 32, 16, 48, 32, Textures::GetInstance()->GetTexture(TEX_SUBWEAPONS_ID));

#pragma endregion

#pragma region Sprite Item
	//small heart
	Sprites::GetInstance()->Add(800, 126, 39, 134, 47, Textures::GetInstance()->GetTexture(TEX_ITEM_ID));
	//big heart
	Sprites::GetInstance()->Add(801, 124, 59, 136, 69, Textures::GetInstance()->GetTexture(TEX_ITEM_ID));
	//whip upgrade
	Sprites::GetInstance()->Add(802, 44, 43, 61, 60, Textures::GetInstance()->GetTexture(TEX_ITEM_ID));
	//pot roast
	Sprites::GetInstance()->Add(803, 35, 157, 51, 170, Textures::GetInstance()->GetTexture(TEX_ITEM_ID));
	//money bag 100
	Sprites::GetInstance()->Add(804, 377, 43, 392, 58, Textures::GetInstance()->GetTexture(TEX_ITEM_ID));
	//money bag 400
	Sprites::GetInstance()->Add(805, 377, 68, 392, 83, Textures::GetInstance()->GetTexture(TEX_ITEM_ID));
	//money bag 700
	Sprites::GetInstance()->Add(806, 377, 92, 392, 107, Textures::GetInstance()->GetTexture(TEX_ITEM_ID));
	//cross
	Sprites::GetInstance()->Add(807, 181, 104, 197, 121, Textures::GetInstance()->GetTexture(TEX_ITEM_ID));
	//invisibility Poision
	Sprites::GetInstance()->Add(808, 290, 102, 303, 108, Textures::GetInstance()->GetTexture(TEX_ITEM_ID));
	//double shot
	Sprites::GetInstance()->Add(809, 206, 157, 220, 171, Textures::GetInstance()->GetTexture(TEX_ITEM_ID));
	//triple shot
	Sprites::GetInstance()->Add(810, 206, 184, 220, 198, Textures::GetInstance()->GetTexture(TEX_ITEM_ID));
	//crystal ball
	Sprites::GetInstance()->Add(811, 178, 156, 191, 171, Textures::GetInstance()->GetTexture(TEX_ITEM_ID));
	Sprites::GetInstance()->Add(812, 178, 182, 192, 198, Textures::GetInstance()->GetTexture(TEX_ITEM_ID));

#pragma endregion
}

void Database::CreateAnimation()
{
#pragma region Animation Simon
	LPANIMATION aniTurningBack = new Animation(120);
	aniTurningBack->Add(-201);
	Animations::GetInstance()->Add(-50, aniTurningBack); // 0 animation turn back

	LPANIMATION aniSitLeft = new Animation(120);
	aniSitLeft->Add(-200);
	Animations::GetInstance()->Add(-49, aniSitLeft); // 1 animation sit left

	LPANIMATION aniIdleLeft = new Animation(100);
	aniIdleLeft->Add(-199);
	Animations::GetInstance()->Add(-48, aniIdleLeft); // 2 animation idle left

	LPANIMATION aniWalkingLeft = new Animation(100);
	aniWalkingLeft->Add(-199);
	aniWalkingLeft->Add(-198);
	aniWalkingLeft->Add(-197);
	aniWalkingLeft->Add(-198);
	Animations::GetInstance()->Add(-47, aniWalkingLeft); //3 animation walking left

	LPANIMATION aniIdleUpStairLeft = new Animation(100);
	aniIdleUpStairLeft->Add(-196);
	Animations::GetInstance()->Add(-46, aniIdleUpStairLeft); // 4 animation idle upstair left

	LPANIMATION aniUpstairLeft = new Animation(120);
	aniUpstairLeft->Add(-196);
	aniUpstairLeft->Add(-198);
	Animations::GetInstance()->Add(-45, aniUpstairLeft); // 5 animation upstairs left

	LPANIMATION aniIdleDownStairLeft = new Animation(100);
	aniIdleDownStairLeft->Add(-195);
	Animations::GetInstance()->Add(-44, aniIdleDownStairLeft); // 6 animation idle downstair left

	LPANIMATION aniDownstairLeft = new Animation(120);
	aniDownstairLeft->Add(-195);
	aniDownstairLeft->Add(-198);
	Animations::GetInstance()->Add(-43, aniDownstairLeft); // 7 animation downstairs left

	LPANIMATION aniStandAttackLeft = new Animation(100);
	aniStandAttackLeft->Add(-194);
	aniStandAttackLeft->Add(-193);
	aniStandAttackLeft->Add(-192, 200);
	Animations::GetInstance()->Add(-42, aniStandAttackLeft); // 8 animation stand attack left

	LPANIMATION aniSitAttackLeft = new Animation(100);
	aniSitAttackLeft->Add(-191);
	aniSitAttackLeft->Add(-190);
	aniSitAttackLeft->Add(-189, 200);
	Animations::GetInstance()->Add(-41, aniSitAttackLeft); // 9 animation sit attack left


	LPANIMATION aniUpStairsAttackLeft = new Animation(100);
	aniUpStairsAttackLeft->Add(-188);
	aniUpStairsAttackLeft->Add(-187);
	aniUpStairsAttackLeft->Add(-186, 200);
	Animations::GetInstance()->Add(-40, aniUpStairsAttackLeft); // 10 animation upstairs attack left

	LPANIMATION aniDownStairsAttackLeft = new Animation(100);
	aniDownStairsAttackLeft->Add(-185);
	aniDownStairsAttackLeft->Add(-184);
	aniDownStairsAttackLeft->Add(-183, 200);
	Animations::GetInstance()->Add(-39, aniDownStairsAttackLeft); // 11 animation downstairs attack left
	
	LPANIMATION aniEatSpItemLeft = new Animation(120);
	aniEatSpItemLeft->Add(-182);
	aniEatSpItemLeft->Add(-181);
	aniEatSpItemLeft->Add(-180);
	aniEatSpItemLeft->Add(-179);
	Animations::GetInstance()->Add(-38, aniEatSpItemLeft); // 12 animation eat sp item left

	//=======================================================================================

	LPANIMATION aniSitRight = new Animation(120);
	aniSitRight->Add(-178);
	Animations::GetInstance()->Add(-37, aniSitRight); // 13 animation sit right

	LPANIMATION aniIdleRight = new Animation(120);
	aniIdleRight->Add(-177);
	Animations::GetInstance()->Add(-36, aniIdleRight); // 14 animation idle right

	LPANIMATION aniWalkingRight = new Animation(100);
	aniWalkingRight->Add(-177);
	aniWalkingRight->Add(-176);
	aniWalkingRight->Add(-175);
	aniWalkingRight->Add(-176);
	Animations::GetInstance()->Add(-35, aniWalkingRight); // 15 animation walking right

	LPANIMATION aniIdleUpStairRight = new Animation(100);
	aniIdleUpStairRight->Add(-174);
	Animations::GetInstance()->Add(-34, aniIdleUpStairRight); // 16 animation idle upstair right

	LPANIMATION aniUpstairRight = new Animation(120);
	aniUpstairRight->Add(-174);
	aniUpstairRight->Add(-176);
	Animations::GetInstance()->Add(-33, aniUpstairRight); // 17 animation upstairs right

	LPANIMATION aniIdleDownStairRight = new Animation(100);
	aniIdleDownStairRight->Add(-173);
	Animations::GetInstance()->Add(-32, aniIdleDownStairRight); // 18 animation idle downstair right

	LPANIMATION aniDownstairRight = new Animation(120);
	aniDownstairRight->Add(-173);
	aniDownstairRight->Add(-176);
	Animations::GetInstance()->Add(-31, aniDownstairRight); // 19 animation downstairs right

	LPANIMATION aniStandAttackRight = new Animation(100);
	aniStandAttackRight->Add(-172);
	aniStandAttackRight->Add(-171);
	aniStandAttackRight->Add(-170, 200);
	Animations::GetInstance()->Add(-30, aniStandAttackRight); // 20 animation stand attack right

	LPANIMATION aniSitAttackRight = new Animation(100);
	aniSitAttackRight->Add(-169);
	aniSitAttackRight->Add(-168);
	aniSitAttackRight->Add(-167, 200);
	Animations::GetInstance()->Add(-29, aniSitAttackRight); // 21 animation sit attack right

	LPANIMATION aniUpStairsAttackRight = new Animation(100);
	aniUpStairsAttackRight->Add(-166);
	aniUpStairsAttackRight->Add(-165);
	aniUpStairsAttackRight->Add(-164, 200);
	Animations::GetInstance()->Add(-28, aniUpStairsAttackRight); // 22 animation upstairs attack right

	LPANIMATION aniDownStairsAttackRight = new Animation(100);
	aniDownStairsAttackRight->Add(-163);
	aniDownStairsAttackRight->Add(-162);
	aniDownStairsAttackRight->Add(-161, 200);
	Animations::GetInstance()->Add(-27, aniDownStairsAttackRight); // 23 animation downstairs attack right

	LPANIMATION aniEatSpItemRight = new Animation(120);
	aniEatSpItemRight->Add(-160);
	aniEatSpItemRight->Add(-159);
	aniEatSpItemRight->Add(-158);
	aniEatSpItemRight->Add(-157);
	Animations::GetInstance()->Add(-26, aniEatSpItemRight); // 24 animation eat sp item attack right
#pragma endregion

#pragma region Animation Whip														
	LPANIMATION aniNomalLeft = new Animation(100);
	aniNomalLeft->Add(100);
	aniNomalLeft->Add(101);
	aniNomalLeft->Add(102, 200);
	Animations::GetInstance()->Add(100, aniNomalLeft); // 0 animation nomal left
					
	LPANIMATION aniNomalRight = new Animation(100);
	aniNomalRight->Add(103);
	aniNomalRight->Add(104);
	aniNomalRight->Add(105, 200);
	Animations::GetInstance()->Add(101, aniNomalRight); // 1 animation nomal right

	LPANIMATION aniRedLeft = new Animation(100);
	aniRedLeft->Add(106);
	aniRedLeft->Add(107);
	aniRedLeft->Add(108, 200);
	Animations::GetInstance()->Add(102, aniRedLeft); // 2 animation red left

	LPANIMATION aniRedRight = new Animation(100);
	aniRedRight->Add(109);
	aniRedRight->Add(110);
	aniRedRight->Add(111, 200);
	Animations::GetInstance()->Add(103, aniRedRight); // 3 animation red right

	LPANIMATION aniShortLeft = new Animation(100);
	aniShortLeft->Add(112);
	aniShortLeft->Add(113);
	aniShortLeft->Add(114, 200);
	Animations::GetInstance()->Add(104, aniShortLeft); // 4 animation short left

	LPANIMATION aniShortRight = new Animation(100);
	aniShortRight->Add(115);
	aniShortRight->Add(116);
	aniShortRight->Add(117, 200);
	Animations::GetInstance()->Add(105, aniShortRight); // 5 animation short right

	LPANIMATION aniYellowLeft = new Animation(100);
	aniYellowLeft->Add(118);
	aniYellowLeft->Add(119);
	aniYellowLeft->Add(120, 200);
	Animations::GetInstance()->Add(106, aniYellowLeft); // 6 animation yellow left

	LPANIMATION aniYellowRight = new Animation(100);
	aniYellowRight->Add(121);
	aniYellowRight->Add(122);
	aniYellowRight->Add(123, 200);
	Animations::GetInstance()->Add(107, aniYellowRight); // 7 animation yellow right

	LPANIMATION aniBlueLeft = new Animation(100);
	aniBlueLeft->Add(124);
	aniBlueLeft->Add(125);
	aniBlueLeft->Add(126, 200);
	Animations::GetInstance()->Add(108, aniBlueLeft); // 8 animation blue left

	LPANIMATION aniBlueRight = new Animation(100);
	aniBlueRight->Add(127);
	aniBlueRight->Add(128);
	aniBlueRight->Add(129, 200);
	Animations::GetInstance()->Add(109, aniBlueRight); // 9 animation blue right

	LPANIMATION aniVioletLeft = new Animation(100);
	aniVioletLeft->Add(130);
	aniVioletLeft->Add(131);
	aniVioletLeft->Add(132, 200);
	Animations::GetInstance()->Add(110, aniVioletLeft); // 10 animation violet left

	LPANIMATION aniVioletRight = new Animation(100);
	aniVioletRight->Add(133);
	aniVioletRight->Add(134);
	aniVioletRight->Add(135, 200);
	Animations::GetInstance()->Add(111, aniVioletRight); // 11 animation violet right
#pragma endregion

#pragma region Animation Menu
														
	LPANIMATION aniBat = new Animation(100);

	for (int i = 1; i <= 15; i++)
	{
		aniBat->Add(i);
	}
	Animations::GetInstance()->Add(0, aniBat);

	aniBat = new Animation(100);

	for (int i = 13; i <= 15; i++)
	{
		aniBat->Add(i);
	}
	Animations::GetInstance()->Add(-1, aniBat);

	LPANIMATION aniTitle = new Animation(300);
	for (int i = 16; i <= 17; i++)
	{
		aniTitle->Add(i);
	}
	Animations::GetInstance()->Add(1, aniTitle);

#pragma endregion

#pragma region Animation Intro
	LPANIMATION aniBatFly = new Animation(50);
	aniBatFly->Add(51);
	aniBatFly->Add(52);
	Animations::GetInstance()->Add(2, aniBatFly); // bat fly

	LPANIMATION aniCloudFly = new Animation(120);
	aniCloudFly->Add(53);
	Animations::GetInstance()->Add(3, aniCloudFly); // cloud

#pragma endregion

#pragma region Animation Large candle
	LPANIMATION aniBurn = new Animation(100);
	aniBurn->Add(401);
	aniBurn->Add(402);
	Animations::GetInstance()->Add(500, aniBurn); // nomal ani
#pragma endregion

#pragma region Animation Object Hitted
	LPANIMATION aniHit = new Animation(100);
	aniHit->Add(403);
	aniHit->Add(404);
	Animations::GetInstance()->Add(501, aniHit); //hitted 1

	LPANIMATION aniHit1 = new Animation(100);
	aniHit1->Add(405);
	aniHit1->Add(406);
	Animations::GetInstance()->Add(502, aniHit1); //hitted 2
#pragma endregion

#pragma region Sub Weapons
	//AXE
	LPANIMATION aniAxeRight = new Animation(100);
	aniAxeRight->Add(600);
	aniAxeRight->Add(601);
	aniAxeRight->Add(602);
	aniAxeRight->Add(603);
	Animations::GetInstance()->Add(600, aniAxeRight); // axe right

	LPANIMATION aniAxeLeft = new Animation(100);
	aniAxeLeft->Add(601);
	aniAxeLeft->Add(600);
	aniAxeLeft->Add(603);
	aniAxeLeft->Add(602);
	Animations::GetInstance()->Add(601, aniAxeLeft); // axe left



#pragma endregion

#pragma region Animation Item
	//1000 money bag
	LPANIMATION ani1000MoneyBag = new Animation(100);
	ani1000MoneyBag->Add(804);
	ani1000MoneyBag->Add(805);
	ani1000MoneyBag->Add(806);
	Animations::GetInstance()->Add(800, ani1000MoneyBag);

	//crystal ball
	LPANIMATION aniCrystalBall = new Animation(100);
	aniCrystalBall->Add(811);
	aniCrystalBall->Add(812);
	Animations::GetInstance()->Add(801, aniCrystalBall);

#pragma endregion
}