#include "stdafx.h"

Enemy::Enemy()
{
	this->x = 0;
	this->y = 0;
	this->movinvoid[0] = false;
	this->movinvoid[1] = false;
	this->movinvoid[2] = false;
	this->movinvoid[3] = false;
	this->isMoving = false;
	this->direction = 0;
	this->frameIndex = 0;
	this->speed = 10;
	this->spriteSet = ResourceManager<Gdiplus::Image>::Load(L"Resource/001-Fighter01.png");
}

Enemy::~Enemy()
{
	delete spriteSet;
}

void Enemy::UpdateObject(std::chrono::milliseconds dt)
{
	if (movinvoid[0] || movinvoid[1] || movinvoid[2] || movinvoid[3])
	{
		UINT counter = 0;
		if (movinvoid[0])
		{
			direction = 0;
			counter++;
		}
		else if (movinvoid[1])
		{
			direction = 1;
			counter++;
		}
		else if (movinvoid[2])
		{
			direction = 2;
			counter++;
		}
		else if (movinvoid[3])
		{
			direction = 3;
			counter++;
		}

		if (counter == 2)
		{
			if (movinvoid[0])
				y += speed * sin(45);
			if (movinvoid[1])
				x -= speed * cos(45);
			if (movinvoid[2])
				x += speed * cos(45);
			if (movinvoid[3])
				y -= speed * sin(45);
		}
		else if (counter == 1)
		{
			if (movinvoid[0])
				y += speed;
			if (movinvoid[1])
				x -= speed;
			if (movinvoid[2])
				x += speed;
			if (movinvoid[3])
				y -= speed;
		}
		frameIndex = (frameIndex + 1) % 4;
		movinvoid[0] = movinvoid[1] = movinvoid[2] = movinvoid[3] = false;
	}
}

void Enemy::RenderObject(int screen_x, int screen_y)
{
	if (spriteSet == nullptr)
		return;
	Gdiplus::Graphics *g = scene->GetGraphics();
	int width = spriteSet->GetWidth() / 4, height = spriteSet->GetHeight() / 4;
	g->DrawImage(spriteSet, x - width / 2 - screen_x, y - height / 2 - screen_y, width * frameIndex, height * direction, width, height, Gdiplus::Unit::UnitPixel);
}

void Enemy::SetPosition(int _x, int _y)
{
	x = _x;
	y = _y;
}
