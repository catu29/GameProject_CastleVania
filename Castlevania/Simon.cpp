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

	onStairLeft = onStairRight = false;

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

	AddAnimation(-47); //3 animation walking left

	AddAnimation(-46); // 4 animation upstairs left

	AddAnimation(-45); // 5 animation downstairs left

	AddAnimation(-44); // 6 animation stand attack left

	AddAnimation(-43); // 7 animation sit attack left

	AddAnimation(-42); // 8 animation upstairs attack left

	AddAnimation(-41); // 9 animation downstairs attack left

	AddAnimation(-40); // 10 animation eat sp item attack left

					   //======================================================================
	AddAnimation(-39); // 11 animation sit right

	AddAnimation(-38); // 12 animation idle right

	AddAnimation(-37); // 13 animation walking right

	AddAnimation(-36); // 14 animation upstairs right

	AddAnimation(-35); // 15 animation downstairs right

	AddAnimation(-34); // 16 animation stand attack right

	AddAnimation(-33); // 17 animation sit attack right

	AddAnimation(-32); // 18 animation upstairs attack right

	AddAnimation(-31); // 19 animation downstairs attack right

	AddAnimation(-30); // 20 animation eat sp item attack right
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects)
{
	GameObject::Update(dt, colliableObjects);
	if (onStairLeft == false && onStairRight == false)
	{
		vy += SIMON_GRAVITY;
	}

	switch (state)
	{
	case SIMON_STATE_ATTACK:
		Whip::GetInstance()->SetPosition(this->position, !isSit, direction.x);
		Whip::GetInstance()->SetState(WHIP_STATE_ATTACK);

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
		Whip::GetInstance()->HandleCollision(dt, colliableObjects);
		break;
	case SIMON_STATE_THROW:
		SubWeapons::GetInstance()->SetPosition(this->position, !isSit, direction.x);
		SubWeapons::GetInstance()->SetState(STATE_LIVE);

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
		SubWeapons::GetInstance()->Update(dt, colliableObjects);
		break;
	}

	vector<LPCOLLISIONEVENT> colliableEvents;
	vector<LPCOLLISIONEVENT> colliableResults;

	colliableEvents.clear();

	if (state != SIMON_STATE_DIE)
		CalPotentialCollision(colliableObjects, colliableEvents);

	if (colliableEvents.size() == 0)
	{
		position.x += dx;
		position.y += dy;
	}
	else
	{
		float min_tx, min_ty, nx, ny;

		// @Danh: Which events did you filter?
		FilterCollision(colliableEvents, colliableResults, min_tx, min_ty, nx, ny);

		position.x += min_tx * dx;// + nx * 0.4f;
		position.y += min_ty * dy + ny * 0.4f;

		for (UINT i = 0; i < colliableResults.size(); i++)
		{
			LPCOLLISIONEVENT e = colliableResults[i];

			if (e->GetObj()->GetTag() == TAG_LARGE_CANDLE)
			{
				position.x += dx;

				if (e->Get_ny() != 0)
					position.y += dy;
			}

			else if (e->GetObj()->GetTag() == TAG_ITEM)
			{
				// @Danh: simon did not hit Whip ?? Maybe they are filtered???

				if (dynamic_cast<Item *>(colliableResults[i]->GetObj()))
				{
					if (e->Get_ny() != 0)
					{
						position.y += dy;
					}
					position.x += dx;

					Item * item = dynamic_cast<Item *>(colliableResults[i]->GetObj());
					switch (item->GetType())
					{
					case ITEM_BIG_HEART:
						info.y += 5;
						break;
					case ITEM_WHIP_UPGRADE:
						// @Danh: Simon vs Whip Item ???
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
						if (state == SIMON_STATE_DOWNSTAIR_LEFT || state == SIMON_STATE_DOWNSTAIR_RIGHT)
						{
							onStairLeft = false;
							onStairRight = false;
							vy = 0;
							position.y += dy * min_ty + ny * 0.4f;
						}

						if (e->Get_ny() < 0)
						{
							vy = 0;

							if (state == SIMON_STATE_ATTACK || state == SIMON_STATE_THROW)
								vx = 0;
						}
						else if (e->Get_ny() > 0)
						{
							position.x += dx;
							position.y += dy;
						}
					}
					else if (br->GetType() == BRICK_TYPE_ITEM)
					{
						if (!(br->CanMove()))
						{
							if (vx != 0.02f && vx != -0.02f)
							{
								Item * i = new Item(br->GetSpecialItemType());
								br->SetSpecialItem(i);
							}

							br->SetState(STATE_DIE);
						}
					}
					else if (br->GetType() == BRICK_TYPE_WALL)
					{
						if (e->Get_nx() != 0)
						{
							vx = 0;
							position.x += min_tx * dx + nx * 0.4f;
						}

						position.y += dy;
					}
					else if (br->GetType() == BRICK_TYPE_PRE_CHANGE) // For entrance scene - map 0
					{
						if (e->Get_ny() < 0)
						{
							position.y += dy;
						}

						if (e->Get_nx() < 0 || br->GetDirection().x == -1)
						{
							state = SIMON_STATE_WALKING_RIGHT;
							vx = 0.01f;
							position.x += dx;
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

			else if (e->GetObj()->GetTag() == TAG_STAIR)
			{
				if (dynamic_cast<Stair *>(e->GetObj()))
				{
					Stair * stair = dynamic_cast<Stair *>(e->GetObj());

					if (onStairLeft == false && onStairRight == false)
					{
						position.x += dx;
						if (e->Get_ny() < 0)
							position.y += dy;
					}

					if (stair->GetType() == STAIR_TYPE_BOTTOM_LEFT)
					{
						if (state == SIMON_STATE_DOWNSTAIR_RIGHT)
						{
							onStairLeft = false;
						}
						else
						{
							if (InputDevice::GetInstance()->IsKeyDown(DIK_UPARROW))
							{
								onStairLeft = true;
								onStairRight = false;
							}
						}
					}
					else if (stair->GetType() == STAIR_TYPE_BOTTOM_RIGHT)
					{
						/*if (state == SIMON_STATE_DOWNSTAIR_LEFT)
						{
						onStairRight = false;
						}
						else*/
						{
							if (InputDevice::GetInstance()->IsKeyDown(DIK_UPARROW))
							{
								onStairLeft = false;
								onStairRight = true;
								position.x = stair->GetPosition().x - 8;
							}
						}
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
			if (InputDevice::GetInstance()->IsKeyDown(DIK_DOWNARROW))
			{
				if (onStairLeft == false && onStairRight == false)
				{
					SetState(SIMON_STATE_SIT);
				}
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_RIGHTARROW))
			{
				SetState(SIMON_STATE_WALKING_RIGHT);
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_LEFTARROW))
			{
				SetState(SIMON_STATE_WALKING_LEFT);
			}
			else
			{
				SetState(SIMON_STATE_IDLE);
			}
		}
		else if (onStairLeft == true || onStairRight == true)
		{
			if (InputDevice::GetInstance()->IsKeyDown(DIK_UPARROW))
			{
				if (onStairLeft == true && onStairRight == false)
				{
					SetState(SIMON_STATE_UPSTAIR_LEFT);
				}
				else if (onStairRight == true && onStairLeft == false)
				{
					SetState(SIMON_STATE_UPSTAIR_RIGHT);
				}
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_DOWNARROW))
			{
				if (onStairLeft == true && onStairRight == false)
				{
					SetState(SIMON_STATE_DOWNSTAIR_RIGHT);
				}
				else if (onStairRight == true && onStairLeft == false)
				{
					SetState(SIMON_STATE_DOWNSTAIR_LEFT);
				}
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_RIGHTARROW))
			{
				if (state == SIMON_STATE_IDLE_ON_STAIR)
				{
					if (direction.y > 0)
					{
						SetState(SIMON_STATE_DOWNSTAIR_RIGHT);
					}
					else
					{
						SetState(SIMON_STATE_UPSTAIR_RIGHT);
					}
				}
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_LEFTARROW))
			{
				if (state == SIMON_STATE_IDLE_ON_STAIR)
				{
					if (direction.y > 0)
					{
						SetState(SIMON_STATE_DOWNSTAIR_LEFT);
					}
					else
					{
						SetState(SIMON_STATE_UPSTAIR_LEFT);
					}
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
			if (InputDevice::GetInstance()->IsKeyDown(DIK_LCONTROL))
			{
				SetState(SIMON_STATE_ATTACK);
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_SPACE) && onStairLeft == false && onStairRight == false
				&& state != SIMON_STATE_JUMP && state != SIMON_STATE_SIT && state != SIMON_STATE_ATTACK && state != SIMON_STATE_THROW)
			{
				SetState(SIMON_STATE_JUMP);
			}
			else if (InputDevice::GetInstance()->IsKeyDown(DIK_LSHIFT) && totalSubWeapon != -1)
			{
				SetState(SIMON_STATE_THROW);
				SubWeapons::GetInstance()->SetState(STATE_LIVE);
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

	case SIMON_STATE_ATTACK: case SIMON_STATE_THROW:
		if (onStairRight == true)
		{
			ani = SIMON_ANI_UPSTAIRS_ATTACK_RIGHT;
		}
		else if (onStairLeft == true)
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

		Whip::GetInstance()->Render(camera);

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
		break;

	case SIMON_STATE_SIT:
		vx = 0;
		vy = 0;
		direction.y = 0;
		isSit = true;
		onStairLeft = false;
		onStairRight = false;
		break;

	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
		isSit = false;
		break;

	case SIMON_STATE_WALKING_RIGHT:
		direction.x = 1;
		direction.y = 0;
		vx = SIMON_WALKING_SPEED;
		vy = 0;
		isSit = false;
		onStairLeft = onStairRight = false;
		break;

	case SIMON_STATE_WALKING_LEFT:
		direction.x = -1;
		direction.y = 0;
		vx = -SIMON_WALKING_SPEED;
		vy = 0;
		isSit = false;
		onStairLeft = onStairRight = false;
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
		onStairRight = true;
		onStairLeft = false;
		break;

	case SIMON_STATE_DOWNSTAIR_RIGHT:
		direction.x = 1;
		direction.y = 1;

		vx = SIMON_ONSTAIR_SPEED;
		vy = SIMON_ONSTAIR_SPEED;

		isSit = false;
		onStairRight = true;
		onStairLeft = false;
		break;

	case SIMON_STATE_UPSTAIR_LEFT:
		direction.x = -1;
		direction.y = -1;

		vx = vy = -SIMON_ONSTAIR_SPEED;

		isSit = false;
		onStairLeft = true;
		onStairRight = false;
		break;

	case SIMON_STATE_DOWNSTAIR_LEFT:
		direction.x = -1;
		direction.y = 1;

		vx = -SIMON_ONSTAIR_SPEED;
		vy = SIMON_ONSTAIR_SPEED;

		isSit = false;
		onStairLeft = true;
		onStairRight = false;
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
		b.left = position.x - 6.0f;
		b.right = b.left + SIMON_BBOX_WIDTH;
		b.top = position.y;
		b.bottom = b.top + SIMON_STAND_BBOX_HEIGHT;
		break;

	case SIMON_STATE_IDLE_ON_STAIR:
		if (direction.x > 0)
		{
			b.left = position.x - 6.0f;
		}
		else
		{
			b.left = position.x;
		}

		b.right = b.left + SIMON_BBOX_WIDTH;
		b.top = position.y;
		b.bottom = b.top + SIMON_STAND_BBOX_HEIGHT;
		break;

	default:
		if (direction.x == 1)
			b.left = position.x + 6.0f;
		else
			b.left = position.x + 4.0f;

		b.top = position.y;
		b.right = b.left + SIMON_BBOX_WIDTH;
		b.bottom = b.top + SIMON_STAND_BBOX_HEIGHT;
	}

	return b;
}