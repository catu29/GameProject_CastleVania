#pragma once
#include "d3dx9.h"
#include "Sprites.h"
#include "Define.h"
#include <string>
#include <vector>
using namespace std;


#define GAME_FONT "Resource\\Font\\prstart.ttf"

class UI
{
private:
	ID3DXFont * font;

	string information;
	


	int simonHP;
	int enemyHP;
	int uiHP;

	int score;
	int time;
	int item;
	int simonEnergy;
	int simonLife;
	int stage;
	int subWeapon;
public:
	UI(int simonHP, int simonEnergy, int simonLife, int stage);
	~UI();

	bool Initialize();
	void Update(int time, int simonHP, int simonEnergy, int simonLife, long score, int stage);
	void Render();

	void LoadResource();
};

