#include "UI.h"
#include "Simon.h"
#include "Graphics.h"
#include "Textures.h"

#define UI_TEX "Resource\\UI\\UI.png"

UI::UI(int _simonHP, int _simonEnergy, int _simonLife, int _stage)
{
	simonHP = _simonHP;
	simonEnergy = _simonEnergy;
	simonLife = _simonLife;
	stage = _stage;
	score = 0;

	enemyHP = 16;
	LoadResource();
}

UI::~UI()
{
}

void UI::LoadResource()
{
	Textures::GetInstance()->Add(300, UI_TEX, D3DCOLOR_XRGB(255, 0, 255));

	//sprite heart
	Sprites::GetInstance()->Add(301, 0, 17, 8, 25, Textures::GetInstance()->GetTexture(300));
	//sprite simon HP
	Sprites::GetInstance()->Add(302, 12, 19, 15, 25, Textures::GetInstance()->GetTexture(300));
	//sprite Enemy HP
	Sprites::GetInstance()->Add(303, 19, 19, 22, 25, Textures::GetInstance()->GetTexture(300));
	//sprite No HP
	Sprites::GetInstance()->Add(304, 26, 19, 29, 25, Textures::GetInstance()->GetTexture(300));
	//sprite Item square
	Sprites::GetInstance()->Add(305, 33, 19, 65, 41, Textures::GetInstance()->GetTexture(300));

}

bool UI::Initialize()
{
	font = NULL;
	AddFontResourceEx(GAME_FONT, FR_PRIVATE, NULL);
	HRESULT result = D3DXCreateFont(
		Graphics::GetInstance()->device, 8, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, "Press Start", &font);

	if (!SUCCEEDED(result))
	{
		return false;
	}
		

	//SetRect(&rect, 0, 20, SCREEN_WIDTH, SCREEN_HEIGHT);
	information = "SCORE-000000 TIME 0300 STAGE 01\n";
	information += "PLAYER                 -05\n";
	information += "ENEMY                 P-03\n";
}

void UI::Update(int time, int simonHP, int simonEnergy, int simonLife, long score, int stage)
{
	this->simonHP = simonHP;
	this->simonEnergy = simonEnergy;
	this->simonLife = simonLife;
	this->score = score;
	this->stage = stage;

	string timeString = to_string(time);
	switch (timeString.length())
	{
	case 3:
		timeString = "0" + timeString;
		break;
	case 2:
		timeString = "00" + timeString;
		break;
	case 1:
		timeString = "0000" + timeString;
		break;
	}

	string stageString = to_string(stage);
	if (stageString.length() <= 1)
	{
		stageString = "0" + stageString;
	}

	string simonLifeString = to_string(simonLife);
	
	string simonEnergyString = to_string(simonEnergy);
	if (simonEnergyString.length() <= 1)
	{
		simonEnergyString = "0" + simonEnergyString;
	}

	string scoreString = to_string(score);
	switch (scoreString.length())
	{
	case 1:
		scoreString = "00000" + scoreString;
		break;
	case 2:
		scoreString = "0000" + scoreString;
		break;
	case 3:
		scoreString = "000" + scoreString;
		break;
	case 4:
		scoreString = "00" + scoreString;
		break;
	case 5:
		scoreString = "0" + scoreString;
		break;
	}

	information = "SCORE-" + scoreString + " TIME " + timeString + " STAGE " + stageString + "\n";
	information += "PLAYER                 -" + simonEnergyString + "\n";
	information += "ENEMY                 P-0" +simonLifeString+ "\n";

}

void UI::Render()
{
	RECT rect;
	SetRect(&rect, 0, 8, SCREEN_WIDTH, SCREEN_HEIGHT);
	//sprite heart
	Sprites::GetInstance()->GetSprite(301)->Draw(176, 16);
	//Simon HP
	float simonHPx = 56;
	float simonHPy = 17;
	for (int i = 0; i < simonHP; i++)
	{
		Sprites::GetInstance()->GetSprite(302)->Draw(simonHPx, simonHPy);
		simonHPx += 5;
	}
	for (int i = 0; i < 16 - simonHP; i++)
	{
		Sprites::GetInstance()->GetSprite(304)->Draw(simonHPx, simonHPy);
		simonHPx += 5;
	}
	//Ememy HP
	float ememyHPx = 56;
	float enemyHPy = 25;
	for (int i = 0; i < enemyHP; i++)
	{
		Sprites::GetInstance()->GetSprite(303)->Draw(ememyHPx, enemyHPy);
		ememyHPx += 5;
	}
	for (int i = 0; i < 16 - enemyHP; i++)
	{
		Sprites::GetInstance()->GetSprite(304)->Draw(ememyHPx, enemyHPy);
		ememyHPx += 5;
	}
	//Font information
	if (font)
	{
		font->DrawTextA(NULL, information.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	}
	//Square
	Sprites::GetInstance()->GetSprite(305)->Draw(140, 16);

}
