#include <fstream>
#include <sstream>
#include <string.h>

#include "GameEntranceScene.h"
#include "Simon.h"
#include "Candles.h"
#include "Grid.h"
#include "SceneManager.h"
#include "Item.h"
#include "Bricks.h"
#include "Stairs.h"
#include "WalkingGhost.h"
#include "SubWeapons.h"

GameEntranceScene::GameEntranceScene()
{
	currentMap = 1;

	camBoundLeft = 0;
	level = 0;
	isPassingGate = false;

	gate1 = gate2 = NULL;

	ViewPort::GetInstance()->SetCameraPos(D3DXVECTOR3(0, 0, 0));

	listObjects = new vector<LPGAMEOBJECT>();
	colliableObjects = new vector<LPGAMEOBJECT>;

	ui = new UI(Simon::GetInstance()->GetInfo().x, Simon::GetInstance()->GetInfo().y, Simon::GetInstance()->GetInfo().z, 1);
}


GameEntranceScene::~GameEntranceScene()
{
}

void GameEntranceScene::KeyState()
{
	Simon::GetInstance()->HandleMove();

}

void GameEntranceScene::OnKeyUp(int keyCode)
{
	Simon::GetInstance()->HandleEvent(false);
}

void GameEntranceScene::OnKeyDown(int keyCode)
{
	Simon::GetInstance()->HandleEvent(true);
}

void GameEntranceScene::Update(DWORD dt)
{
	if (isChangeMap)
	{
		ChangeMap();
		gameTime += 0;
	}
	else if (isPassingGate)
	{
		gameTime += 0;

		if (level == 1)
		{
			HandlePassGate(gate1);
		}
	}
	else
	{
		gameTime += dt;
	}
	
	if (gameTime >= 1000)
	{
		ui->Update(
			300 - (int)gameTime / 1000,
			Simon::GetInstance()->GetInfo().x,
			Simon::GetInstance()->GetInfo().y,
			Simon::GetInstance()->GetInfo().z,
			Simon::GetInstance()->GetScore(),
			1);
	}

	for (int i = 0; i < listObjects->size(); i++)
		listObjects->at(i)->Update(dt, colliableObjects);

	Simon::GetInstance()->Update(dt, colliableObjects); // Update Simon, handle collision (include his weapons)

	D3DXVECTOR3 pos = ViewPort::GetInstance()->GetCameraPos();

	// Handling Simon position and camera position
	// 
	if (Simon::GetInstance()->GetPosition().x >= ViewPort::GetInstance()->GetCameraWidth() / 2.0f)
	{
		pos.x = Simon::GetInstance()->GetPosition().x - ViewPort::GetInstance()->GetCameraWidth() / 2.0f;

		if (Simon::GetInstance()->GetPosition().x >= (camBoundRight - ViewPort::GetInstance()->GetCameraWidth() / 2.0f))
		{
			pos.x = camBoundRight - (float)ViewPort::GetInstance()->GetCameraWidth();

			if (Simon::GetInstance()->GetPosition().x >= camBoundRight)
			{
				Simon::GetInstance()->SetPosition(camBoundRight - 16.0f, Simon::GetInstance()->GetPosition().y);
			}
		}
	}
	else
	{
		pos.x = camBoundLeft;

		if (Simon::GetInstance()->GetPosition().x <= camBoundLeft)
		{
			Simon::GetInstance()->SetPosition(camBoundLeft, Simon::GetInstance()->GetPosition().y);
		}
	}

	ViewPort::GetInstance()->SetCameraPos(pos); // Set camera postion 	

	HandleDestroyedObjects(); // Handle objects that be destroyed after colliding

	Grid::GetInstance()->Update(colliableObjects); // Update coliable object list following camera	
}

void GameEntranceScene::Initialize()
{
	ui->Initialize();
	listObjects->clear();

	TileMap * map_1a = new TileMap();
	map_1a->LoadMatrixMap("Resource\\Map\\MapState1_a_TileSet_bg.txt");
	map_1a->InitTileSet(Sprites::GetInstance()->GetSprite(99));
	listMap.push_back(map_1a);

	TileMap * map_1b = new TileMap();
	map_1b->LoadMatrixMap("Resource\\Map\\MapState1_b_TileSet_bg.txt");
	map_1b->InitTileSet(Sprites::GetInstance()->GetSprite(98));
	listMap.push_back(map_1b);

	LoadMap();
}

void GameEntranceScene::LoadMap()
{
	camBoundRight = listMap[currentMap]->GetColumns() * listMap[currentMap]->GetTileWidth();

	if (currentMap == 0)
	{
		listObjects->clear();
		Simon::GetInstance()->SetPosition(0, 112);
		Simon::GetInstance()->SetState(SIMON_STATE_IDLE);

		ViewPort::GetInstance()->SetCameraSize(256, 160);
		Grid::GetInstance()->UpdateGrid(listMap[currentMap]);
		float cellWidth = Grid::GetInstance()->GetCellWidth();
		float cellHeight = Grid::GetInstance()->GetCellHeight();

#pragma region Load Map 1 Objects
		LargeCandles * lCandles;

		lCandles = new LargeCandles(ITEM_BIG_HEART);
		lCandles->SetPosition(80, 112);
		lCandles->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(lCandles);

		lCandles = new LargeCandles(ITEM_WHIP_UPGRADE);
		lCandles->SetPosition(216, 112);
		lCandles->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(lCandles);

		lCandles = new LargeCandles(ITEM_BIG_HEART);
		lCandles->SetPosition(352, 112);
		lCandles->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(lCandles);

		lCandles = new LargeCandles(ITEM_WHIP_UPGRADE);
		lCandles->SetPosition(472, 112);
		lCandles->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(lCandles);

		lCandles = new LargeCandles(ITEM_KNIFE);
		lCandles->SetPosition(600, 112);
		lCandles->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(lCandles);

		Brick * bricks;

		for (float x = 0; x < 704; x += 16)
		{
			bricks = new Brick(BRICK_TYPE_GROUND);
			bricks->SetPosition(x, 144);
			bricks->SetCellsOffSet(cellWidth, cellHeight);
			listObjects->push_back(bricks);
		}

		for (float x = 720; x < 768; x += 16)
		{
			bricks = new Brick(BRICK_TYPE_GROUND);
			bricks->SetPosition(x, 144);
			bricks->SetCellsOffSet(cellWidth, cellHeight);
			listObjects->push_back(bricks);
		}

		bricks = new Brick(BRICK_TYPE_PRE_CHANGE);
		bricks->SetPosition(688, 112);
		bricks->SetDirection(D3DXVECTOR2(1, 0));
		bricks->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(bricks);

		bricks = new Brick(BRICK_TYPE_ITEM);
		bricks->SetPosition(704, 144);
		bricks->SetSpecialItemType(ITEM_MONEY_BAG_1000);
		bricks->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(bricks);
#pragma endregion
	}
	else if (currentMap == 1)
	{
		Simon::GetInstance()->SetState(SIMON_STATE_IDLE);
		Simon::GetInstance()->SetDirection(D3DXVECTOR2(1, 0));

		ViewPort::GetInstance()->SetCameraSize(256, 176);
		Grid::GetInstance()->UpdateGrid(listMap[currentMap]);
		

		listObjects->clear();

		if (level == 0)
		{
			camBoundLeft = 0;
			camBoundRight = 1536;

			Simon::GetInstance()->SetPosition(0, 128);

			LoadObjects(0);			

			gate1 = new Gate();
			gate1->SetPosition(1528, 16);
			gate1->SetDirection(D3DXVECTOR2(1, 0));
			gate1->SetCellsOffSet(Grid::GetInstance()->GetCellWidth(), Grid::GetInstance()->GetCellHeight());
		}
		else if (level == 1)
		{
			camBoundLeft = 1536;
			camBoundRight = 2048;

			Simon::GetInstance()->SetPosition(1500, 128);

			LoadObjects(1);

			gate2 = new Gate();
			gate2->SetPosition(2056, 16);
			gate2->SetDirection(D3DXVECTOR2(1, 0));
			gate2->SetCellsOffSet(Grid::GetInstance()->GetCellWidth(), Grid::GetInstance()->GetCellHeight());
		}
	}
}

void GameEntranceScene::LoadObjects(int lv)
{
	float cellWidth = Grid::GetInstance()->GetCellWidth();
	float cellHeight = Grid::GetInstance()->GetCellHeight();

	if (lv == 0) // Load objects in level 0
	{
		Brick * bricks;

		for (int x = 0; x < 1528; x += 16)
		{
			bricks = new Brick(BRICK_TYPE_GROUND);
			bricks->SetPosition(x, 160);
			bricks->SetCellsOffSet(cellWidth, cellHeight);
			listObjects->push_back(bricks);
		}

		for (int x = 688; x < 736; x += 16)
		{
			bricks = new Brick(BRICK_TYPE_GROUND);
			bricks->SetPosition(x, 96);
			bricks->SetCellsOffSet(cellWidth, cellHeight);
			listObjects->push_back(bricks);
		}

		for (int x = 928; x < 1008; x += 16)
		{
			bricks = new Brick(BRICK_TYPE_GROUND);
			bricks->SetPosition(x, 96);
			bricks->SetCellsOffSet(cellWidth, cellHeight);
			listObjects->push_back(bricks);
		}

		for (int x = 752; x < 912; x += 16)
		{
			bricks = new Brick(BRICK_TYPE_GROUND);
			bricks->SetPosition(x, 64);
			bricks->SetCellsOffSet(cellWidth, cellHeight);
			listObjects->push_back(bricks);
		}

		for (int x = 1392; x < 1528; x += 16)
		{
			bricks = new Brick(BRICK_TYPE_GROUND);
			bricks->SetPosition(x, 64);
			bricks->SetCellsOffSet(cellWidth, cellHeight);
			listObjects->push_back(bricks);
		}

		bricks = new Brick(BRICK_TYPE_ITEM);
		bricks->SetPosition(1008, 96);
		bricks->SetSpecialItemType(ITEM_MONEY_BAG_400);
		bricks->SetMoving();
		bricks->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(bricks);

		bricks = new Brick(BRICK_TYPE_WALL);
		bricks->SetPosition(1528, 0);
		bricks->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(bricks);

		for (int y = 80; y < 160; y += 16)
		{
			bricks = new Brick(BRICK_TYPE_WALL);
			bricks->SetPosition(1528, y);
			bricks->SetCellsOffSet(cellWidth, cellHeight);
			listObjects->push_back(bricks);
		}

		Stair * stairs;

		stairs = new Stair(STAIR_TYPE_BOTTOM_RIGHT);
		stairs->SetPosition(616, 156);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);

		stairs = new Stair(STAIR_TYPE_BOTTOM_RIGHT);
		stairs->SetPosition(712, 92);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);

		stairs = new Stair(STAIR_TYPE_BOTTOM_RIGHT);
		stairs->SetPosition(1288, 156);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);

		stairs = new Stair(STAIR_TYPE_BOTTOM_LEFT);
		stairs->SetPosition(936, 92);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);

		stairs = new Stair(STAIR_TYPE_TOP_RIGHT);
		stairs->SetPosition(680, 92);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);

		stairs = new Stair(STAIR_TYPE_TOP_RIGHT);
		stairs->SetPosition(744, 60);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);

		stairs = new Stair(STAIR_TYPE_TOP_RIGHT);
		stairs->SetPosition(1384, 60);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);

		stairs = new Stair(STAIR_TYPE_TOP_LEFT);
		stairs->SetPosition(904, 62);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);

		stairs = new Stair(STAIR_TYPE_END_UP);
		stairs->SetPosition(680, 61);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);

		stairs = new Stair(STAIR_TYPE_END_UP);
		stairs->SetPosition(744, 30);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);

		stairs = new Stair(STAIR_TYPE_END_UP);
		stairs->SetPosition(904, 30);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);

		stairs = new Stair(STAIR_TYPE_END_UP);
		stairs->SetPosition(1384, 30);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);

		WalkingGhost * wg;

		wg = new WalkingGhost();
		wg->SetPosition(250, 100);
		wg->SetDirection(D3DXVECTOR2(-1, 0));
		wg->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(wg);
	}
	else if (lv == 1) // Load objects in level 1
	{
		Brick * bricks;

		for (int x = 1536; x < 1582; x += 16)
		{
			bricks = new Brick(BRICK_TYPE_GROUND);
			bricks->SetPosition(x, 160);
			bricks->SetCellsOffSet(cellWidth, cellHeight);
			listObjects->push_back(bricks);
		}

		for (int x = 1600; x < 1792; x += 16)
		{
			bricks = new Brick(BRICK_TYPE_GROUND);
			bricks->SetPosition(x, 160);
			bricks->SetCellsOffSet(cellWidth, cellHeight);
			listObjects->push_back(bricks);
		}

		for (int x = 1664; x < 1712; x += 16)
		{
			bricks = new Brick(BRICK_TYPE_GROUND);
			bricks->SetPosition(x, 96);
			bricks->SetCellsOffSet(cellWidth, cellHeight);
			listObjects->push_back(bricks);
		}

		for (int x = 1536; x < 1664; x += 16)
		{
			bricks = new Brick(BRICK_TYPE_GROUND);
			bricks->SetPosition(x, 64);
			bricks->SetCellsOffSet(cellWidth, cellHeight);
			listObjects->push_back(bricks);
		}

		bricks = new Brick(BRICK_TYPE_WALL);
		bricks->SetPosition(1528, 0);
		bricks->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(bricks);

		for (int y = 80; y < 160; y += 16)
		{
			bricks = new Brick(BRICK_TYPE_WALL);
			bricks->SetPosition(1528, y);
			bricks->SetCellsOffSet(cellWidth, cellHeight);
			listObjects->push_back(bricks);
		}

		bricks = new Brick(BRICK_TYPE_WALL);
		bricks->SetPosition(1792, 96);
		bricks->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(bricks);

		bricks = new Brick(BRICK_TYPE_WALL);
		bricks->SetPosition(1792, 112);
		bricks->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(bricks);

		bricks = new Brick(BRICK_TYPE_WALL);
		bricks->SetPosition(1792, 160);
		bricks->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(bricks);

		bricks = new Brick(BRICK_TYPE_WALL);
		bricks->SetPosition(1580, 128);
		bricks->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(bricks);

		bricks = new Brick(BRICK_TYPE_WALL);
		bricks->SetPosition(1792, 128);
		bricks->SetMoving();
		bricks->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(bricks);

		bricks = new Brick(BRICK_TYPE_ITEM);
		bricks->SetPosition(1792, 144);
		bricks->SetSpecialItemType(ITEM_POT_ROAST);
		bricks->SetMoving();
		bricks->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(bricks);

		Stair * stairs;

		stairs = new Stair(STAIR_TYPE_BOTTOM_LEFT);
		stairs->SetPosition(1768, 156);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);

		stairs = new Stair(STAIR_TYPE_TOP_LEFT);
		stairs->SetPosition(1704, 92);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);

		stairs = new Stair(STAIR_TYPE_END_UP);
		stairs->SetPosition(1704, 61);
		stairs->SetCellsOffSet(cellWidth, cellHeight);
		listObjects->push_back(stairs);
	}
}

void GameEntranceScene::HandlePassGate(Gate * &gate)
{
	float vx, vy;
	Simon::GetInstance()->GetSpeed(vx, vy);
	D3DXVECTOR3 pos = ViewPort::GetInstance()->GetCameraPos();

	if (vx == 0)
	{
		if (gate->IsOpening())
		{
			if (pos.x < (Simon::GetInstance()->GetPosition().x - ViewPort::GetInstance()->GetCameraWidth() / 2.0f))
			{
				pos.x += 0.04f;
				ViewPort::GetInstance()->SetCameraPos(pos);
			}
			else
			{
				gate->SetState(GATE_STATE_OPEN);
				camBoundLeft = gate->GetPosition().x + 8.0f;
			}
		}
		else
		{
			if(pos.x < camBoundLeft)
			{
				pos.x += 0.04f;
				ViewPort::GetInstance()->SetCameraPos(pos);
			}
			else
			{
				pos.x = camBoundLeft;
				ViewPort::GetInstance()->SetCameraPos(pos);

				Simon::GetInstance()->SetState(SIMON_STATE_IDLE);
				Simon::GetInstance()->SetControlKB(true);
			}
		}
	}
	else
	{
		if (Simon::GetInstance()->GetPosition().x > gate->GetPosition().x + 48.0f)
		{
			Simon::GetInstance()->SetSpeed(0, 0);

			gate->SetState(GATE_STATE_CLOSE);
			gate->SetOpen(false);
		}
	}
}

void GameEntranceScene::HandleDestroyedObjects()
{
	for (int i = 0; i < listObjects->size(); i++)
	{
		if ((listObjects->at(i))->CanDestroy())
		{
			if ((listObjects->at(i))->GetTag() == TAG_LARGE_CANDLE)
			{
				Item * item;
				switch (dynamic_cast<LargeCandles*> (listObjects->at(i))->GetDropItem())
				{
				case ITEM_BIG_HEART:
					item = new Item(ITEM_BIG_HEART);
					break;
				case ITEM_WHIP_UPGRADE:
					item = new Item(ITEM_WHIP_UPGRADE);
					break;
				case ITEM_KNIFE:
					item = new Item(ITEM_KNIFE);
					break;
				default:
					item = new Item(ITEM_SMALL_HEART);
					break;
				}
				item->SetPosition(listObjects->at(i)->GetPosition().x, listObjects->at(i)->GetPosition().y);
				item->SetCellsOffSet(Grid::GetInstance()->GetCellWidth(), Grid::GetInstance()->GetCellHeight());
				listObjects->push_back(item);
			}
			else if ((listObjects->at(i))->GetTag() == TAG_SMALL_CANDLE)
			{
				Item * item;
				switch (dynamic_cast<SmallCandles*> (listObjects->at(i))->GetDropItem())
				{
				case ITEM_BIG_HEART:
					item = new Item(ITEM_BIG_HEART);
					break;
				case ITEM_WHIP_UPGRADE:
					item = new Item(ITEM_WHIP_UPGRADE);
					break;
				case ITEM_KNIFE:
					item = new Item(ITEM_KNIFE);
					break;
				case ITEM_DOUBLE_SHOT:
					item = new Item(ITEM_DOUBLE_SHOT);
					break;
				case ITEM_POT_ROAST:
					item = new Item(ITEM_POT_ROAST);
					break;
				case ITEM_AXE:
					item = new Item(ITEM_AXE);
					break;
				case ITEM_MONEY_BAG_100:
					item = new Item(ITEM_MONEY_BAG_100);
					break;
				default:
					item = new Item(ITEM_SMALL_HEART);
					break;
				}
				item->SetPosition(listObjects->at(i)->GetPosition().x, listObjects->at(i)->GetPosition().y);
				item->SetCellsOffSet(Grid::GetInstance()->GetCellWidth(), Grid::GetInstance()->GetCellHeight());
				listObjects->push_back(item);
			}
			else if ((listObjects->at(i))->GetTag() == TAG_BRICK)
			{
				if (dynamic_cast<Brick *>(listObjects->at(i)))
				{
					Brick * br = dynamic_cast<Brick *>(listObjects->at(i));

					if (br->GetSpecialItem() != NULL)
					{
						Item * item = br->GetSpecialItem();

						if (item->GetType() == ITEM_MONEY_BAG_1000)
						{
							if (currentMap == 0)
							{
								item->SetPosition(624, 144);
								item->SetCellsOffSet(Grid::GetInstance()->GetCellWidth(), Grid::GetInstance()->GetCellHeight());
							}
						}

						listObjects->push_back(item);
					}
					else if (br->GetType() == BRICK_TYPE_PRE_CHANGE)
					{
						Brick *changeBrick = new Brick(BRICK_TYPE_CHANGE);
						changeBrick->SetPosition(714, 112);
						changeBrick->SetCellsOffSet(Grid::GetInstance()->GetCellWidth(), Grid::GetInstance()->GetCellHeight());
						listObjects->push_back(changeBrick);
					}
				}
			}

			listObjects->erase(listObjects->begin() + i);
		}
	}
}

void GameEntranceScene::Draw()
{
	ui->Render();

	listMap[currentMap]->Draw(ViewPort::GetInstance());

	for (int i = 0; i < colliableObjects->size(); i++)
	{
		listObjects->at(i)->Render(ViewPort::GetInstance());
	}

	Simon::GetInstance()->Render(ViewPort::GetInstance());
}

void GameEntranceScene::DestroyAll()
{
	if (currentMap == 0)
	{
		for (UINT i = 0; i < listObjects->size(); i++)
		{
			if (listObjects->at(i)->GetTag() == TAG_BRICK)
				continue;

			listObjects->erase(listObjects->begin() + i);
		}
	}
	else if (currentMap == 1)
	{
		for (UINT i = 0; i < listObjects->size(); i++)
		{
			if (listObjects->at(i)->GetTag() == TAG_BRICK || listObjects->at(i)->GetTag() == TAG_STAIR)
				continue;

			listObjects->erase(listObjects->begin() + i);
		}
	}
}

void GameEntranceScene::ChangeMap()
{
	listObjects->clear();

	if (currentMap == 2)
		currentMap--;
	else
		currentMap++;


	LoadMap();
	Simon::GetInstance()->SetControlKB(true);
	isChangeMap = false;
}
