#include "Animations.h"

//Struture of Animation
void Animation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = Sprites::GetInstance()->GetSprite(spriteId);
	LPANIMATION_FRAME frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
}

void Animation::Render(int x, int y)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			
			lastFrameTime = now;
			if (currentFrame == frames.size())
			{
				currentFrame = 0;
			}
		}		
	}
	frames[currentFrame]->GetSprite()->Draw(x, y);
}

//Animation Manager
Animations * Animations::instance = NULL;

Animations * Animations::GetInstance()
{
	if (instance == NULL) instance = new Animations();
	return instance;
}

void Animations::Add(int id, LPANIMATION ani)
{
	animationsList[id] = ani;
}

LPANIMATION Animations::GetAnimation(int id)
{
	return animationsList[id];
}