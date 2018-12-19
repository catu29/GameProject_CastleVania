#include <math.h>
#include "Simon.h"
#include "Textures.h"
#include "Animations.h"
#include "Whip.h"
#include "SubWeapons.h"
#include "Item.h"
#include "Candles.h"
#include "Bricks.h"
#include "Stairs.h"
#include "Gate.h"
#include "SceneManager.h"

Simon * Simon::_instance = NULL;

Simon::Simon()
{
	Whip::GetInstance()->SetType(NORMAL_WHIP);

	LoadAnimation();

	totalSubWeapon = -1;

	info = D3DXVECTOR3(16, 5, 3);
	SetState(SIMON_STATE_IDLE);
	direction.x = 1;

	isPassingGate = false;
	checkOnStairLeft = checkOnStairRight = false;
	isOnStairLeft = isOnStairRight = false;
	isUntouchable = false;
	canControlKeyboard = true;
}

Simon::~Simon()
{
}

Simon * Simon::GetInstance()
{
	if (_instance == NULL) _instance = new Simon();
	return _instance;
}

void Simon::LoadAnimation()
{
	AddAnimation(-50); // 0 animation turn back

	AddAnimation(-49); // 1 animation sit left

	AddAnimation(-48); // 2 animation idle left

	AddAnimation(-47); // 3 animation walking left

	AddAnimation(-46); // 4 animation idle upstairs left

	AddAnimation(-45); // 5 animation upstairs left

	AddAnimation(-44); // 6 animation idle downstairs left

	AddAnimation(-43); // 7 animation downstairs left

	AddAnimation(-42); // 8 animation stand attack left

	AddAnimation(-41); // 9 animation sit attack left

	AddAnimation(-40); // 10 animation upstairs attack left
	
	AddAnimation(-39); // 11 animation downstairs attack left

	AddAnimation(-38); // 12 animation stand get special item left

	//=========================================================

	AddAnimation(-37); // 13 animation sit right

	AddAnimation(-36); // 14 animation idle right

	AddAnimation(-35); // 15 animation walking right

	AddAnimation(-34); // 16 animation idle upstairs right

	AddAnimation(-33); // 17 animation upstairs right

	AddAnimation(-32); // 18 animation idle downstairs right

	AddAnimation(-31); // 19 animation downstairs right

	AddAnimation(-30); // 20 animation stand attack right

	AddAnimation(-29); // 21 animation sit attack right

	AddAnimation(-28); // 22 animation upstairs attack right

	AddAnimation(-27); // 23 animation downstairs attack right

	AddAnimation(-26); // 24 animation eat sp item attack right

	AddAnimation(-25); // 25 animation hitted left

	AddAnimation(-24); // 26 animation hitted right
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects)
{
	GameObject::Update(dt, colliableObjects);
	Whip::GetInstance()->SetPosition(this->position, !isSit, direction.x);

	if (isOnStairLeft == false && isOnStairRight == false && isPassingGate == false)
	{
		vy += SIMON_GRAVITY;
	}

	if (isPassingGate == true)
	{
		position.x += dx;
	}

	if (GetTickCount() - touchableTime >= 2000)
	{
		isUntouchable = false;
	}

	switch (state)
	{
	case SIMON_STATE_ATTACK:
		if (GetTickCount() - stateTime >= 300)
		{
			Whip::GetInstance()->SetState(WHIP_STATE_ATTACK);
			Whip::GetInstance()->HandleCollision(dt, colliableObjects);
		}

		if (GetTickCount() - stateTime >= 400)
		{
			if (isSit)
			{
				state = SIMON_STATE_SIT;
			}
			else
			{
				state = SIMON_STATE_IDLE;
			}
		}
		break;
	case SIMON_STATE_THROW:
		if (GetTickCount() - stateTime >= 100)
		{
			SubWeapons::GetInstance()->SetState(STATE_LIVE);
		}
		if (GetTickCount() - stateTime >= 400)
		{
			if (isSit)
			{
				state = SIMON_STATE_SIT;
			}
			else
			{
				state = SIMON_STATE_IDLE;
			}
		}
		break;
	case SIMON_STATE_GET_ITEM:
		if (GetTickCount() - stateTime >= 800)
		{
			SetState(SIMON_STATE_IDLE);
			canControlKeyboard = true;
		}
		break;
	}
	SubWeapons::GetInstance()->Update(dt, colliableObjects);

	vector<LPCOLLISIONEVENT> colliableEvents;
	vector<LPCOLLISIONEVENT> colliableResults;

	colliableEvents.clear();

	if (state != SIMON_STATE_DIE)
		CalPotentialCollision(colliableObjects, colliableEvents);

	if (colliableEvents.size() == 0)
	{
		position.y += dy;
		position.x += dx;
	}
	else
	{
		float min_tx, min_ty, nx, ny;
		FilterCollision(colliableEvents, colliableResults, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < colliableResults.size(); i++)
		{
			LPCOLLISIONEVENT e = colliableResults[i];

			if (colliableResults[i]->GetObj()->GetTag() == TAG_WALKING_GHOST && (colliableResults[i]->Get_nx() != 0 || colliableResults[i]->Get_ny() != 0))
			{
				if (!isUntouchable && colliableResults[i]->GetObj()->GetState() == STATE_LIVE)
				{
					vx = colliableResults[i]->Get_nx() * 0.05f;
					vy = -SIMON_JUMP_SPEED_Y;

					touchableTime = GetTickCount();
					state = SIMON_STATE_HITTED;

					isUntouchable = true;

					info.x -= 2;
				}
				else
				{
					position.x += dx;
					position.y += dy;
				}
			}

			else if (e->GetObj()->GetTag() == TAG_ITEM)
			{
				if (dynamic_cast<Item *>(colliableResults[i]->GetObj()))
				{
					Item * item = dynamic_cast<Item *>(colliableResults[i]->GetObj());
					switch (item->GetType())
					{
					case ITEM_SMALL_HEART:
						info.y += 1;
						break;
					case ITEM_BIG_HEART:
						info.y += 5;
						break;
					case ITEM_WHIP_UPGRADE:
						SetState(SIMON_STATE_GET_ITEM);
						Whip::GetInstance()->SetType((Whip::GetInstance()->GetType() + 1) > 5 ? Whip::GetInstance()->GetType() : Whip::GetInstance()->GetType() + 1);
						totalWhip = Whip::GetInstance()->GetType();
						break;
					case ITEM_KNIFE:
						SubWeapons::GetInstance()->SetType(SW_KNIFE);
						totalSubWeapon = SW_KNIFE;
						break;
					case ITEM_MONEY_BAG_1000:
						score += 1000;
						break;
					}
					item->SetState(STATE_DIE);
				}
			}

			else if (e->GetObj()->GetTag() == TAG_BRICK)
			{
				if (dynamic_cast<Brick *>(colliableResults[i]->GetObj()))
				{
					Brick * br = dynamic_cast<Brick *>(colliableResults[i]->GetObj());
					if (br->GetType() == BRICK_TYPE_GROUND)
					{
						if (isOnStairLeft == true || isOnStairRight == true)
						{
							position.x += dx;
							position.y += dy;
						}
						else
						{					
							if (e->Get_ny() < 0)
							{
								isOnStairLeft = isOnStairRight = false;
								vy = 0;

								if (state == SIMON_STATE_ATTACK || state == SIMON_STATE_THROW)
									vx = 0;
							}
							else if (e->Get_ny() > 0)
							{
								position.y += dy;
							}

							if (e->Get_nx() != 0)
							{
								vx = 0;
							}

							position.x += min_tx * dx; //+ nx * 0.4f;
							position.y += min_ty * dy + ny * 0.4f;
						}
					}
					else if (br->GetType() == BRICK_TYPE_ITEM)
					{
						position.x += dx;

						if (e->Get_ny() < 0)
						{
							isOnStairLeft = isOnStairRight = false;
							vy = 0;

							if (state == SIMON_STATE_ATTACK || state == SIMON_STATE_THROW)
								vx = 0;
						}

						if (!(br->CanMove()))
						{
							if (vx != 0.01f && vx != -0.01f)
							{
								Item * i = new Item(br->GetSpecialItemType());
								br->SetSpecialItem(i);
							}

							br->SetState(STATE_DIE);
						}
					}
					else if (br->GetType() == BRICK_TYPE_WALL)
					{
						vx = 0;
						position.x += dx * min_tx + nx * 0.4f;

						if (e->Get_ny() < 0)
						{
							vy = 0;
							position.y += min_ty * dy + ny * 0.4f;
						}
					}
					else if (br->GetType() == BRICK_TYPE_PRE_CHANGE) // For entrance scene - map 0
					{
						SceneManager::GetInstance()->GetCurrentScene()->DestroyAll();

						if (e->Get_nx() < 0 || br->GetDirection().x == -1)
						{
							state = SIMON_STATE_WALKING_RIGHT;
							vx = 0.01f;
							canControlKeyboard = false;
							br->SetState(STATE_DIE);
						}
						else if (br->GetDirection().x == 1)
						{
							state = SIMON_STATE_WALKING_LEFT;
							vx = -0.01f;
							br->SetPosition(br->GetPosition().x - 18.0f, br->GetPosition().y);
							br->SetDirection(D3DXVECTOR2(-1, 0));
							canControlKeyboard = false;
						}
					}
					else if (br->GetType() == BRICK_TYPE_CHANGE)
					{
						SceneManager::GetInstance()->GetCurrentScene()->SetChangingMap(true);
					}
				}
			}

			else if (e->GetObj()->GetTag() == TAG_GATE)
			{
				if (dynamic_cast<Gate *>(e->GetObj()))
				{
					Gate * gate = dynamic_cast<Gate *>(e->GetObj());

					if (direction.x * gate->GetDirection().x > 0)
					{
						canControlKeyboard = false;
						vx = 0;
						isPassingGate = true;

						gate->SetOpen(true);
						SceneManager::GetInstance()->GetCurrentScene()->SetPassingGate(true);
					}
					else
					{
						canControlKeyboard = true;
						gate->SetState(STATE_DIE);
					}
				}
			}
		}

		for (UINT i = 0; i < colliableEvents.size(); i++)
			delete colliableEvents[i];
	}
}

void Simon::HandleMove()
{
	if (canControlKeyboard && state != SIMON_STATE_ATTACK && state != SIMON_STATE_THROW)
	{
		if (vy == 0)
		{
			if (InputDevice::GetInstance()->IsKeyDown(DIK_UPARROW))
			{
				if (checkOnStairLeft == true)
				{
					SetState(SIMON_STATE_UPSTAIR_LEFT);
					checkOnStairLeft = false;
				}
				else if (checkOnStairRight == true)
				{
					SetState(SIMON_STATE_UPSTAIR_RIGHT);
					checkOnStairRight = false;
				}
				else if (isOnStairLeft == true)
				{
					SetState(SIMON_STATE_UPSTAIR_LEFT);
				}
				else if (isOnStairRight == true)
				{
					SetState(SIMON_STATE_UPSTAIR_RIGHT);
				}
				else
				{
					SetState(SIMON_STATE_IDLE);
				}
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_DOWNARROW))
			{
				if (checkOnStairLeft == true)
				{
					SetState(SIMON_STATE_DOWNSTAIR_RIGHT);
					checkOnStairLeft = false;
				}
				else if (checkOnStairRight == true)
				{
					SetState(SIMON_STATE_DOWNSTAIR_LEFT);
					checkOnStairRight = false;
				}
				else if (isOnStairLeft == true)
				{
					SetState(SIMON_STATE_DOWNSTAIR_RIGHT);
				}
				else if (isOnStairRight == true)
				{
					SetState(SIMON_STATE_DOWNSTAIR_LEFT);
				}
				else
				{
					SetState(SIMON_STATE_SIT);
				}
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_RIGHTARROW))
			{
				if (isOnStairRight == true)
				{
					SetState(SIMON_STATE_UPSTAIR_RIGHT);
				}
				else if (isOnStairLeft == true)
				{
					SetState(SIMON_STATE_DOWNSTAIR_RIGHT);
				}
				else if (isSit)
				{
					direction.x = 1;
				}
				else
				{
					SetState(SIMON_STATE_WALKING_RIGHT);
				}
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_LEFTARROW))
			{
				if (isOnStairLeft == true)
				{
					SetState(SIMON_STATE_UPSTAIR_LEFT);
				}
				else if (isOnStairRight == true)
				{
					SetState(SIMON_STATE_DOWNSTAIR_LEFT);
				}
				else if (isSit)
				{
					direction.x = -1;
				}
				else
				{
					SetState(SIMON_STATE_WALKING_LEFT);
				}
			}
			else
			{
				if (isOnStairLeft == true || isOnStairRight == true)
				{
					SetState(SIMON_STATE_IDLE_ON_STAIR);
				}
				
				if (isOnStairLeft == false && isOnStairRight == false)
				{
					SetState(SIMON_STATE_IDLE);
				}
			}
		}
		else if (isOnStairLeft == true || isOnStairRight == true)
		{
			if (InputDevice::GetInstance()->IsKeyDown(DIK_UPARROW))
			{
				if (isOnStairLeft == true && isOnStairRight == false)
				{
					SetState(SIMON_STATE_UPSTAIR_LEFT);
				}
				else if (isOnStairRight == true && isOnStairLeft == false)
				{
					SetState(SIMON_STATE_UPSTAIR_RIGHT);
				}
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_DOWNARROW))
			{
				if (isOnStairLeft == true && isOnStairRight == false)
				{
					SetState(SIMON_STATE_DOWNSTAIR_RIGHT);
				}
				else if (isOnStairRight == true && isOnStairLeft == false)
				{
					SetState(SIMON_STATE_DOWNSTAIR_LEFT);
				}
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_RIGHTARROW))
			{
				if (isOnStairRight == true)
				{
					SetState(SIMON_STATE_UPSTAIR_RIGHT);
				}
				else if (isOnStairLeft == true)
				{
					SetState(SIMON_STATE_DOWNSTAIR_RIGHT);
				}
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_LEFTARROW))
			{
				if (isOnStairLeft == true)
				{
					SetState(SIMON_STATE_UPSTAIR_LEFT);
				}
				else if (isOnStairRight == true)
				{
					SetState(SIMON_STATE_DOWNSTAIR_LEFT);
				}
			}
			else
			{
				SetState(SIMON_STATE_IDLE_ON_STAIR);
			}
		}
	}
}

void Simon::HandleEvent(bool isKeyDown)
{
	if (canControlKeyboard)
	{
		if (isKeyDown)
		{
			if (InputDevice::GetInstance()->IsKeyDown(DIK_LCONTROL) && state != SIMON_STATE_ATTACK)
			{
				SetState(SIMON_STATE_ATTACK);
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_SPACE) && isOnStairLeft == false && isOnStairRight == false
				&& state != SIMON_STATE_JUMP && state != SIMON_STATE_SIT && state != SIMON_STATE_ATTACK && state != SIMON_STATE_THROW)
			{
				SetState(SIMON_STATE_JUMP);
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_LSHIFT) &&
				totalSubWeapon != -1 &&
				info.y > 0 &&
				state != SIMON_STATE_THROW &&
				SubWeapons::GetInstance()->GetState() == STATE_DIE)
			{
				SetState(SIMON_STATE_THROW);
			}
		}
	}
}

void Simon::Render(ViewPort * camera)
{
	int ani;

	switch (state)
	{
	case SIMON_STATE_IDLE:
	{
		if (direction.x > 0)
		{
			ani = SIMON_ANI_IDLE_RIGHT;
		}
		else if (direction.x < 0)
		{
			ani = SIMON_ANI_IDLE_LEFT;
		}
	}
	break;

	case SIMON_STATE_IDLE_TURNBACK:
		ani = SIMON_ANI_IDLE_TURNBACK;
		break;

	case SIMON_STATE_WALKING_LEFT:
		ani = SIMON_ANI_WALKING_LEFT;
		if (isSit)
		{
			ani = SIMON_ANI_SIT_LEFT;
		}
		break;

	case SIMON_STATE_WALKING_RIGHT:
		ani = SIMON_ANI_WALKING_RIGHT;
		if (isSit)
		{
			ani = SIMON_ANI_SIT_RIGHT;
		}
		break;

	case SIMON_STATE_ATTACK:
		if (isOnStairRight == true)
		{
			if (direction.y < 0)
			{
				ani = SIMON_ANI_UPSTAIRS_ATTACK_RIGHT;
			}
			else if (direction.y > 0)
			{
				ani = SIMON_ANI_DOWNSTAIRS_ATTACK_LEFT;
			}
		}
		else if (isOnStairLeft == true)
		{
			if (direction.y < 0)
			{
				ani = SIMON_ANI_UPSTAIRS_ATTACK_LEFT;
			}
			else if (direction.y > 0)
			{
				ani = SIMON_ANI_DOWNSTAIRS_ATTACK_RIGHT;
			}
		}
		else if (!isSit)
		{
			if (direction.x > 0)
			{
				ani = SIMON_ANI_STAND_ATTACK_RIGHT;
			}
			else if (direction.x < 0)
			{
				ani = SIMON_ANI_STAND_ATTACK_LEFT;
			}
		}
		else
		{
			if (direction.x > 0)
			{
				ani = SIMON_ANI_SIT_ATTACK_RIGHT;
			}
			else if (direction.x < 0)
			{
				ani = SIMON_ANI_SIT_ATTACK_LEFT;
			}
		}

		Whip::GetInstance()->Render(camera);
		break;

	case SIMON_STATE_THROW:
		if (isOnStairRight == true)
		{
			ani = SIMON_ANI_UPSTAIRS_ATTACK_RIGHT;
		}
		else if (isOnStairLeft == true)
		{
			ani = SIMON_ANI_UPSTAIRS_ATTACK_LEFT;
		}
		else if (!isSit)
		{
			if (direction.x > 0)
			{
				ani = SIMON_ANI_STAND_ATTACK_RIGHT;
			}
			else if (direction.x < 0)
			{
				ani = SIMON_ANI_STAND_ATTACK_LEFT;
			}
		}
		else
		{
			if (direction.x > 0)
			{
				ani = SIMON_ANI_SIT_ATTACK_RIGHT;
			}
			else if (direction.x < 0)
			{
				ani = SIMON_ANI_SIT_ATTACK_LEFT;
			}
		}
		break;

	case SIMON_STATE_SIT:
		if (direction.x > 0)
		{
			ani = SIMON_ANI_SIT_RIGHT;
		}
		else if (direction.x < 0)
		{
			ani = SIMON_ANI_SIT_LEFT;
		}
		break;

	case SIMON_STATE_JUMP:
		if (direction.x > 0)
		{
			ani = SIMON_ANI_SIT_RIGHT;
		}
		else if (direction.x < 0)
		{
			ani = SIMON_ANI_SIT_LEFT;
		}
		break;

	case SIMON_STATE_HITTED:
		if (direction.x > 0)
		{
			ani = SIMON_ANI_HITTED_RIGHT;
		}
		else if (direction.x < 0)
		{
			ani = SIMON_ANI_HITTED_LEFT;
		}
		break;

	case SIMON_STATE_GET_ITEM:
		if (direction.x > 0)
		{
			ani = SIMON_ANI_STAND_GET_SPITEM_RIGHT;
		}
		else if (direction.x < 0)
		{
			ani = SIMON_ANI_STAND_GET_SPITEM_LEFT;
		}
		break;

	case SIMON_STATE_UPSTAIR_RIGHT:
		ani = SIMON_ANI_UPSTAIRS_RIGHT;
		break;

	case SIMON_STATE_DOWNSTAIR_RIGHT:
		ani = SIMON_ANI_DOWNSTAIRS_RIGHT;
		break;

	case SIMON_STATE_UPSTAIR_LEFT:
		ani = SIMON_ANI_UPSTAIRS_LEFT;
		break;

	case SIMON_STATE_DOWNSTAIR_LEFT:
		ani = SIMON_ANI_DOWNSTAIRS_LEFT;
		break;

	case SIMON_STATE_IDLE_ON_STAIR:
		if (direction.x > 0)
		{
			if (direction.y > 0)
			{
				ani = SIMON_ANI_IDLE_DOWNSTAIRS_RIGHT;
			}
			else
			{
				ani = SIMON_ANI_IDLE_UPSTAIRS_RIGHT;
			}

		}
		else if (direction.x < 0)
		{
			if (direction.y > 0)
			{
				ani = SIMON_ANI_IDLE_DOWNSTAIRS_LEFT;
			}
			else
			{
				ani = SIMON_ANI_IDLE_UPSTAIRS_LEFT;
			}
		}
	}

	D3DXVECTOR3 viewPortPos = this->position;

	CollisionBox bbox = this->GetBoundingBox();
	D3DXVECTOR3 bboxPos = viewPortPos;
	bboxPos.x = bbox.left;
	bboxPos.y = bbox.top;

	if (camera != NULL)
	{
		viewPortPos = camera->ConvertPosInViewPort(this->position);
		bboxPos = camera->ConvertPosInViewPort(bboxPos);
	}

	animations[ani]->Render(viewPortPos.x, viewPortPos.y);
	
	if (SubWeapons::GetInstance()->GetState() == STATE_LIVE)
	{
		SubWeapons::GetInstance()->Render(camera);
	}

	RenderBoundingBox(bboxPos.x, bboxPos.y);
}

void Simon::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_IDLE:
		vx = 0;
		vy = 0;
		direction.y = 0;
		isSit = false;
		isPassingGate = false;
		break;

	case SIMON_STATE_SIT:
		vx = 0;
		vy = 0;
		direction.y = 0;
		isSit = true;
		isOnStairLeft = false;
		isOnStairRight = false;
		break;

	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
		//direction.y = -1;
		isSit = false;
		break;

	case SIMON_STATE_WALKING_RIGHT:
		direction.x = 1;
		direction.y = 0;
		vx = SIMON_WALKING_SPEED;
		vy = 0;
		isSit = false;
		isOnStairLeft = isOnStairRight = false;
		break;

	case SIMON_STATE_WALKING_LEFT:
		direction.x = -1;
		direction.y = 0;
		vx = -SIMON_WALKING_SPEED;
		vy = 0;
		isSit = false;
		isOnStairLeft = isOnStairRight = false;
		break;

	case SIMON_STATE_IDLE_TURNBACK:
		direction.x = 0;
		direction.y = 0;
		vx = vy = 0;
		isSit = false;
		break;

	case SIMON_STATE_IDLE_ON_STAIR:
		vx = vy = 0;
		break;

	case SIMON_STATE_UPSTAIR_RIGHT:
		direction.x = 1;
		direction.y = -1;

		vx = SIMON_ONSTAIR_SPEED;
		vy = -SIMON_ONSTAIR_SPEED;

		isSit = false;
		isOnStairRight = true;
		isOnStairLeft = false;
		break;

	case SIMON_STATE_DOWNSTAIR_RIGHT:
		direction.x = 1;
		direction.y = 1;

		vx = SIMON_ONSTAIR_SPEED;
		vy = SIMON_ONSTAIR_SPEED;

		isSit = false;
		isOnStairRight = false;
		isOnStairLeft = true;
		break;

	case SIMON_STATE_UPSTAIR_LEFT:
		direction.x = -1;
		direction.y = -1;

		vx = -SIMON_ONSTAIR_SPEED;
		vy = -SIMON_ONSTAIR_SPEED;

		isSit = false;
		isOnStairLeft = true;
		isOnStairRight = false;
		break;

	case SIMON_STATE_DOWNSTAIR_LEFT:
		direction.x = -1;
		direction.y = 1;

		vx = -SIMON_ONSTAIR_SPEED;
		vy = SIMON_ONSTAIR_SPEED;

		isSit = false;
		isOnStairLeft = false;
		isOnStairRight = true;
		break;

	case SIMON_STATE_THROW:
		info.y--;
		if (info.y >= 0)
		{
			SubWeapons::GetInstance()->SetPosition(this->position, !isSit, direction.x);
		}
		break;
	}

}

CollisionBox Simon::GetBoundingBox()
{
	CollisionBox b(0, 0, 0, 0);
	switch (state)
	{
	case SIMON_STATE_JUMP:
	case SIMON_STATE_SIT:
		if (direction.x == 1)
			b.left = position.x + 6.0f;
		else
			b.left = position.x + 4.0f;

		b.top = position.y + (SIMON_STAND_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT);
		b.right = b.left + SIMON_BBOX_WIDTH;
		b.bottom = b.top + SIMON_SIT_BBOX_HEIGHT;
		break;
	case SIMON_STATE_ATTACK:
	case SIMON_STATE_THROW:
		if (direction.x == 1)
			b.left = position.x + 6.0f;
		else
			b.left = position.x + 4.0f;

		if (isSit == true)
		{
			b.top = position.y + (SIMON_STAND_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT);
			b.right = b.left + SIMON_BBOX_WIDTH;
			b.bottom = b.top + SIMON_SIT_BBOX_HEIGHT;
			break;
		}
		else
		{
			b.top = position.y;
			b.right = b.left + SIMON_BBOX_WIDTH;
			b.bottom = b.top + SIMON_STAND_BBOX_HEIGHT;
			break;
		}
	case SIMON_STATE_UPSTAIR_RIGHT:
		b.left = position.x;
		b.right = b.left + SIMON_BBOX_WIDTH;
		b.top = position.y;
		b.bottom = b.top + SIMON_STAND_BBOX_HEIGHT;
		break;

	case SIMON_STATE_IDLE_ON_STAIR:
		b.left = position.x;
		b.right = b.left + SIMON_BBOX_WIDTH;
		b.top = position.y;
		b.bottom = b.top + SIMON_STAND_BBOX_HEIGHT;
		break;

	default:
		if (direction.x == 1)
			b.left = position.x + 7.0f;
		else
			b.left = position.x + 5.0f;

		b.top = position.y;
		b.right = b.left + SIMON_BBOX_WIDTH;
		b.bottom = b.top + SIMON_STAND_BBOX_HEIGHT;
	}

	return b;
}

void Simon::CalPotentialCollision(vector<LPGAMEOBJECT>* colliableObjects, vector<LPCOLLISIONEVENT>& colliableEvents)
{
	for (UINT i = 0; i < colliableObjects->size(); i++)
	{
		if (colliableObjects->at(i)->GetTag() == TAG_LARGE_CANDLE || colliableObjects->at(i)->GetTag() == TAG_SMALL_CANDLE)
		{
			continue;
		}
		else if (colliableObjects->at(i)->GetTag() == TAG_ITEM)
		{
			if (AABB(this->GetBoundingBox(), colliableObjects->at(i)->GetBoundingBox()))
			{
				LPCOLLISIONEVENT e = new CollisionEvent(0, -this->direction.x, -this->direction.y, colliableObjects->at(i));
				colliableEvents.push_back(e);
			}
		}
		else if (colliableObjects->at(i)->GetTag() == TAG_STAIR)
		{
			if (AABB(this->GetBoundingBox(), colliableObjects->at(i)->GetBoundingBox()))
			{
				if (dynamic_cast<Stair *>(colliableObjects->at(i)))
				{
					Stair * stair = dynamic_cast<Stair *>(colliableObjects->at(i));

					if (stair->GetType() == STAIR_TYPE_BOTTOM_LEFT)
					{
						if (state == SIMON_STATE_DOWNSTAIR_RIGHT)
						{
							checkOnStairLeft = false;
							isOnStairLeft = false;
							SetState(SIMON_STATE_IDLE);
						}
						else
						{
							if (InputDevice::GetInstance()->IsKeyDown(DIK_UPARROW))
							{
								checkOnStairLeft = true;
								checkOnStairRight = false;

								if (direction.x == 1)
								{
									position.x = stair->GetPosition().x - 3.0f;
								}
								else if (direction.x == -1)
								{
									position.x = stair->GetPosition().x - 2.0f;
								}
							}
						}
					}
					//======
					else if (stair->GetType() == STAIR_TYPE_BOTTOM_RIGHT)
					{
						if (state == SIMON_STATE_DOWNSTAIR_LEFT)
						{
							isOnStairRight = false;
							checkOnStairRight = false;
							SetState(SIMON_STATE_IDLE);
						}
						else
						{
							if (InputDevice::GetInstance()->IsKeyDown(DIK_UPARROW))
							{
								checkOnStairLeft = false;
								checkOnStairRight = true;
								if (direction.x == 1)
								{
									position.x = stair->GetPosition().x - 3.0f;
								}
								else if (direction.x == -1)
								{
									position.x = stair->GetPosition().x - 2.0f;
								}
							}
						}
					}
					//======
					else if (stair->GetType() == STAIR_TYPE_END_UP)
					{
						if (state == SIMON_STATE_UPSTAIR_RIGHT || state == SIMON_STATE_UPSTAIR_LEFT)
						{
							if (direction.y < 0)
							{
								isOnStairRight = false;
								isOnStairLeft = false;

								checkOnStairRight = false;
								checkOnStairLeft = false;

								SetState(SIMON_STATE_IDLE);
							}
						}
					}
					//======
					else if (stair->GetType() == STAIR_TYPE_TOP_RIGHT)
					{
						if (isOnStairRight == true)
						{
							break;
						}
						else if (InputDevice::GetInstance()->IsKeyDown(DIK_DOWNARROW))
						{
							if (direction.x == 1)
							{
								position.x = stair->GetPosition().x - 6.0f;
							}
							else if (direction.x == -1)
							{
								position.x = stair->GetPosition().x - 5.0f;
							}

							checkOnStairRight = true;
							checkOnStairLeft = false;
						}
					}
					//======
					else if (stair->GetType() == STAIR_TYPE_TOP_LEFT)
					{
						if (isOnStairLeft == true)
						{
							break;
						}
						if (InputDevice::GetInstance()->IsKeyDown(DIK_DOWNARROW))
						{
							position.x = stair->GetPosition().x;
							checkOnStairLeft = true;
							checkOnStairRight = false;
						}
					}
				}
			}
		}
		else
		{
			if (isPassingGate)
			{
				if (colliableObjects->at(i)->GetTag() == TAG_GATE)
					continue;
			}
			LPCOLLISIONEVENT e = new CollisionEvent(-1, 0, 0, colliableObjects->at(i));

			if (this->vx == 0 && this->vy == 0)
			{
				CollisionBox b1 = this->GetBoundingBox();

				CollisionBox b2 = colliableObjects->at(i)->GetBoundingBox();

				if (AABB(b1, b2))
				{
					e = new CollisionEvent(0, -(this->direction.x), -(this->direction.y), colliableObjects->at(i));
				}
			}
			else
			{
				e = SweptAABBEx(colliableObjects->at(i));
			}

			if (e->Get_t() >= 0.0f && e->Get_t() < 1.0f)
				colliableEvents.push_back(e);
			else
				delete e;
		}

	}
	
	std::sort(colliableEvents.begin(), colliableEvents.end());
}