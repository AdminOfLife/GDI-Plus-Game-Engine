#include "stdafx.h"

Object::Object()
{
}

void Object::GetPosition(int & _x, int & _y)
{
	_x = x;
	_y = y;
}

Object::~Object()
{
}
