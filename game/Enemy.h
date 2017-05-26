#pragma once
class Enemy : public Object
{
public:
	Enemy();
	~Enemy();
	virtual void UpdateObject(std::chrono::milliseconds dt);
	virtual void RenderObject(int screen_x, int screen_y);
	void SetPosition(int _x, int _y);
protected:
	Gdiplus::Image *spriteSet;
	BOOL isMoving;
	BOOL movinvoid[4];
	UINT direction;
	UINT frameIndex;
};
