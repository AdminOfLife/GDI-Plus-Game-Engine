#include "stdafx.h"

Character::Character()
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
	this->spriteSet = ResourceManager<Gdiplus::Image>::Load(L"resource/001-Fighter01.png");

	this->InputComponent.AddBinding(VK_RIGHT, INPUT_PRESSED, new Function(&Character::MoveRight, this));
	this->InputComponent.AddBinding(VK_LEFT, INPUT_PRESSED, new Function(&Character::MoveLeft, this));
	this->InputComponent.AddBinding(VK_UP, INPUT_PRESSED, new Function(&Character::MoveUp, this));
	this->InputComponent.AddBinding(VK_DOWN, INPUT_PRESSED, new Function(&Character::MoveDown, this));
}

Character::~Character()
{
	delete spriteSet;
}

void Character::SetPosition(int _x, int _y)
{
	this->x = _x;
	this->y = _y;
}

void Character::Stop()
{
	frameIndex = 0;
}

void Character::MoveDown()
{
	movinvoid[0] = TRUE;
}

void Character::MoveLeft()
{
	movinvoid[1] = TRUE;
}

void Character::MoveRight()
{
	movinvoid[2] = TRUE;
}

void Character::MoveUp()
{
	movinvoid[3] = TRUE;
}
/*
void Character::CheckPosition()
{
	TCHAR temp[256];
	wsprintf(temp, L"x : %d, y : %d", this->x, this->y);
	MessageBox(0, temp, L"Position", MB_OK);
}
*/
void Character::UpdateObject(std::chrono::milliseconds dt)
{
	this->InputComponent.Update();

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

void Character::RenderObject(int screen_x, int screen_y)
{
	if (spriteSet == nullptr)
		return;
	Gdiplus::Graphics *g = scene->GetGraphics();
	int width = spriteSet->GetWidth() / 4, height = spriteSet->GetHeight() / 4;
	g->DrawImage(spriteSet, x - width / 2 - screen_x, y - height / 2 - screen_y, width * frameIndex, height * direction, width, height, Gdiplus::Unit::UnitPixel);
}
