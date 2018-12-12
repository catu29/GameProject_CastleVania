#include "Animations.h"
#include <fstream>
#include <sstream>
#include <string.h>

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

void Animations::LoadDataFromFile(LPCSTR dataPath)
{
	fstream pFile;
	pFile.open(dataPath, fstream::in);

	string lineString; // chuoi nam tren dong hien tai
	string subString;
	int value;
	int * posSpace = new int[100]; // luu vi tri cua space vao mot mang
	vector<int> animationData;

	Animation * ani;

	while (pFile.good())
	{
		getline(pFile, lineString);
		ani = new Animation(100);
		//1. dem so chu so co tren 1 hang
		int numCount = 0;
		for (int i = 0; i < lineString.length(); i++)
		{
			if (lineString[i] == ' ')
			{
				numCount++;
			}
		}
		numCount++;
		//2. Add tung chu so vao vector, animationData[0] la id cua ani trong Animations
		for (int i = 0; i < numCount; i++)
		{
			if (i == 0)
			{
				posSpace[0] = lineString.find(" ", 0);

				subString = lineString.substr(0, posSpace[0]);

				value = atoi(subString.c_str());

				animationData.push_back(value);
			}
			else
			{
				posSpace[i] = lineString.find(" ", posSpace[i - 1] + 1);

				subString = lineString.substr(posSpace[i - 1] + 1, posSpace[i] - (posSpace[i - 1] + 1));

				value = atoi(subString.c_str());

				animationData.push_back(value);
			}
		}
		//add vao animations

		//3. Tao animation
		for (int i = 0; i < (numCount - 1) / 2; i++)
		{
			ani->Add(animationData[2 * i + 1], animationData[2 * i + 2]);
		}

		//4. Add ani vao animations list
		Animations::GetInstance()->Add(animationData[0], ani); // 0 animation nomal left

															   //5. Xoa data
		animationData.clear();
	}
}